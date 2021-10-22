#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <wiringPiI2C.h>
#include <qthread.h>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    system("gpio mode 1 pwm");
    system("gpio pwm 1 500");

    I2C_thread = new QThread;
    I2C_Worker = new I2C_Comm();
    I2C_Worker->moveToThread(I2C_thread);
    connect(I2C_thread, SIGNAL(started()), I2C_Worker, SLOT(process()));
    connect(I2C_Worker, SIGNAL(finished()), I2C_thread, SLOT(quit()));
    connect(I2C_Worker, SIGNAL(finished()), I2C_Worker, SLOT(deleteLater()));
    connect(I2C_thread, SIGNAL(finished()), I2C_Worker, SLOT(deleteLater()));
    connect(I2C_Worker, SIGNAL(newData()), this, SLOT(updateData()));
    I2C_thread->start();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_btnQuit_clicked()
{
    this->close();
}

void MainWidget::on_vSlider1_sliderReleased()
{
    ;
}

void MainWidget::on_vSlider1_valueChanged(int value)
{
    char szCmd[50];
//    pwmWrite(18, value);
    sprintf(szCmd, "gpio pwm 1 %d", value * 10);
    system(szCmd);
}

void MainWidget::on_btnRead_clicked()
{
    ;
}

void MainWidget::updateData()
{
    ui->lbYawH->setText(QString::number(I2C_Worker->stData.dYaw, 'f', 2));
    ui->lbRollH->setText(QString::number(I2C_Worker->stData.dRoll, 'f', 2));
    ui->lbPitchH->setText(QString::number(I2C_Worker->stData.dPitch, 'f', 2));
    ui->HSI->setPitch(I2C_Worker->stData.dPitch);
    ui->HSI->setRoll(I2C_Worker->stData.dRoll);
    ui->HSI->setYaw(I2C_Worker->stData.dYaw);
    ui->lbTemp->setText(QString::number(I2C_Worker->stData.dTemp, 'f', 2));
    ui->lbPression->setText(QString::number(I2C_Worker->stData.dPressure, 'f', 2));
    this->update();
}
