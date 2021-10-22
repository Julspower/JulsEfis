#include "i2c_comm.h"


I2C_Comm::I2C_Comm()
{
    stData.dYaw = 0;
}

I2C_Comm::~I2C_Comm()
{

}

void I2C_Comm::process()
{
    float qw, qx, qy, qz, temperature, pressure;
    double roll, pitch, yaw;

    m_EM7180 = new EM7180_Master(100, 200, 200, 50, 3);
    m_bStop = false;
    if(!m_EM7180->begin())
        m_bStop = true;

    while(!m_bStop)
    {
        m_EM7180->checkEventStatus();

        if (m_EM7180->gotError())
        {
            printf("ERROR: %s\n", m_EM7180->getErrorString());
            break;
        }
        //  Define output variables from updated quaternion---these are Tait-Bryan
        //  angles, commonly used in aircraft orientation.  In this coordinate
        //  system, the positive z-axis is down toward Earth.  Yaw is the angle
        //  between Sensor x-axis and Earth magnetic North (or true North if
        //  corrected for local declination, looking down on the sensor positive
        //  yaw is counterclockwise.  Pitch is angle between sensor x-axis and
        //  Earth ground plane, toward the Earth is positive, up toward the sky is
        //  negative.  Roll is angle between sensor y-axis and Earth ground plane,
        //  y-axis up is positive roll.  These arise from the definition of the
        //  homogeneous rotation matrix constructed from q.  Tait-Bryan
        //  angles as well as Euler angles are non-commutative; that is, the get
        //  the correct orientation the rotations must be applied in the correct
        //  order which for this configuration is yaw, pitch, and then roll.  For
        //  more see http://en.wikipedia.org/wiki/Conversion_between_q_and_Euler_angles
        //  which has additional links.
        if (m_EM7180->gotQuaternion())
        {
            m_EM7180->readQuaternion(qw, qx, qy, qz);

            roll = atan2(2.0f * (qw * qx + qy * qz), qw * qw - qx * qx - qy * qy + qz * qz);
            pitch = -asin(2.0f * (qx * qz - qw * qy));
            yaw = atan2(2.0f * (qx * qy + qw * qz), qw * qw + qx * qx - qy * qy - qz * qz);

            pitch *= 180.0f / M_PI;
            yaw   *= 180.0f / M_PI;
            yaw   -= 14.7f; // Declination at Danville, California is 13 degrees 48 minutes and 47 seconds on 2014-04-04
            if(yaw < 0)
                yaw += 360.0f ; // Ensure yaw stays between 0 and 360
            roll *= 180.0f / M_PI;

            if (m_EM7180->gotBarometer())
            {
                m_EM7180->readBarometer(pressure, temperature);
        //        float altitude = (1.0f - powf(pressure / 1013.25f, 0.190295f)) * 44330.0f;
        //        printf("  Altitude = %5.2f m\n\n", altitude);
                stData.dPressure = pressure;
                stData.dTemp = temperature;
            }

            stData.dRoll = roll;
            stData.dYaw = yaw;
            stData.dPitch = pitch;
            emit newData();
        }

        // Or define output variable according to the Android system, where
        // heading (0 to 360) is defined by the angle between the y-axis and True
        // North, pitch is rotation about the x-axis (-180 to +180), and roll is
        // rotation about the y-axis (-90 to +90) In this systen, the z-axis is
        // pointing away from Earth, the +y-axis is at the "top" of the device
        // (cellphone) and the +x-axis points toward the right of the device.
        QThread::usleep(1250);
    }
    emit finished();
}

void I2C_Comm::StopI2C()
{
    m_bStop = true;
}
