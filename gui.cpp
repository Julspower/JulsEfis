#include "gui.h"
#include <QPainter>
#include <QtMath>
#include <QFrame>
#include <QHBoxLayout>
#include <QTextStream>

Gui::Gui(QWidget *parent) : QWidget(parent)
{
    ADC2Rad = (M_PI * 2 / 1024.0);
    AHSize = (0.8);
    VAngleRad = (vFoV * M_PI / 180);
    tanVAngle = (qTan(VAngleRad)); //Vert FoV->rad and take tan.
    m_dPitch = 0;
    m_dRoll = 0;
    m_dAlt = 0;
    m_dSpeed = 0;
    m_dYaw = 0;
}

void Gui::setYaw(double dVal)
{
    m_dYaw = dVal;
}

void Gui::setPitch(double dVal)
{
    m_dPitch = dVal;
}

void Gui::setRoll(double dVal)
{
    m_dRoll = dVal;
}

void Gui::setSpeed(double dVal)
{
    m_dSpeed = dVal;
}

void Gui::setAlt(double dVal)
{
    m_dAlt = dVal;
}

void Gui::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect geo = geometry();
    int width = geo.width();
    int height = geo.height();
    int rectDim;       // Dimension of the sky and ground rectangles.
    int horizonOffs;		// Horizon centerline offset from top of widget.
    int widgetXCenter, widgetYCenter;
    double pitchAngleRadDisp; //Pitch angle will be displayed up to this value.

    static ticker aspdI(100, 20, 0.7, 0.1, 0.7); //Indicated airspeed ticker.
    static ticker heading(70, 10, 0.8, 0.1, 0.5); //Heading ticker. Last parameter not used.
    static ticker alt(100, 20, 0.7, 0.1, 0.7); // Altitude ticker.
//    static ticker pitch(vFoV*2*0.8, 10, 0.8, 0.1, 0.5);

    static rotatingDial rollArc(11, 2 * M_PI / 3, M_PI / 3 / 2, 0.25, 1.1);

    QPen pen(Qt::white, 2, Qt::SolidLine);
                                          // creates a default pen
    pen.setStyle(Qt::SolidLine);          //http://doc.trolltech.com/4.6/qpen.html
    pen.setWidth(4);
    pen.setBrush(Qt::white);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    painter.setPen(pen);

    QFont newFont = font();
    newFont.setPointSize(14);
    setFont(newFont);

    //Get current widget sizes. Resizing window generates repaint event.
    width = size().width();
    height = size().height();
    //printf ("Width=%4d Height=%4d\n",width,height);

    widgetXCenter = width / 2;
    widgetYCenter = height / 2;

    //rollAngle = efis->AircraftRoll/1024.0*360-180;
    //pitchAngle = efis->AircraftPitch/1024.0*180-90; //Pitch range +-90 deg.
    //pitchAngleRad=pitchAngle*Rad2Deg;
    //pitchAngleRad=efis->AircraftPitch*Rad2Deg;

    pitchAngleRadDisp = m_dPitch * M_PI / 180;
    if(pitchAngleRadDisp > 2 * VAngleRad)
      pitchAngleRadDisp = 2 * VAngleRad;           //Limit drawn pitch angle.
    else if(pitchAngleRadDisp < (-2 * VAngleRad))
      pitchAngleRadDisp = -2 * VAngleRad;

    //TODO: Next two lines should not be necessary:
    painter.setBrush(Qt::black);
    painter.drawRect(0,0,width,height);

    rectDim = static_cast<int>(2 * sqrt(width * width + height * height));
    //Minimum size rectangle that covers
    // the window under all rotation angles depends on the worst case tilt
    // angle(45deg) and also the aspect ratio of the widget(tall and narrow.
    //For these cases a larger rectangle is used (*2 above).

    painter.translate (0.5,0.5);  //Go to center of each pixel...

    painter.save();			    // This is the origin.

    //Go to center of image.
    painter.translate(widgetXCenter, widgetYCenter);

    //Rotate to the current attitude angle:
    //  painter.rotate(360-rollAngle);
    painter.rotate(360 - static_cast<int>(m_dRoll));

    //Translate to center of widget + vertical offset due to pitch:
    horizonOffs = static_cast<int>(static_cast<double>(height) / (2 * tanVAngle) * qTan(pitchAngleRadDisp));
    // TODO should add qRound();

    painter.translate(0, horizonOffs); // How to calculate without hor.dist?

    //Translate to upper left of sky rectangle:
    //  painter.translate (-rectDim/2 , -rectDim/2);
    painter.translate (-rectDim/2, -rectDim);

    //  pen.setBrush(Qt::white);            //This should not be necessary.
    //  painter.setPen(pen);

    QLinearGradient gradient(rectDim/2, 0, rectDim/2, rectDim);
    gradient.setColorAt(1, QColor(117, 117, 252));
    gradient.setColorAt(0, QColor(14, 14, 162));
    painter.fillRect(0, 0, rectDim, rectDim, gradient);   //Draw sky rect.

    //Translate to origin of ground rectangle:
    //  painter.translate (0,rectDim/2);
    painter.translate (0,rectDim);
    gradient.setColorAt(1, QColor(182, 69, 3));
    gradient.setColorAt(0, QColor(179, 98, 16));
    painter.fillRect(0, 0, rectDim, rectDim, gradient);   //Draw Ground
    painter.drawLine(0, 0, rectDim, 0);

    //Finally move to center of horizon, keeping the rotation.
    painter.translate (rectDim/2,-horizonOffs);


    //Draw the roll gage.
    //Roll gage does not follow pitch but may tilt(dynon), or no tilt (Chelton).
    pen.setWidth(1);
    painter.setPen(pen);

    //rollArc.calcParam(height);
    rollArc.calcParam((height<width)?height:width);
    rollArc.paintArcDial(&painter);

    //Draw pitch attitude lines. They tilt and follow pitch angle.
    painter.translate (0, -height / 2);
    //  pitch.Lvalue=pitchAngle; //TODO efis->AircraftPitchAngle;
