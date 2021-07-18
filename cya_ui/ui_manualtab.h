/********************************************************************************
** Form generated from reading UI file 'manualtab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALTAB_H
#define UI_MANUALTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ManualTab
{
public:
    QGridLayout *gridLayout;
    QFrame *settingsFrame;
    QGridLayout *gridLayout_4;
    QCheckBox *trackTicketsCheckBox;
    QDoubleSpinBox *windAdjustmentSpinBox;
    QLabel *windAdjustmentLabel;
    QLabel *vehicleWeightLabel;
    QSpinBox *vehicleWeightSpinBox;
    QDoubleSpinBox *weightAdjustmentSpinBox;
    QLabel *riderWeightLabel;
    QCheckBox *vehicleTicketsCheckBox;
    QDoubleSpinBox *riderWeightSpinBox;
    QLabel *weightAdjustmentLabel;
    QFrame *frame;
    QGridLayout *gridLayout_5;
    QLabel *currentPressureLabel;
    QLineEdit *temperatureEdit;
    QLineEdit *windSpeedEdit;
    QLabel *vaporPressure;
    QLabel *currentTemperatureLabel;
    QLineEdit *pressureEdit;
    QLineEdit *windDirectionEdit;
    QLabel *currentWindSpeedLabel;
    QLabel *currentHumidityLabel;
    QLabel *densityAltitude;
    QLabel *label;
    QLabel *currentVaporPressureLabel;
    QLineEdit *humidityEdit;
    QLabel *currentWindDirectionLabel;
    QFrame *currentPFrame;
    QGridLayout *gridLayout_3;
    QLabel *sixtyLabel;
    QLabel *thousandH;
    QLabel *eighthH;
    QLabel *sixtyT;
    QLabel *sixtyA;
    QLabel *threeThirtyLabel;
    QLabel *pressureLabel;
    QLabel *threeThirtyA;
    QLabel *sixtyD;
    QLabel *eighthA;
    QLabel *threeThirtyD;
    QLabel *quarterP;
    QLabel *quarterH;
    QLabel *temperatureLabel;
    QLabel *sixtyP;
    QLabel *threeThirtyT;
    QLabel *thousandT;
    QLabel *quarterD;
    QLabel *thousandD;
    QLabel *averageLabel;
    QLabel *quarterT;
    QLabel *thousandP;
    QLabel *threeThirtyH;
    QLabel *eighthD;
    QLabel *eighthT;
    QLabel *thousandLabel;
    QLabel *threeThirtyP;
    QLabel *eighthLabel;
    QLabel *sixtyH;
    QLabel *quarterA;
    QLabel *quarterLabel;
    QLabel *thousandA;
    QLabel *humidityLabel;
    QLabel *eighthP;
    QLabel *densityALabel;
    QLabel *currentPLabel;
    QFrame *graphFrame;
    QGridLayout *gridLayout_6;
    QPushButton *lengthToggleButton;
    QLabel *lengthLabel;
    QLabel *graphLabel;

    void setupUi(QWidget *ManualTab)
    {
        if (ManualTab->objectName().isEmpty())
            ManualTab->setObjectName(QString::fromUtf8("ManualTab"));
        ManualTab->resize(1166, 459);
        gridLayout = new QGridLayout(ManualTab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        settingsFrame = new QFrame(ManualTab);
        settingsFrame->setObjectName(QString::fromUtf8("settingsFrame"));
        settingsFrame->setFrameShape(QFrame::StyledPanel);
        settingsFrame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(settingsFrame);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        trackTicketsCheckBox = new QCheckBox(settingsFrame);
        trackTicketsCheckBox->setObjectName(QString::fromUtf8("trackTicketsCheckBox"));

        gridLayout_4->addWidget(trackTicketsCheckBox, 1, 7, 1, 1);

        windAdjustmentSpinBox = new QDoubleSpinBox(settingsFrame);
        windAdjustmentSpinBox->setObjectName(QString::fromUtf8("windAdjustmentSpinBox"));
        windAdjustmentSpinBox->setDecimals(3);
        windAdjustmentSpinBox->setMaximum(0.990000000000000);
        windAdjustmentSpinBox->setSingleStep(0.001000000000000);

        gridLayout_4->addWidget(windAdjustmentSpinBox, 5, 8, 1, 1);

        windAdjustmentLabel = new QLabel(settingsFrame);
        windAdjustmentLabel->setObjectName(QString::fromUtf8("windAdjustmentLabel"));

        gridLayout_4->addWidget(windAdjustmentLabel, 5, 7, 1, 1, Qt::AlignRight);

        vehicleWeightLabel = new QLabel(settingsFrame);
        vehicleWeightLabel->setObjectName(QString::fromUtf8("vehicleWeightLabel"));

        gridLayout_4->addWidget(vehicleWeightLabel, 8, 7, 1, 1, Qt::AlignRight);

        vehicleWeightSpinBox = new QSpinBox(settingsFrame);
        vehicleWeightSpinBox->setObjectName(QString::fromUtf8("vehicleWeightSpinBox"));
        vehicleWeightSpinBox->setMaximum(10000);

        gridLayout_4->addWidget(vehicleWeightSpinBox, 8, 8, 1, 1);

        weightAdjustmentSpinBox = new QDoubleSpinBox(settingsFrame);
        weightAdjustmentSpinBox->setObjectName(QString::fromUtf8("weightAdjustmentSpinBox"));
        weightAdjustmentSpinBox->setDecimals(3);
        weightAdjustmentSpinBox->setMaximum(0.999000000000000);
        weightAdjustmentSpinBox->setSingleStep(0.001000000000000);

        gridLayout_4->addWidget(weightAdjustmentSpinBox, 6, 8, 1, 1);

        riderWeightLabel = new QLabel(settingsFrame);
        riderWeightLabel->setObjectName(QString::fromUtf8("riderWeightLabel"));

        gridLayout_4->addWidget(riderWeightLabel, 9, 7, 1, 1, Qt::AlignRight);

        vehicleTicketsCheckBox = new QCheckBox(settingsFrame);
        vehicleTicketsCheckBox->setObjectName(QString::fromUtf8("vehicleTicketsCheckBox"));

        gridLayout_4->addWidget(vehicleTicketsCheckBox, 0, 7, 1, 1);

        riderWeightSpinBox = new QDoubleSpinBox(settingsFrame);
        riderWeightSpinBox->setObjectName(QString::fromUtf8("riderWeightSpinBox"));
        riderWeightSpinBox->setDecimals(1);
        riderWeightSpinBox->setMaximum(999.000000000000000);
        riderWeightSpinBox->setSingleStep(0.100000000000000);

        gridLayout_4->addWidget(riderWeightSpinBox, 9, 8, 1, 1);

        weightAdjustmentLabel = new QLabel(settingsFrame);
        weightAdjustmentLabel->setObjectName(QString::fromUtf8("weightAdjustmentLabel"));

        gridLayout_4->addWidget(weightAdjustmentLabel, 6, 7, 1, 1, Qt::AlignRight);


        gridLayout->addWidget(settingsFrame, 1, 3, 1, 1);

        frame = new QFrame(ManualTab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        currentPressureLabel = new QLabel(frame);
        currentPressureLabel->setObjectName(QString::fromUtf8("currentPressureLabel"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        currentPressureLabel->setFont(font);

        gridLayout_5->addWidget(currentPressureLabel, 3, 0, 1, 1, Qt::AlignRight);

        temperatureEdit = new QLineEdit(frame);
        temperatureEdit->setObjectName(QString::fromUtf8("temperatureEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(temperatureEdit->sizePolicy().hasHeightForWidth());
        temperatureEdit->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(temperatureEdit, 0, 1, 1, 1);

        windSpeedEdit = new QLineEdit(frame);
        windSpeedEdit->setObjectName(QString::fromUtf8("windSpeedEdit"));
        sizePolicy.setHeightForWidth(windSpeedEdit->sizePolicy().hasHeightForWidth());
        windSpeedEdit->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(windSpeedEdit, 4, 1, 1, 1);

        vaporPressure = new QLabel(frame);
        vaporPressure->setObjectName(QString::fromUtf8("vaporPressure"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(vaporPressure->sizePolicy().hasHeightForWidth());
        vaporPressure->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(10);
        vaporPressure->setFont(font1);

        gridLayout_5->addWidget(vaporPressure, 6, 1, 1, 1);

        currentTemperatureLabel = new QLabel(frame);
        currentTemperatureLabel->setObjectName(QString::fromUtf8("currentTemperatureLabel"));
        currentTemperatureLabel->setFont(font);

        gridLayout_5->addWidget(currentTemperatureLabel, 0, 0, 1, 1, Qt::AlignRight);

        pressureEdit = new QLineEdit(frame);
        pressureEdit->setObjectName(QString::fromUtf8("pressureEdit"));
        sizePolicy.setHeightForWidth(pressureEdit->sizePolicy().hasHeightForWidth());
        pressureEdit->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(pressureEdit, 3, 1, 1, 1);

        windDirectionEdit = new QLineEdit(frame);
        windDirectionEdit->setObjectName(QString::fromUtf8("windDirectionEdit"));
        sizePolicy.setHeightForWidth(windDirectionEdit->sizePolicy().hasHeightForWidth());
        windDirectionEdit->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(windDirectionEdit, 5, 1, 1, 1);

        currentWindSpeedLabel = new QLabel(frame);
        currentWindSpeedLabel->setObjectName(QString::fromUtf8("currentWindSpeedLabel"));
        currentWindSpeedLabel->setFont(font);

        gridLayout_5->addWidget(currentWindSpeedLabel, 4, 0, 1, 1, Qt::AlignRight);

        currentHumidityLabel = new QLabel(frame);
        currentHumidityLabel->setObjectName(QString::fromUtf8("currentHumidityLabel"));
        currentHumidityLabel->setFont(font);

        gridLayout_5->addWidget(currentHumidityLabel, 2, 0, 1, 1, Qt::AlignRight);

        densityAltitude = new QLabel(frame);
        densityAltitude->setObjectName(QString::fromUtf8("densityAltitude"));
        sizePolicy1.setHeightForWidth(densityAltitude->sizePolicy().hasHeightForWidth());
        densityAltitude->setSizePolicy(sizePolicy1);
        densityAltitude->setFont(font1);

        gridLayout_5->addWidget(densityAltitude, 7, 1, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout_5->addWidget(label, 7, 0, 1, 1, Qt::AlignRight);

        currentVaporPressureLabel = new QLabel(frame);
        currentVaporPressureLabel->setObjectName(QString::fromUtf8("currentVaporPressureLabel"));
        currentVaporPressureLabel->setFont(font);

        gridLayout_5->addWidget(currentVaporPressureLabel, 6, 0, 1, 1, Qt::AlignRight);

        humidityEdit = new QLineEdit(frame);
        humidityEdit->setObjectName(QString::fromUtf8("humidityEdit"));
        sizePolicy.setHeightForWidth(humidityEdit->sizePolicy().hasHeightForWidth());
        humidityEdit->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(humidityEdit, 2, 1, 1, 1);

        currentWindDirectionLabel = new QLabel(frame);
        currentWindDirectionLabel->setObjectName(QString::fromUtf8("currentWindDirectionLabel"));
        currentWindDirectionLabel->setFont(font);

        gridLayout_5->addWidget(currentWindDirectionLabel, 5, 0, 1, 1, Qt::AlignRight);


        gridLayout->addWidget(frame, 1, 1, 1, 1);

        currentPFrame = new QFrame(ManualTab);
        currentPFrame->setObjectName(QString::fromUtf8("currentPFrame"));
        currentPFrame->setFrameShape(QFrame::StyledPanel);
        currentPFrame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(currentPFrame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        sixtyLabel = new QLabel(currentPFrame);
        sixtyLabel->setObjectName(QString::fromUtf8("sixtyLabel"));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        sixtyLabel->setFont(font2);

        gridLayout_3->addWidget(sixtyLabel, 0, 2, 1, 1, Qt::AlignHCenter);

        thousandH = new QLabel(currentPFrame);
        thousandH->setObjectName(QString::fromUtf8("thousandH"));
        QFont font3;
        font3.setPointSize(12);
        thousandH->setFont(font3);

        gridLayout_3->addWidget(thousandH, 4, 5, 1, 1, Qt::AlignHCenter);

        eighthH = new QLabel(currentPFrame);
        eighthH->setObjectName(QString::fromUtf8("eighthH"));
        QFont font4;
        font4.setPointSize(14);
        eighthH->setFont(font4);

        gridLayout_3->addWidget(eighthH, 4, 4, 1, 1, Qt::AlignHCenter);

        sixtyT = new QLabel(currentPFrame);
        sixtyT->setObjectName(QString::fromUtf8("sixtyT"));
        sixtyT->setFont(font3);

        gridLayout_3->addWidget(sixtyT, 3, 2, 1, 1, Qt::AlignHCenter);

        sixtyA = new QLabel(currentPFrame);
        sixtyA->setObjectName(QString::fromUtf8("sixtyA"));
        sixtyA->setFont(font3);

        gridLayout_3->addWidget(sixtyA, 2, 2, 1, 1, Qt::AlignHCenter);

        threeThirtyLabel = new QLabel(currentPFrame);
        threeThirtyLabel->setObjectName(QString::fromUtf8("threeThirtyLabel"));
        threeThirtyLabel->setFont(font2);

        gridLayout_3->addWidget(threeThirtyLabel, 0, 3, 1, 1, Qt::AlignHCenter);

        pressureLabel = new QLabel(currentPFrame);
        pressureLabel->setObjectName(QString::fromUtf8("pressureLabel"));
        pressureLabel->setFont(font4);

        gridLayout_3->addWidget(pressureLabel, 5, 0, 1, 1, Qt::AlignRight);

        threeThirtyA = new QLabel(currentPFrame);
        threeThirtyA->setObjectName(QString::fromUtf8("threeThirtyA"));
        threeThirtyA->setFont(font3);

        gridLayout_3->addWidget(threeThirtyA, 2, 3, 1, 1, Qt::AlignHCenter);

        sixtyD = new QLabel(currentPFrame);
        sixtyD->setObjectName(QString::fromUtf8("sixtyD"));
        sixtyD->setFont(font2);

        gridLayout_3->addWidget(sixtyD, 1, 2, 1, 1, Qt::AlignHCenter);

        eighthA = new QLabel(currentPFrame);
        eighthA->setObjectName(QString::fromUtf8("eighthA"));
        eighthA->setFont(font4);

        gridLayout_3->addWidget(eighthA, 2, 4, 1, 1, Qt::AlignHCenter);

        threeThirtyD = new QLabel(currentPFrame);
        threeThirtyD->setObjectName(QString::fromUtf8("threeThirtyD"));
        threeThirtyD->setFont(font2);

        gridLayout_3->addWidget(threeThirtyD, 1, 3, 1, 1, Qt::AlignHCenter);

        quarterP = new QLabel(currentPFrame);
        quarterP->setObjectName(QString::fromUtf8("quarterP"));
        quarterP->setFont(font4);

        gridLayout_3->addWidget(quarterP, 5, 6, 1, 1, Qt::AlignHCenter);

        quarterH = new QLabel(currentPFrame);
        quarterH->setObjectName(QString::fromUtf8("quarterH"));
        quarterH->setFont(font4);

        gridLayout_3->addWidget(quarterH, 4, 6, 1, 1, Qt::AlignHCenter);

        temperatureLabel = new QLabel(currentPFrame);
        temperatureLabel->setObjectName(QString::fromUtf8("temperatureLabel"));
        temperatureLabel->setFont(font4);

        gridLayout_3->addWidget(temperatureLabel, 3, 0, 1, 1, Qt::AlignRight);

        sixtyP = new QLabel(currentPFrame);
        sixtyP->setObjectName(QString::fromUtf8("sixtyP"));
        sixtyP->setFont(font3);

        gridLayout_3->addWidget(sixtyP, 5, 2, 1, 1, Qt::AlignHCenter);

        threeThirtyT = new QLabel(currentPFrame);
        threeThirtyT->setObjectName(QString::fromUtf8("threeThirtyT"));
        threeThirtyT->setFont(font3);

        gridLayout_3->addWidget(threeThirtyT, 3, 3, 1, 1, Qt::AlignHCenter);

        thousandT = new QLabel(currentPFrame);
        thousandT->setObjectName(QString::fromUtf8("thousandT"));
        thousandT->setFont(font3);

        gridLayout_3->addWidget(thousandT, 3, 5, 1, 1, Qt::AlignHCenter);

        quarterD = new QLabel(currentPFrame);
        quarterD->setObjectName(QString::fromUtf8("quarterD"));
        QFont font5;
        font5.setPointSize(18);
        font5.setBold(true);
        font5.setWeight(75);
        quarterD->setFont(font5);

        gridLayout_3->addWidget(quarterD, 1, 6, 1, 1, Qt::AlignHCenter);

        thousandD = new QLabel(currentPFrame);
        thousandD->setObjectName(QString::fromUtf8("thousandD"));
        thousandD->setFont(font2);

        gridLayout_3->addWidget(thousandD, 1, 5, 1, 1, Qt::AlignHCenter);

        averageLabel = new QLabel(currentPFrame);
        averageLabel->setObjectName(QString::fromUtf8("averageLabel"));
        averageLabel->setFont(font4);

        gridLayout_3->addWidget(averageLabel, 2, 0, 1, 1, Qt::AlignRight);

        quarterT = new QLabel(currentPFrame);
        quarterT->setObjectName(QString::fromUtf8("quarterT"));
        quarterT->setFont(font4);

        gridLayout_3->addWidget(quarterT, 3, 6, 1, 1, Qt::AlignHCenter);

        thousandP = new QLabel(currentPFrame);
        thousandP->setObjectName(QString::fromUtf8("thousandP"));
        thousandP->setFont(font3);

        gridLayout_3->addWidget(thousandP, 5, 5, 1, 1, Qt::AlignHCenter);

        threeThirtyH = new QLabel(currentPFrame);
        threeThirtyH->setObjectName(QString::fromUtf8("threeThirtyH"));
        threeThirtyH->setFont(font3);

        gridLayout_3->addWidget(threeThirtyH, 4, 3, 1, 1, Qt::AlignHCenter);

        eighthD = new QLabel(currentPFrame);
        eighthD->setObjectName(QString::fromUtf8("eighthD"));
        eighthD->setFont(font5);

        gridLayout_3->addWidget(eighthD, 1, 4, 1, 1, Qt::AlignHCenter);

        eighthT = new QLabel(currentPFrame);
        eighthT->setObjectName(QString::fromUtf8("eighthT"));
        eighthT->setFont(font4);

        gridLayout_3->addWidget(eighthT, 3, 4, 1, 1, Qt::AlignHCenter);

        thousandLabel = new QLabel(currentPFrame);
        thousandLabel->setObjectName(QString::fromUtf8("thousandLabel"));
        thousandLabel->setFont(font2);

        gridLayout_3->addWidget(thousandLabel, 0, 5, 1, 1, Qt::AlignHCenter);

        threeThirtyP = new QLabel(currentPFrame);
        threeThirtyP->setObjectName(QString::fromUtf8("threeThirtyP"));
        threeThirtyP->setFont(font3);

        gridLayout_3->addWidget(threeThirtyP, 5, 3, 1, 1, Qt::AlignHCenter);

        eighthLabel = new QLabel(currentPFrame);
        eighthLabel->setObjectName(QString::fromUtf8("eighthLabel"));
        QFont font6;
        font6.setPointSize(16);
        font6.setBold(true);
        font6.setWeight(75);
        eighthLabel->setFont(font6);

        gridLayout_3->addWidget(eighthLabel, 0, 4, 1, 1, Qt::AlignHCenter);

        sixtyH = new QLabel(currentPFrame);
        sixtyH->setObjectName(QString::fromUtf8("sixtyH"));
        sixtyH->setFont(font3);

        gridLayout_3->addWidget(sixtyH, 4, 2, 1, 1, Qt::AlignHCenter);

        quarterA = new QLabel(currentPFrame);
        quarterA->setObjectName(QString::fromUtf8("quarterA"));
        quarterA->setFont(font4);

        gridLayout_3->addWidget(quarterA, 2, 6, 1, 1, Qt::AlignHCenter);

        quarterLabel = new QLabel(currentPFrame);
        quarterLabel->setObjectName(QString::fromUtf8("quarterLabel"));
        quarterLabel->setFont(font6);

        gridLayout_3->addWidget(quarterLabel, 0, 6, 1, 1, Qt::AlignHCenter);

        thousandA = new QLabel(currentPFrame);
        thousandA->setObjectName(QString::fromUtf8("thousandA"));
        thousandA->setFont(font3);

        gridLayout_3->addWidget(thousandA, 2, 5, 1, 1, Qt::AlignHCenter);

        humidityLabel = new QLabel(currentPFrame);
        humidityLabel->setObjectName(QString::fromUtf8("humidityLabel"));
        humidityLabel->setFont(font4);

        gridLayout_3->addWidget(humidityLabel, 4, 0, 1, 1, Qt::AlignRight);

        eighthP = new QLabel(currentPFrame);
        eighthP->setObjectName(QString::fromUtf8("eighthP"));
        eighthP->setFont(font4);

        gridLayout_3->addWidget(eighthP, 5, 4, 1, 1, Qt::AlignHCenter);

        densityALabel = new QLabel(currentPFrame);
        densityALabel->setObjectName(QString::fromUtf8("densityALabel"));
        densityALabel->setFont(font6);

        gridLayout_3->addWidget(densityALabel, 1, 0, 1, 1, Qt::AlignRight);

        currentPLabel = new QLabel(currentPFrame);
        currentPLabel->setObjectName(QString::fromUtf8("currentPLabel"));
        QFont font7;
        font7.setPointSize(20);
        font7.setBold(true);
        font7.setWeight(75);
        currentPLabel->setFont(font7);

        gridLayout_3->addWidget(currentPLabel, 0, 0, 1, 1);


        gridLayout->addWidget(currentPFrame, 1, 2, 1, 1);

        graphFrame = new QFrame(ManualTab);
        graphFrame->setObjectName(QString::fromUtf8("graphFrame"));
        graphFrame->setFrameShape(QFrame::StyledPanel);
        graphFrame->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(graphFrame);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        lengthToggleButton = new QPushButton(graphFrame);
        lengthToggleButton->setObjectName(QString::fromUtf8("lengthToggleButton"));
        sizePolicy.setHeightForWidth(lengthToggleButton->sizePolicy().hasHeightForWidth());
        lengthToggleButton->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(lengthToggleButton, 1, 1, 1, 1);

        lengthLabel = new QLabel(graphFrame);
        lengthLabel->setObjectName(QString::fromUtf8("lengthLabel"));
        QFont font8;
        font8.setPointSize(17);
        lengthLabel->setFont(font8);

        gridLayout_6->addWidget(lengthLabel, 1, 0, 1, 1, Qt::AlignHCenter);

        graphLabel = new QLabel(graphFrame);
        graphLabel->setObjectName(QString::fromUtf8("graphLabel"));
        graphLabel->setFont(font7);

        gridLayout_6->addWidget(graphLabel, 0, 0, 1, 1);


        gridLayout->addWidget(graphFrame, 2, 1, 1, 3);


        retranslateUi(ManualTab);

        QMetaObject::connectSlotsByName(ManualTab);
    } // setupUi

    void retranslateUi(QWidget *ManualTab)
    {
        ManualTab->setWindowTitle(QApplication::translate("ManualTab", "Form", nullptr));
        trackTicketsCheckBox->setText(QApplication::translate("ManualTab", "Use all tickets for this track", nullptr));
        windAdjustmentLabel->setText(QApplication::translate("ManualTab", "1/4mi ET adjustment per 1MPH of wind", nullptr));
        vehicleWeightLabel->setText(QApplication::translate("ManualTab", "Vehicle Weight", nullptr));
        riderWeightLabel->setText(QApplication::translate("ManualTab", "Rider Weight", nullptr));
        vehicleTicketsCheckBox->setText(QApplication::translate("ManualTab", "Use all tickets for this vehicle", nullptr));
        weightAdjustmentLabel->setText(QApplication::translate("ManualTab", "1/4mi ET adjustment per 1lb of weight", nullptr));
        currentPressureLabel->setText(QApplication::translate("ManualTab", "Pressure", nullptr));
        vaporPressure->setText(QApplication::translate("ManualTab", "vPres", nullptr));
        currentTemperatureLabel->setText(QApplication::translate("ManualTab", "Temperature", nullptr));
        currentWindSpeedLabel->setText(QApplication::translate("ManualTab", "Wind Speed", nullptr));
        currentHumidityLabel->setText(QApplication::translate("ManualTab", "Humidity", nullptr));
        densityAltitude->setText(QApplication::translate("ManualTab", "dAlt", nullptr));
        label->setText(QApplication::translate("ManualTab", "Density Altitude", nullptr));
        currentVaporPressureLabel->setText(QApplication::translate("ManualTab", "Vapor Pressure", nullptr));
        currentWindDirectionLabel->setText(QApplication::translate("ManualTab", "Wind Direction", nullptr));
        sixtyLabel->setText(QApplication::translate("ManualTab", "60'", nullptr));
        thousandH->setText(QApplication::translate("ManualTab", "1000'", nullptr));
        eighthH->setText(QApplication::translate("ManualTab", "1/8", nullptr));
        sixtyT->setText(QApplication::translate("ManualTab", "60'", nullptr));
        sixtyA->setText(QApplication::translate("ManualTab", "60'", nullptr));
        threeThirtyLabel->setText(QApplication::translate("ManualTab", "330'", nullptr));
        pressureLabel->setText(QApplication::translate("ManualTab", "By Pressure", nullptr));
        threeThirtyA->setText(QApplication::translate("ManualTab", "330'", nullptr));
        sixtyD->setText(QApplication::translate("ManualTab", "60'", nullptr));
        eighthA->setText(QApplication::translate("ManualTab", "1/8", nullptr));
        threeThirtyD->setText(QApplication::translate("ManualTab", "330'", nullptr));
        quarterP->setText(QApplication::translate("ManualTab", "1/4", nullptr));
        quarterH->setText(QApplication::translate("ManualTab", "1/4", nullptr));
        temperatureLabel->setText(QApplication::translate("ManualTab", "By Temperature", nullptr));
        sixtyP->setText(QApplication::translate("ManualTab", "60'", nullptr));
        threeThirtyT->setText(QApplication::translate("ManualTab", "330'", nullptr));
        thousandT->setText(QApplication::translate("ManualTab", "1000'", nullptr));
        quarterD->setText(QApplication::translate("ManualTab", "1/4", nullptr));
        thousandD->setText(QApplication::translate("ManualTab", "1000'", nullptr));
        averageLabel->setText(QApplication::translate("ManualTab", "By Average Weather", nullptr));
        quarterT->setText(QApplication::translate("ManualTab", "1/4", nullptr));
        thousandP->setText(QApplication::translate("ManualTab", "1000'", nullptr));
        threeThirtyH->setText(QApplication::translate("ManualTab", "330'", nullptr));
        eighthD->setText(QApplication::translate("ManualTab", "1/8", nullptr));
        eighthT->setText(QApplication::translate("ManualTab", "1/8", nullptr));
        thousandLabel->setText(QApplication::translate("ManualTab", "1000'", nullptr));
        threeThirtyP->setText(QApplication::translate("ManualTab", "330'", nullptr));
        eighthLabel->setText(QApplication::translate("ManualTab", "1/8", nullptr));
        sixtyH->setText(QApplication::translate("ManualTab", "60'", nullptr));
        quarterA->setText(QApplication::translate("ManualTab", "1/4", nullptr));
        quarterLabel->setText(QApplication::translate("ManualTab", "1/4", nullptr));
        thousandA->setText(QApplication::translate("ManualTab", "1000'", nullptr));
        humidityLabel->setText(QApplication::translate("ManualTab", "By Humidity", nullptr));
        eighthP->setText(QApplication::translate("ManualTab", "1/8", nullptr));
        densityALabel->setText(QApplication::translate("ManualTab", "By Density Altitude", nullptr));
        currentPLabel->setText(QApplication::translate("ManualTab", "Predicted Run", nullptr));
        lengthToggleButton->setText(QApplication::translate("ManualTab", "Show 1/8", nullptr));
        lengthLabel->setText(QApplication::translate("ManualTab", "1/4 Mile Predictions", nullptr));
        graphLabel->setText(QApplication::translate("ManualTab", "DA Prediction Graph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ManualTab: public Ui_ManualTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALTAB_H
