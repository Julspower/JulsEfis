/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "gui.h"

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QPushButton *btnQuit;
    QSlider *vSlider1;
    QPushButton *btnRead;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *lbPression;
    QLabel *lbYaw_5;
    QLabel *lbYawH;
    QLabel *lbYaw_6;
    QLabel *lbYaw_9;
    QLabel *lbYaw_8;
    QLabel *lbTemp;
    QLabel *lbPitchH;
    QLabel *lbYaw_7;
    QLabel *lbRollH;
    Gui *HSI;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QStringLiteral("MainWidget"));
        MainWidget->resize(1200, 800);
        btnQuit = new QPushButton(MainWidget);
        btnQuit->setObjectName(QStringLiteral("btnQuit"));
        btnQuit->setGeometry(QRect(70, 550, 89, 25));
        vSlider1 = new QSlider(MainWidget);
        vSlider1->setObjectName(QStringLiteral("vSlider1"));
        vSlider1->setGeometry(QRect(150, 90, 16, 160));
        vSlider1->setMaximum(100);
        vSlider1->setValue(75);
        vSlider1->setOrientation(Qt::Vertical);
        btnRead = new QPushButton(MainWidget);
        btnRead->setObjectName(QStringLiteral("btnRead"));
        btnRead->setGeometry(QRect(70, 490, 89, 25));
        frame = new QFrame(MainWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(30, 340, 191, 115));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lbPression = new QLabel(frame);
        lbPression->setObjectName(QStringLiteral("lbPression"));

        gridLayout->addWidget(lbPression, 6, 1, 1, 1);

        lbYaw_5 = new QLabel(frame);
        lbYaw_5->setObjectName(QStringLiteral("lbYaw_5"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbYaw_5->sizePolicy().hasHeightForWidth());
        lbYaw_5->setSizePolicy(sizePolicy);
        lbYaw_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lbYaw_5, 0, 0, 1, 1);

        lbYawH = new QLabel(frame);
        lbYawH->setObjectName(QStringLiteral("lbYawH"));

        gridLayout->addWidget(lbYawH, 0, 1, 1, 1);

        lbYaw_6 = new QLabel(frame);
        lbYaw_6->setObjectName(QStringLiteral("lbYaw_6"));
        sizePolicy.setHeightForWidth(lbYaw_6->sizePolicy().hasHeightForWidth());
        lbYaw_6->setSizePolicy(sizePolicy);
        lbYaw_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lbYaw_6, 1, 0, 1, 1);

        lbYaw_9 = new QLabel(frame);
        lbYaw_9->setObjectName(QStringLiteral("lbYaw_9"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbYaw_9->sizePolicy().hasHeightForWidth());
        lbYaw_9->setSizePolicy(sizePolicy1);
        lbYaw_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lbYaw_9, 5, 0, 1, 1);

        lbYaw_8 = new QLabel(frame);
        lbYaw_8->setObjectName(QStringLiteral("lbYaw_8"));
        sizePolicy.setHeightForWidth(lbYaw_8->sizePolicy().hasHeightForWidth());
        lbYaw_8->setSizePolicy(sizePolicy);
        lbYaw_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lbYaw_8, 6, 0, 1, 1);

        lbTemp = new QLabel(frame);
        lbTemp->setObjectName(QStringLiteral("lbTemp"));

        gridLayout->addWidget(lbTemp, 5, 1, 1, 1);

        lbPitchH = new QLabel(frame);
        lbPitchH->setObjectName(QStringLiteral("lbPitchH"));

        gridLayout->addWidget(lbPitchH, 1, 1, 1, 1);

        lbYaw_7 = new QLabel(frame);
        lbYaw_7->setObjectName(QStringLiteral("lbYaw_7"));
        sizePolicy.setHeightForWidth(lbYaw_7->sizePolicy().hasHeightForWidth());
        lbYaw_7->setSizePolicy(sizePolicy);
        lbYaw_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lbYaw_7, 2, 0, 1, 1);

        lbRollH = new QLabel(frame);
        lbRollH->setObjectName(QStringLiteral("lbRollH"));

        gridLayout->addWidget(lbRollH, 2, 1, 1, 1);

        HSI = new Gui(MainWidget);
        HSI->setObjectName(QStringLiteral("HSI"));
        HSI->setGeometry(QRect(409, 10, 781, 781));

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "Form", nullptr));
        btnQuit->setText(QApplication::translate("MainWidget", "Quit", nullptr));
        btnRead->setText(QApplication::translate("MainWidget", "Read", nullptr));
        lbPression->setText(QApplication::translate("MainWidget", "TextLabel", nullptr));
        lbYaw_5->setText(QApplication::translate("MainWidget", "Yaw:", nullptr));
        lbYawH->setText(QApplication::translate("MainWidget", "TextLabel", nullptr));
        lbYaw_6->setText(QApplication::translate("MainWidget", "Pitch:", nullptr));
        lbYaw_9->setText(QApplication::translate("MainWidget", "Temp\303\251rature:", nullptr));
        lbYaw_8->setText(QApplication::translate("MainWidget", "Pression:", nullptr));
        lbTemp->setText(QApplication::translate("MainWidget", "TextLabel", nullptr));
        lbPitchH->setText(QApplication::translate("MainWidget", "TextLabel", nullptr));
        lbYaw_7->setText(QApplication::translate("MainWidget", "Roll:", nullptr));
        lbRollH->setText(QApplication::translate("MainWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
