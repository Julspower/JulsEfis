#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <wiringPi.h>
#include <softPwm.h>
#include <QtCore>
#include "i2c_comm.h"
#include <qthread.h>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_btnQuit_clicked();

    void on_vSlider1_sliderReleased();

    void on_vSlider1_valueChanged(int value);

    void on_btnRead_clicked();

    void updateData();

private:
    Ui::MainWidget *ui;
    QThread* I2C_thread;
    I2C_Comm* I2C_Worker;
};

#endif // MAINWIDGET_H
