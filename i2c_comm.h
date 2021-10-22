#ifndef I2C_COMM_H
#define I2C_COMM_H

#include <QObject>
#include <QtCore>
#include "EM7180_Master.h"

class I2C_Comm : public QObject
{
    Q_OBJECT

typedef struct
{
    double dYaw;
    double dPitch;
    double dRoll;
    double dTemp;
    double dPressure;
}DataStruct;

public:
    I2C_Comm();
    ~I2C_Comm();

    DataStruct stData;

public slots:
    void process();
    void StopI2C();

signals:
    void finished();
    void newData();

private slots:

private:
    bool m_bStop;
    EM7180_Master *m_EM7180;
};

#endif // I2C_COMM_H