//    pitch.Lvalue = static_cast<float>(m_dPitch);

//    pitch.calcParam  (height, 0, 40, 100, 50, 30);
                           //lineoffs, linelen, boxoffs, boxlen, textoffs
//    pitch.paintTickerPitch(&painter);


    painter.restore();  //Restore the viewpoint for boresight.
    painter.save();

    //Boresight is at the center with no tilt.
    //Back to the origin and draw the boresight: (small airplane)
    pen.setWidth(4);
    painter.setPen(pen);
    painter.setBrush(Qt::transparent);
    painter.translate (widgetXCenter,widgetYCenter);  //Go to center of widget.
    painter.drawEllipse(-10,-10, 20,20);
    painter.drawLine(-40,0, -15,0);  //Left wing
    painter.drawLine(40,0, 15,0);  //Right wing
    painter.drawLine(0,-15, 0,-35);  //Fin

    //TODO: Draw vertical location Triangle.
    pen.setWidth(2);
    painter.setPen(pen);
    rollArc.paintArcRef(&painter);

    painter.restore();		// Restore painter for tickers:

    //Draw heading ticker at top center
    // airspeed ticker to the left
    // and altitude ticker to the right

    aspdI.Lvalue = static_cast<float>(m_dSpeed);  // Max value would be 300.
    alt.Lvalue = static_cast<float>(m_dAlt);	     // Max value would be 10000.
    heading.Lvalue = static_cast<float>(m_dYaw);
    //  heading.Lvalue=qRound(efis->AircraftHdg*360/1024.0);


    //TODO: if(widgetResized){
    aspdI.calcParam(height, 20, 10, 30, 50, 30);
    alt.calcParam(height, width-20, -10, width-30, -60, width-90);
    heading.calcParam(width,  20,10,30, 50, 30);
                           //lineoffs, linelen, boxoffs, boxlen, textoffs
    //}

    aspdI.paintTickerV(&painter);
    alt.paintTickerV(&painter);
    heading.paintTickerH(&painter);
}


void ticker:: calcParam(int height,int lineoffs, int linelen, int boxoffs, int boxlen, int textoffs)
{
  // Placement and dimensions of ticker:
  Plen = height*PlenRatio;
  Poffs = height*PoffsRatio;
  Pmain = Plen*PmainRatio;
  Displacement=Plen/(float)Lrange*LstepSize;

  //Locations of tick marks and text:
  PlineOffs = lineoffs;
  PlineLen = linelen;
  PsLineLen = PlineLen/2;
  PboxOffs = boxoffs;
  PboxLen = boxlen;
  PtextOffs = textoffs;
}


void ticker::calcPaintValues(void)
// Calculates the numbers to be displayed for current value.
{
  //Value at bottom of ticker.
  LinitVal=qRound(Lvalue-Lrange*PmainRatio);

  // First number to be displayed:
  LinitNum=LstepSize*(int)qRound((LinitVal+LstepSize/2)/(float)LstepSize);
  // How to formulize the round up operation better? (with no magic value 5)

  // Physical distance from bottom of ticker to the first displayed value.
  //  NumOffset= (LinitNum-LinitVal)*Plen/(float)Lrange;
  NumOffset= qRound((LinitNum-Lvalue+Lrange*PmainRatio)*Plen/(float)Lrange);
  // Although Linitval above is the same as the contents of one parantheses,
  //this value here has greater precision and results in smoother scrolling.

  // Where to place the short tick marks:
  if (NumOffset>(Displacement)/2)
    STickOffs=Displacement/2;
  else
    STickOffs= -Displacement/2;

}


