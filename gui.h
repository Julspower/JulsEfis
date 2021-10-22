#ifndef GUI_H
#define GUI_H

#include <QObject>
#include <QWidget>
#include <QColor>

class Gui : public QWidget
{
    Q_OBJECT
public:
    explicit Gui(QWidget *parent = nullptr);

signals:

protected:
    void paintEvent(QPaintEvent* event);

public slots:
    void setYaw(double);
    void setPitch(double);
    void setRoll(double);
    void setSpeed(double);
    void setAlt(double);

private:
    double m_dYaw;
    double m_dPitch;
    double m_dRoll;
    double m_dSpeed;
    double m_dAlt;

    double ADC2Rad;
    double AHSize;  //Ratio of AH to widget size. Must be less than 1.
    double VAngleRad; //Rad of vertical field of view angle/2
    double tanVAngle; //Tangent of vertical field of view angle/2

};

#define vFoV 20          //Vertical field of view angle/2

class ticker{
private:
  // Physical locations:
  int Poffs;        // Vertical dist from origin to top of ticker (0,0) is top left corner.
  float PoffsRatio; // Ratio of ticker offset to widget height.
  int Plen;	    // Length of ticker.
  float PlenRatio;  // Ratio of ticker length to widget height.
  int Pmain;	    // Distance from value of interest to ticker bottom.
  float PmainRatio; // Ratio of position of main value wrt. ticker length, from ticker bottom.

  //Locations and dimensions of ticks and box.
  int PlineOffs;
  int PlineLen;
  int PsLineLen;    // Length of short tick.
  int PboxOffs;
  int PboxLen;
  int PtextOffs;

  // Logical values:
  int Lrange; 	// Range of values to be displayed.
  int LstepSize;// Increments of printed values.
  int LinitVal;	// The lowest value on ticker should be this
  int LinitNum;	// This is the first number to appear at the bottom of ticker.
  int LnumTicks;// This many ticks on the ticker.
  int LcurVal;	// Current value to be displayed

  // Transformation values:
  int NumOffset;    // Distance from bottom of ticker to first line.
  int Displacement; // distance between each line on ticker.
  int STickOffs;    // distance of first small tick to first displayed value.

  void calcPaintValues(void);

public:
  float Lvalue;	// Value to be displayed

  void calcParam(int height,int lineoffs, int linelen, int boxoffs, int boxlen, int textoffs);
  void paintTickerV (QPainter*); // For drawing vertical tickers.
  void paintTickerH (QPainter*); // For drawing horizontal tickers.
  void paintTickerPitch(QPainter *); //Drawing pitch tickers over horizon.

  ticker(int range, int stepsize, float lenratio, float offsratio, float mainratio)
  {
    //The values here are only those that are fixed for the lifetime of widget.
    Lrange=range;
    LstepSize=stepsize;
    PlenRatio=lenratio;
    PoffsRatio=offsratio;
    PmainRatio=mainratio;
    LnumTicks= qRound(Lrange/(float)LstepSize);
  }
};

class rotatingDial{

  //  float PiBy3;
  float Pi;

public:

  //Definitions for roll arc display.
  //float tickLen=10;
  int noOfTicks;// = 11;   // 11 seems to be the default.
  float tickAngle;// = 2*PiBy3/(float)(noOfTicks-1);
  float tickOffset;//=PiBy3/2;
  //This should be const:
  float tiltArcRatio;//=0.25; //Ratio of tilt arc to widget height.
  int tiltArcRadius;
  float tickRatio;//=1.1;  //Ratio of tick line length to tilt arc radius.
  float spreadAngle;
  float arcOffset;

  //  rotatingDial rollArc(11, 2*PiBy3, PiBy3/2, 0.25, 1.1);
  //numticks, spreadangle, arcoffset, tiltarcratio, tickratio

  rotatingDial(int numticks, float spreadangle, float arcoffset, float tiltarcratio, float tickratio)
  {

    //PiBy3=3.14159265358979323846264338327950288419717/3;
    Pi=3.14159265358979323846264338327950288419717;
    noOfTicks = numticks;
    tickAngle = spreadangle/(float)(noOfTicks-1); //ToDo: Why -1? Bug?
    tickOffset = arcoffset;
    arcOffset = arcoffset*180/Pi;
    spreadAngle = spreadangle*180/Pi;
    tiltArcRatio = tiltarcratio;
    //  tiltArcRadius = tiltarcradius; //This can be left out because
                                   // it is variable.
    tickRatio = tickratio;
  }

  void calcParam(int height);
  void paintArcDial(QPainter * painter);
  void paintArcRef(QPainter * painter);
  void paintFullDial(QPainter * painter);
  void paintNEWS(QPainter * painter, float rotAngle, QFontMetrics * fm);


};//End declaration: class rotatingDial

#endif // GUI_H
