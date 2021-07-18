/********************************************************************************
** Form generated from reading UI file 'dashboardtab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARDTAB_H
#define UI_DASHBOARDTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "raceswidget.h"
#include "trackswidget.h"
#include "vehicleswidget.h"

QT_BEGIN_NAMESPACE

class Ui_DashboardTab
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QPushButton *openRaceControlButton;
    QLabel *openRaceControlLabel;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    TracksWidget *tracksWidget;
    RacesWidget *racesWidget;
    VehiclesWidget *vehiclesWidget;

    void setupUi(QWidget *DashboardTab)
    {
        if (DashboardTab->objectName().isEmpty())
            DashboardTab->setObjectName(QString::fromUtf8("DashboardTab"));
        DashboardTab->resize(780, 411);
        verticalLayout = new QVBoxLayout(DashboardTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_2 = new QFrame(DashboardTab);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        openRaceControlButton = new QPushButton(frame_2);
        openRaceControlButton->setObjectName(QString::fromUtf8("openRaceControlButton"));
        QFont font;
        font.setPointSize(15);
        openRaceControlButton->setFont(font);

        gridLayout->addWidget(openRaceControlButton, 0, 1, 1, 1);

        openRaceControlLabel = new QLabel(frame_2);
        openRaceControlLabel->setObjectName(QString::fromUtf8("openRaceControlLabel"));
        openRaceControlLabel->setFont(font);

        gridLayout->addWidget(openRaceControlLabel, 0, 0, 1, 1, Qt::AlignRight);


        verticalLayout->addWidget(frame_2, 0, Qt::AlignHCenter);

        frame = new QFrame(DashboardTab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tracksWidget = new TracksWidget(frame);
        tracksWidget->setObjectName(QString::fromUtf8("tracksWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tracksWidget->sizePolicy().hasHeightForWidth());
        tracksWidget->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(tracksWidget);

        racesWidget = new RacesWidget(frame);
        racesWidget->setObjectName(QString::fromUtf8("racesWidget"));
        sizePolicy.setHeightForWidth(racesWidget->sizePolicy().hasHeightForWidth());
        racesWidget->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(racesWidget);

        vehiclesWidget = new VehiclesWidget(frame);
        vehiclesWidget->setObjectName(QString::fromUtf8("vehiclesWidget"));
        sizePolicy.setHeightForWidth(vehiclesWidget->sizePolicy().hasHeightForWidth());
        vehiclesWidget->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(vehiclesWidget);


        verticalLayout->addWidget(frame);


        retranslateUi(DashboardTab);

        QMetaObject::connectSlotsByName(DashboardTab);
    } // setupUi

    void retranslateUi(QWidget *DashboardTab)
    {
        DashboardTab->setWindowTitle(QApplication::translate("DashboardTab", "Form", nullptr));
        openRaceControlButton->setText(QApplication::translate("DashboardTab", "Open Race Control", nullptr));
        openRaceControlLabel->setText(QApplication::translate("DashboardTab", "Select a Race and a Vehicle ->", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DashboardTab: public Ui_DashboardTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARDTAB_H