void ticker::paintTickerV(QPainter * painter)
// Paints vertical ticker.
{
  int i,j;

  calcPaintValues();

  //painter->drawRect(PlineOffs,Poffs,PlineLen,Plen); //For reference.
  for (i=0;i<LnumTicks;++i){
    LcurVal=LinitNum+i*LstepSize;
    if (LcurVal>=0){
      j=Poffs+Plen-(Displacement*i+NumOffset);
      painter->drawLine(PlineOffs,j,PlineOffs+PlineLen,j); // Normal tick.
      //And display the numerical value:
      painter->drawText(PtextOffs,(j-10), 60, 20,
           //A rectangle... L-margin,alignment,hsize,vsize
           Qt::AlignHCenter | Qt::AlignTop,QString::number(LcurVal));
    }
    //The condition below is a band-aid remedy for displaying the short tick at the end of the ticker (0) correctly. There must be a better way, probably when calculating the rounded values in calcParam.
    if (LcurVal>0 || STickOffs< 0){
      painter->drawLine(PlineOffs,j+STickOffs,PlineOffs+PsLineLen,j+STickOffs);
    }             // Short tick.

  }

  // Finally draw rectangle at the ticker display position
  //  to display actual value:
  painter->drawRect (PboxOffs,(Poffs+Plen-Pmain-12),PboxLen,30);
  painter->drawText(PboxOffs,(Poffs+Plen-Pmain-10),PboxLen,30,
            Qt::AlignHCenter | Qt::AlignTop,QString::number(qRound(Lvalue)));

}

void ticker::paintTickerH(QPainter * painter)
//Paints horizontal ticker.
{
  int i,j;

  calcPaintValues();

  for (i=0;i<LnumTicks;++i){
    LcurVal=LinitNum+i*LstepSize;
    if(LcurVal>360) LcurVal-=360; // Wraparound compass headings.
    if(LcurVal<0) LcurVal+=360;
    j=Poffs+(Displacement*i+NumOffset);
    painter->drawLine(j,PlineOffs,j,PlineOffs+PlineLen);
    painter->drawLine(j-STickOffs,PlineOffs,j-STickOffs,PlineOffs+PsLineLen);
                                                           // Short tick.
    painter->drawText((j-20),PtextOffs, 40, 30,
         //A rectangle... L-margin,alignment,hsize,vsize
         Qt::AlignHCenter | Qt::AlignTop,QString::number(LcurVal));
  }
}


void ticker::paintTickerPitch(QPainter * painter)
// Paints vertical pitch ticker.
{
  int i,j;

  calcPaintValues();

  //painter->drawRect(PlineOffs,Poffs,PlineLen,Plen); //For reference.
  for (i=0;i<LnumTicks;++i){
    LcurVal=LinitNum+i*LstepSize;
    j=Poffs+Plen-(Displacement*i+NumOffset);

    if (LcurVal<=90 && LcurVal>=-90 && LcurVal!=0){
      //      j=Poffs+Plen-(Displacement*i+NumOffset);
      //  x1=height/(2*tanVAngle)*tan(pitchAngleRadDisp); //The offset is not ilinear as in other tickers, but tangential. This should be used instead...
      //Solved by not displaying '0' line for the time being.

      painter->drawLine(PlineOffs-PlineLen,j,PlineOffs+PlineLen,j);
      if (LcurVal>0){
    painter->drawLine(PlineOffs-PlineLen,j,PlineOffs-PlineLen,j+10);
    painter->drawLine(PlineOffs+PlineLen,j,PlineOffs+PlineLen,j+10);
      }else{
    painter->drawLine(PlineOffs-PlineLen,j,PlineOffs-PlineLen,j-10);
    painter->drawLine(PlineOffs+PlineLen,j,PlineOffs+PlineLen,j-10);
      }      // Normal tick.
      //And display the numerical value:
      painter->drawText(PtextOffs,(j-10), 60, 20,
           //A rectangle... L-margin,alignment,hsize,vsize
            Qt::AlignHCenter | Qt::AlignTop,QString::number(abs(LcurVal)));
      painter->drawText(-PtextOffs-60,(j-10), 60, 20,
           //A rectangle... L-margin,alignment,hsize,vsize
            Qt::AlignHCenter | Qt::AlignTop,QString::number(abs(LcurVal)));

    }
    if ((LcurVal<90||STickOffs>0) && (LcurVal>-90||STickOffs<0)){
      painter->drawLine(PlineOffs-PsLineLen,j+STickOffs,PlineOffs+PsLineLen,j+STickOffs);
    }// Short tick.

  }

  // Finally draw rectangle at the ticker display position
  //  to display actual value:
  painter->drawRect (PboxOffs,(Poffs+Plen-Pmain-12),PboxLen,30);
  painter->drawText(PboxOffs,(Poffs+Plen-Pmain-10),PboxLen,30,
            Qt::AlignHCenter | Qt::AlignTop,QString::number(qRound(Lvalue)));

}


//////////////////////////////////////////////////////////////



void rotatingDial::calcParam(int height)
{
  tiltArcRadius=(int)qRound(height*tiltArcRatio);
}


void rotatingDial::paintArcDial(QPainter * painter)
{
  int i,x1,x2,y1,y2;

  //Draw the tilt arc. Starts from 30deg, spans 120deg.
  painter->drawArc (-tiltArcRadius,-tiltArcRadius,tiltArcRadius*2,tiltArcRadius*2,qRound(arcOffset*16), qRound(spreadAngle*16)); //TODO: Use spreadAngle and ArcOffset to calculate.
  //Convert the initialized values to degrees to use here.

  //Draw tick marks: (11 of them)
  for (i=0;i<noOfTicks;++i){
    x1=(tiltArcRadius*tickRatio)*cos((i*tickAngle)+tickOffset);
    y1=(tiltArcRadius*tickRatio)*-sin((i*tickAngle)+tickOffset);
    x2=(tiltArcRadius)*cos((i*tickAngle)+tickOffset);
    y2=(tiltArcRadius)*-sin((i*tickAngle)+tickOffset);
    painter->drawLine(x1,y1,x2,y2);
  }
  //emphasize the vertical:
  painter->drawLine(0,-tiltArcRadius,0,-1*(tiltArcRadius*1.1*(tickRatio)));
  //TODO: Find a more elegant way to do this!

}



void rotatingDial::paintFullDial(QPainter * painter)
{
  int i,x1,x2,y1,y2;
  float cosT,sinT;

  //Draw the circle.
  painter->drawEllipse (-tiltArcRadius,-tiltArcRadius,tiltArcRadius*2,tiltArcRadius*2);

  //Draw tick marks:
  for (i=0;i<noOfTicks;++i){
    cosT=cos((i*tickAngle)+tickOffset);
    sinT=sin((i*tickAngle)+tickOffset);
    x1=(tiltArcRadius*tickRatio)*sinT;
    y1=(tiltArcRadius*tickRatio)*-cosT;
    x2=(tiltArcRadius)*sinT;
    y2=(tiltArcRadius)*-cosT;
    painter->drawLine(x1,y1,x2,y2);
  }
  //emphasize the vertical:
  painter->drawLine(0,-tiltArcRadius,0,-1*(tiltArcRadius*1.05*(tickRatio)));
  //TODO: Find a more elegant way to do this!
}

void rotatingDial::paintNEWS(QPainter * painter, float rotAngle,QFontMetrics * fm)
{
  //int i,x1,x2,y1,y2;
  // float cosT,sinT;



  //Draw tick marks:
  //  for (i=0;i<noOfTicks;++i){
  //  cosT=cos((i*tickAngle)+tickOffset);
  //  sinT=sin((i*tickAngle)+tickOffset);
  //  x1=(tiltArcRadius*tickRatio)*sinT;
  //  y1=(tiltArcRadius*tickRatio)*-cosT;


  painter->save();
  painter->translate (0, -tiltArcRadius);
  painter->rotate(rotAngle);
  painter->translate(-fm->width("N")/2,fm->height()/4); //Font height is constant.
  painter->drawText(0,0, "N");
  painter->restore();


  painter->save();
  painter->translate (tiltArcRadius,0);
  painter->rotate(rotAngle);
  painter->translate(-fm->width("E")/2,fm->height()/4);
  painter->drawText(0,0, "E");
  painter->restore();

  painter->save();
  painter->translate (0, tiltArcRadius);
  painter->rotate(rotAngle);
  painter->translate(-fm->width("S")/2,fm->height()/4);
  painter->drawText(0,0, "S");
  painter->restore();

  painter->save();
  painter->translate (-tiltArcRadius,0);
  painter->rotate(rotAngle);
  painter->translate(-fm->width("W")/2,fm->height()/4); //TODO: calculate in a separate variable...
  painter->drawText(0,0, "W");
  painter->restore();

}




void rotatingDial::paintArcRef(QPainter * painter)
// Draw the small triangle on top of roll gage.
// Must be called from a painter that has been rolled
//  to the correct angle already.

{
  painter->drawLine(0, -tiltArcRadius-10,6,-tiltArcRadius-18);
  painter->drawLine( 6, -tiltArcRadius-18, -6,-tiltArcRadius-18);
  painter->drawLine(-6, -tiltArcRadius-18,  0, -tiltArcRadius-10);
}

