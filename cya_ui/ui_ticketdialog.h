/********************************************************************************
** Form generated from reading UI file 'ticketdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TICKETDIALOG_H
#define UI_TICKETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_TicketDialog
{
public:
    QGridLayout *gridLayout;
    QFrame *weatherFrame;
    QGridLayout *gridLayout_4;
    QLabel *pressure;
    QLabel *windSpeed;
    QLabel *currentWindDirectionLabel;
    QLabel *currentPressureLabel;
    QLabel *temperature;
    QLabel *vaporPressure;
    QLabel *currentDewPointLabel;
    QLabel *currentDensityALabel;
    QLabel *densityAltitude;
    QLabel *windDirection;
    QLabel *windGust;
    QLabel *humidity;
    QLabel *currentTemperatureLabel;
    QLabel *currentWindGustLabel;
    QLabel *currentHumidityLabel;
    QLabel *currentWindSpeedLabel;
    QLabel *dewPoint;
    QLabel *currentWindGustDirLabel;
    QLabel *windGustDir;
    QLabel *currentVaporPressureLabel;
    QFrame *predictionFrame;
    QGridLayout *gridLayout_3;
    QCheckBox *vehicleTicketsCheckBox;
    QDoubleSpinBox *weightAdjustmentSpinBox;
    QDoubleSpinBox *windAdjustmentSpinBox;
    QCheckBox *trackTicketsCheckBox;
    QLabel *windAdjustmentLabel;
    QLabel *weightAdjustmentLabel;
    QDialogButtonBox *buttonBox;
    QPlainTextEdit *notesEdit;
    QLabel *notesLabel;
    QFrame *clockFrame;
    QGridLayout *gridLayout_2;
    QLabel *thousandT;
    QLabel *thousandP;
    QLabel *laneLabel;
    QLabel *eighthA;
    QLineEdit *eighthMPHEdit;
    QLabel *thousandLable;
    QLabel *threeThirtyP;
    QLabel *threeThirtyLabel;
    QLabel *label_4;
    QLineEdit *eighthEdit;
    QLabel *temperatureLabel;
    QLabel *sixtyD;
    QLabel *quarterLable;
    QComboBox *laneComboBox;
    QLabel *threeThirtyD;
    QLineEdit *thousandEdit;
    QLabel *densityALabel;
    QLineEdit *quarterMPHEdit;
    QLabel *humidityLabel;
    QLabel *quarterP;
    QLabel *splitET;
    QLabel *averageLabel;
    QLabel *eighthH;
    QCheckBox *eighthGoodCheckBox;
    QLabel *eighthD;
    QLabel *reactionLabel;
    QLabel *thousandH;
    QLabel *threeThirtyH;
    QLineEdit *reactionEdit;
    QCheckBox *threeThirtyGoodCheckBox;
    QLabel *quarterD;
    QLabel *eighthMPHLabel;
    QLabel *label_3;
    QLabel *predictedTimesLabel;
    QLabel *quarterA;
    QPushButton *showPredictionsButton;
    QLabel *splitTE;
    QLabel *threeThirtyT;
    QLabel *sixtyLabel;
    QLabel *threeThirtyA;
    QLabel *quarterMPHLable;
    QLabel *sixtyT;
    QCheckBox *quarterGoodCheckBox;
    QLabel *sixtyA;
    QLabel *sixtyP;
    QLabel *quarterT;
    QLabel *label;
    QCheckBox *thousandGoodCheckBox;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_2;
    QLabel *sixtyH;
    QLabel *eighthLabel;
    QLabel *splitTQ;
    QLabel *pressureLabel;
    QLineEdit *sixtyEdit;
    QLabel *quarterH;
    QLabel *thousandA;
    QLabel *eighthT;
    QLabel *eighthP;
    QLineEdit *threeThirtyEdit;
    QLineEdit *quarterEdit;
    QLabel *splitST;
    QCheckBox *sixtyGoodCheckBox;
    QLabel *thousandD;
    QLabel *label_8;
    QLabel *splitMPH;
    QFrame *extraInfoFrame;
    QGridLayout *gridLayout_5;
    QLineEdit *delayEdit;
    QLabel *dialLabel;
    QLabel *delayLabel;
    QLineEdit *dialEdit;
    QDoubleSpinBox *riderWeightSpinBox;
    QLabel *riderWeightLabel;
    QSpinBox *vehicleWeightSpinBox;
    QLabel *vehicleWeightLabel;

    void setupUi(QDialog *TicketDialog)
    {
        if (TicketDialog->objectName().isEmpty())
            TicketDialog->setObjectName(QString::fromUtf8("TicketDialog"));
        TicketDialog->resize(1156, 700);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TicketDialog->sizePolicy().hasHeightForWidth());
        TicketDialog->setSizePolicy(sizePolicy);
        TicketDialog->setMaximumSize(QSize(16777215, 700));
        gridLayout = new QGridLayout(TicketDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        weatherFrame = new QFrame(TicketDialog);
        weatherFrame->setObjectName(QString::fromUtf8("weatherFrame"));
        weatherFrame->setFrameShape(QFrame::NoFrame);
        weatherFrame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(weatherFrame);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pressure = new QLabel(weatherFrame);
        pressure->setObjectName(QString::fromUtf8("pressure"));

        gridLayout_4->addWidget(pressure, 2, 2, 1, 1);

        windSpeed = new QLabel(weatherFrame);
        windSpeed->setObjectName(QString::fromUtf8("windSpeed"));

        gridLayout_4->addWidget(windSpeed, 6, 2, 1, 1);

        currentWindDirectionLabel = new QLabel(weatherFrame);
        currentWindDirectionLabel->setObjectName(QString::fromUtf8("currentWindDirectionLabel"));
        QFont font;
        font.setPointSize(13);
        currentWindDirectionLabel->setFont(font);

        gridLayout_4->addWidget(currentWindDirectionLabel, 7, 0, 1, 1, Qt::AlignRight);

        currentPressureLabel = new QLabel(weatherFrame);
        currentPressureLabel->setObjectName(QString::fromUtf8("currentPressureLabel"));
        currentPressureLabel->setFont(font);

        gridLayout_4->addWidget(currentPressureLabel, 2, 0, 1, 1, Qt::AlignRight);

        temperature = new QLabel(weatherFrame);
        temperature->setObjectName(QString::fromUtf8("temperature"));

        gridLayout_4->addWidget(temperature, 0, 2, 1, 1);

        vaporPressure = new QLabel(weatherFrame);
        vaporPressure->setObjectName(QString::fromUtf8("vaporPressure"));

        gridLayout_4->addWidget(vaporPressure, 3, 2, 1, 1);

        currentDewPointLabel = new QLabel(weatherFrame);
        currentDewPointLabel->setObjectName(QString::fromUtf8("currentDewPointLabel"));
        currentDewPointLabel->setFont(font);

        gridLayout_4->addWidget(currentDewPointLabel, 4, 0, 1, 1, Qt::AlignRight);

        currentDensityALabel = new QLabel(weatherFrame);
        currentDensityALabel->setObjectName(QString::fromUtf8("currentDensityALabel"));
        currentDensityALabel->setFont(font);

        gridLayout_4->addWidget(currentDensityALabel, 5, 0, 1, 1, Qt::AlignRight);

        densityAltitude = new QLabel(weatherFrame);
        densityAltitude->setObjectName(QString::fromUtf8("densityAltitude"));

        gridLayout_4->addWidget(densityAltitude, 5, 2, 1, 1);

        windDirection = new QLabel(weatherFrame);
        windDirection->setObjectName(QString::fromUtf8("windDirection"));

        gridLayout_4->addWidget(windDirection, 7, 2, 1, 1);

        windGust = new QLabel(weatherFrame);
        windGust->setObjectName(QString::fromUtf8("windGust"));

        gridLayout_4->addWidget(windGust, 8, 2, 1, 1);

        humidity = new QLabel(weatherFrame);
        humidity->setObjectName(QString::fromUtf8("humidity"));

        gridLayout_4->addWidget(humidity, 1, 2, 1, 1);

        currentTemperatureLabel = new QLabel(weatherFrame);
        currentTemperatureLabel->setObjectName(QString::fromUtf8("currentTemperatureLabel"));
        currentTemperatureLabel->setFont(font);

        gridLayout_4->addWidget(currentTemperatureLabel, 0, 0, 1, 1, Qt::AlignRight);

        currentWindGustLabel = new QLabel(weatherFrame);
        currentWindGustLabel->setObjectName(QString::fromUtf8("currentWindGustLabel"));
        currentWindGustLabel->setFont(font);

        gridLayout_4->addWidget(currentWindGustLabel, 8, 0, 1, 1, Qt::AlignRight);

        currentHumidityLabel = new QLabel(weatherFrame);
        currentHumidityLabel->setObjectName(QString::fromUtf8("currentHumidityLabel"));
        sizePolicy.setHeightForWidth(currentHumidityLabel->sizePolicy().hasHeightForWidth());
        currentHumidityLabel->setSizePolicy(sizePolicy);
        currentHumidityLabel->setFont(font);

        gridLayout_4->addWidget(currentHumidityLabel, 1, 0, 1, 1, Qt::AlignRight);

        currentWindSpeedLabel = new QLabel(weatherFrame);
        currentWindSpeedLabel->setObjectName(QString::fromUtf8("currentWindSpeedLabel"));
        currentWindSpeedLabel->setFont(font);

        gridLayout_4->addWidget(currentWindSpeedLabel, 6, 0, 1, 1, Qt::AlignRight);

        dewPoint = new QLabel(weatherFrame);
        dewPoint->setObjectName(QString::fromUtf8("dewPoint"));

        gridLayout_4->addWidget(dewPoint, 4, 2, 1, 1);

        currentWindGustDirLabel = new QLabel(weatherFrame);
        currentWindGustDirLabel->setObjectName(QString::fromUtf8("currentWindGustDirLabel"));
        currentWindGustDirLabel->setFont(font);

        gridLayout_4->addWidget(currentWindGustDirLabel, 9, 0, 1, 1, Qt::AlignRight);

        windGustDir = new QLabel(weatherFrame);
        windGustDir->setObjectName(QString::fromUtf8("windGustDir"));
        windGustDir->setFont(font);

        gridLayout_4->addWidget(windGustDir, 9, 2, 1, 1);

        currentVaporPressureLabel = new QLabel(weatherFrame);
        currentVaporPressureLabel->setObjectName(QString::fromUtf8("currentVaporPressureLabel"));
        currentVaporPressureLabel->setFont(font);

        gridLayout_4->addWidget(currentVaporPressureLabel, 3, 0, 1, 1);


        gridLayout->addWidget(weatherFrame, 6, 13, 10, 1);

        predictionFrame = new QFrame(TicketDialog);
        predictionFrame->setObjectName(QString::fromUtf8("predictionFrame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(predictionFrame->sizePolicy().hasHeightForWidth());
        predictionFrame->setSizePolicy(sizePolicy1);
        predictionFrame->setFrameShape(QFrame::NoFrame);
        predictionFrame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(predictionFrame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        vehicleTicketsCheckBox = new QCheckBox(predictionFrame);
        vehicleTicketsCheckBox->setObjectName(QString::fromUtf8("vehicleTicketsCheckBox"));
        vehicleTicketsCheckBox->setFont(font);

        gridLayout_3->addWidget(vehicleTicketsCheckBox, 3, 2, 1, 1);

        weightAdjustmentSpinBox = new QDoubleSpinBox(predictionFrame);
        weightAdjustmentSpinBox->setObjectName(QString::fromUtf8("weightAdjustmentSpinBox"));
        weightAdjustmentSpinBox->setFont(font);
        weightAdjustmentSpinBox->setDecimals(3);
        weightAdjustmentSpinBox->setMaximum(0.999000000000000);
        weightAdjustmentSpinBox->setSingleStep(0.001000000000000);

        gridLayout_3->addWidget(weightAdjustmentSpinBox, 3, 1, 1, 1);

        windAdjustmentSpinBox = new QDoubleSpinBox(predictionFrame);
        windAdjustmentSpinBox->setObjectName(QString::fromUtf8("windAdjustmentSpinBox"));
        windAdjustmentSpinBox->setFont(font);
        windAdjustmentSpinBox->setDecimals(3);
        windAdjustmentSpinBox->setMaximum(0.999000000000000);
        windAdjustmentSpinBox->setSingleStep(0.001000000000000);

        gridLayout_3->addWidget(windAdjustmentSpinBox, 1, 1, 1, 1);

        trackTicketsCheckBox = new QCheckBox(predictionFrame);
        trackTicketsCheckBox->setObjectName(QString::fromUtf8("trackTicketsCheckBox"));
        trackTicketsCheckBox->setFont(font);

        gridLayout_3->addWidget(trackTicketsCheckBox, 1, 2, 1, 1);

        windAdjustmentLabel = new QLabel(predictionFrame);
        windAdjustmentLabel->setObjectName(QString::fromUtf8("windAdjustmentLabel"));
        windAdjustmentLabel->setFont(font);

        gridLayout_3->addWidget(windAdjustmentLabel, 1, 0, 1, 1);

        weightAdjustmentLabel = new QLabel(predictionFrame);
        weightAdjustmentLabel->setObjectName(QString::fromUtf8("weightAdjustmentLabel"));
        weightAdjustmentLabel->setFont(font);

        gridLayout_3->addWidget(weightAdjustmentLabel, 3, 0, 1, 1);


        gridLayout->addWidget(predictionFrame, 16, 0, 1, 9);

        buttonBox = new QDialogButtonBox(TicketDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setFont(font);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 16, 13, 1, 1);

        notesEdit = new QPlainTextEdit(TicketDialog);
        notesEdit->setObjectName(QString::fromUtf8("notesEdit"));
        notesEdit->setFont(font);

        gridLayout->addWidget(notesEdit, 9, 11, 8, 2);

        notesLabel = new QLabel(TicketDialog);
        notesLabel->setObjectName(QString::fromUtf8("notesLabel"));
        notesLabel->setFont(font);

        gridLayout->addWidget(notesLabel, 8, 11, 1, 1, Qt::AlignHCenter);

        clockFrame = new QFrame(TicketDialog);
        clockFrame->setObjectName(QString::fromUtf8("clockFrame"));
        clockFrame->setFrameShape(QFrame::NoFrame);
        clockFrame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(clockFrame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        thousandT = new QLabel(clockFrame);
        thousandT->setObjectName(QString::fromUtf8("thousandT"));
        thousandT->setFont(font);

        gridLayout_2->addWidget(thousandT, 15, 5, 1, 1);

        thousandP = new QLabel(clockFrame);
        thousandP->setObjectName(QString::fromUtf8("thousandP"));
        thousandP->setFont(font);

        gridLayout_2->addWidget(thousandP, 15, 7, 1, 1);

        laneLabel = new QLabel(clockFrame);
        laneLabel->setObjectName(QString::fromUtf8("laneLabel"));
        laneLabel->setFont(font);

        gridLayout_2->addWidget(laneLabel, 1, 0, 1, 1, Qt::AlignRight);

        eighthA = new QLabel(clockFrame);
        eighthA->setObjectName(QString::fromUtf8("eighthA"));
        QFont font1;
        font1.setPointSize(20);
        eighthA->setFont(font1);

        gridLayout_2->addWidget(eighthA, 12, 4, 1, 1);

        eighthMPHEdit = new QLineEdit(clockFrame);
        eighthMPHEdit->setObjectName(QString::fromUtf8("eighthMPHEdit"));
        sizePolicy1.setHeightForWidth(eighthMPHEdit->sizePolicy().hasHeightForWidth());
        eighthMPHEdit->setSizePolicy(sizePolicy1);
        eighthMPHEdit->setFont(font);

        gridLayout_2->addWidget(eighthMPHEdit, 13, 1, 1, 1);

        thousandLable = new QLabel(clockFrame);
        thousandLable->setObjectName(QString::fromUtf8("thousandLable"));
        thousandLable->setFont(font);
        thousandLable->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(thousandLable, 15, 0, 1, 1);

        threeThirtyP = new QLabel(clockFrame);
        threeThirtyP->setObjectName(QString::fromUtf8("threeThirtyP"));
        threeThirtyP->setFont(font);

        gridLayout_2->addWidget(threeThirtyP, 10, 7, 1, 1);

        threeThirtyLabel = new QLabel(clockFrame);
        threeThirtyLabel->setObjectName(QString::fromUtf8("threeThirtyLabel"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Cantarell"));
        font2.setPointSize(13);
        threeThirtyLabel->setFont(font2);
        threeThirtyLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(threeThirtyLabel, 10, 0, 1, 1);

        label_4 = new QLabel(clockFrame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 14, 0, 1, 1, Qt::AlignRight);

        eighthEdit = new QLineEdit(clockFrame);
        eighthEdit->setObjectName(QString::fromUtf8("eighthEdit"));
        sizePolicy1.setHeightForWidth(eighthEdit->sizePolicy().hasHeightForWidth());
        eighthEdit->setSizePolicy(sizePolicy1);
        eighthEdit->setFont(font1);

        gridLayout_2->addWidget(eighthEdit, 12, 1, 1, 1);

        temperatureLabel = new QLabel(clockFrame);
        temperatureLabel->setObjectName(QString::fromUtf8("temperatureLabel"));
        temperatureLabel->setFont(font);

        gridLayout_2->addWidget(temperatureLabel, 6, 5, 1, 1);

        sixtyD = new QLabel(clockFrame);
        sixtyD->setObjectName(QString::fromUtf8("sixtyD"));
        sixtyD->setFont(font);

        gridLayout_2->addWidget(sixtyD, 8, 3, 1, 1);

        quarterLable = new QLabel(clockFrame);
        quarterLable->setObjectName(QString::fromUtf8("quarterLable"));
        quarterLable->setFont(font1);
        quarterLable->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(quarterLable, 17, 0, 1, 1);

        laneComboBox = new QComboBox(clockFrame);
        laneComboBox->setObjectName(QString::fromUtf8("laneComboBox"));
        sizePolicy1.setHeightForWidth(laneComboBox->sizePolicy().hasHeightForWidth());
        laneComboBox->setSizePolicy(sizePolicy1);
        laneComboBox->setFont(font);
        laneComboBox->setMaxVisibleItems(2);

        gridLayout_2->addWidget(laneComboBox, 1, 1, 1, 1);

        threeThirtyD = new QLabel(clockFrame);
        threeThirtyD->setObjectName(QString::fromUtf8("threeThirtyD"));
        threeThirtyD->setFont(font);

        gridLayout_2->addWidget(threeThirtyD, 10, 3, 1, 1);

        thousandEdit = new QLineEdit(clockFrame);
        thousandEdit->setObjectName(QString::fromUtf8("thousandEdit"));
        sizePolicy1.setHeightForWidth(thousandEdit->sizePolicy().hasHeightForWidth());
        thousandEdit->setSizePolicy(sizePolicy1);
        thousandEdit->setFont(font);

        gridLayout_2->addWidget(thousandEdit, 15, 1, 1, 1);

        densityALabel = new QLabel(clockFrame);
        densityALabel->setObjectName(QString::fromUtf8("densityALabel"));
        densityALabel->setFont(font);

        gridLayout_2->addWidget(densityALabel, 6, 3, 1, 1);

        quarterMPHEdit = new QLineEdit(clockFrame);
        quarterMPHEdit->setObjectName(QString::fromUtf8("quarterMPHEdit"));
        sizePolicy1.setHeightForWidth(quarterMPHEdit->sizePolicy().hasHeightForWidth());
        quarterMPHEdit->setSizePolicy(sizePolicy1);
        quarterMPHEdit->setFont(font);

        gridLayout_2->addWidget(quarterMPHEdit, 18, 1, 1, 1);

        humidityLabel = new QLabel(clockFrame);
        humidityLabel->setObjectName(QString::fromUtf8("humidityLabel"));
        humidityLabel->setFont(font);

        gridLayout_2->addWidget(humidityLabel, 6, 6, 1, 1);

        quarterP = new QLabel(clockFrame);
        quarterP->setObjectName(QString::fromUtf8("quarterP"));
        quarterP->setFont(font1);

        gridLayout_2->addWidget(quarterP, 17, 7, 1, 1);

        splitET = new QLabel(clockFrame);
        splitET->setObjectName(QString::fromUtf8("splitET"));

        gridLayout_2->addWidget(splitET, 14, 1, 1, 1);

        averageLabel = new QLabel(clockFrame);
        averageLabel->setObjectName(QString::fromUtf8("averageLabel"));
        averageLabel->setFont(font);

        gridLayout_2->addWidget(averageLabel, 6, 4, 1, 1);

        eighthH = new QLabel(clockFrame);
        eighthH->setObjectName(QString::fromUtf8("eighthH"));
        eighthH->setFont(font1);

        gridLayout_2->addWidget(eighthH, 12, 6, 1, 1);

        eighthGoodCheckBox = new QCheckBox(clockFrame);
        eighthGoodCheckBox->setObjectName(QString::fromUtf8("eighthGoodCheckBox"));
        eighthGoodCheckBox->setFont(font);
        eighthGoodCheckBox->setChecked(false);

        gridLayout_2->addWidget(eighthGoodCheckBox, 12, 2, 1, 1);

        eighthD = new QLabel(clockFrame);
        eighthD->setObjectName(QString::fromUtf8("eighthD"));
        eighthD->setFont(font1);

        gridLayout_2->addWidget(eighthD, 12, 3, 1, 1);

        reactionLabel = new QLabel(clockFrame);
        reactionLabel->setObjectName(QString::fromUtf8("reactionLabel"));
        reactionLabel->setFont(font);

        gridLayout_2->addWidget(reactionLabel, 6, 0, 1, 1);

        thousandH = new QLabel(clockFrame);
        thousandH->setObjectName(QString::fromUtf8("thousandH"));
        thousandH->setFont(font);

        gridLayout_2->addWidget(thousandH, 15, 6, 1, 1);

        threeThirtyH = new QLabel(clockFrame);
        threeThirtyH->setObjectName(QString::fromUtf8("threeThirtyH"));
        threeThirtyH->setFont(font);

        gridLayout_2->addWidget(threeThirtyH, 10, 6, 1, 1);

        reactionEdit = new QLineEdit(clockFrame);
        reactionEdit->setObjectName(QString::fromUtf8("reactionEdit"));
        sizePolicy1.setHeightForWidth(reactionEdit->sizePolicy().hasHeightForWidth());
        reactionEdit->setSizePolicy(sizePolicy1);
        reactionEdit->setFont(font);

        gridLayout_2->addWidget(reactionEdit, 6, 1, 1, 1);

        threeThirtyGoodCheckBox = new QCheckBox(clockFrame);
        threeThirtyGoodCheckBox->setObjectName(QString::fromUtf8("threeThirtyGoodCheckBox"));
        threeThirtyGoodCheckBox->setFont(font);
        threeThirtyGoodCheckBox->setChecked(false);

        gridLayout_2->addWidget(threeThirtyGoodCheckBox, 10, 2, 1, 1);

        quarterD = new QLabel(clockFrame);
        quarterD->setObjectName(QString::fromUtf8("quarterD"));
        quarterD->setFont(font1);

        gridLayout_2->addWidget(quarterD, 17, 3, 1, 1);

        eighthMPHLabel = new QLabel(clockFrame);
        eighthMPHLabel->setObjectName(QString::fromUtf8("eighthMPHLabel"));
        eighthMPHLabel->setFont(font);
        eighthMPHLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(eighthMPHLabel, 13, 0, 1, 1);

        label_3 = new QLabel(clockFrame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 16, 0, 1, 1, Qt::AlignRight);

        predictedTimesLabel = new QLabel(clockFrame);
        predictedTimesLabel->setObjectName(QString::fromUtf8("predictedTimesLabel"));
        predictedTimesLabel->setFont(font1);

        gridLayout_2->addWidget(predictedTimesLabel, 1, 3, 1, 5, Qt::AlignHCenter);

        quarterA = new QLabel(clockFrame);
        quarterA->setObjectName(QString::fromUtf8("quarterA"));
        quarterA->setFont(font1);

        gridLayout_2->addWidget(quarterA, 17, 4, 1, 1);

        showPredictionsButton = new QPushButton(clockFrame);
        showPredictionsButton->setObjectName(QString::fromUtf8("showPredictionsButton"));
        showPredictionsButton->setFont(font);

        gridLayout_2->addWidget(showPredictionsButton, 18, 3, 1, 5);

        splitTE = new QLabel(clockFrame);
        splitTE->setObjectName(QString::fromUtf8("splitTE"));

        gridLayout_2->addWidget(splitTE, 11, 1, 1, 1);

        threeThirtyT = new QLabel(clockFrame);
        threeThirtyT->setObjectName(QString::fromUtf8("threeThirtyT"));
        threeThirtyT->setFont(font);

        gridLayout_2->addWidget(threeThirtyT, 10, 5, 1, 1);

        sixtyLabel = new QLabel(clockFrame);
        sixtyLabel->setObjectName(QString::fromUtf8("sixtyLabel"));
        sixtyLabel->setFont(font);

        gridLayout_2->addWidget(sixtyLabel, 8, 0, 1, 1, Qt::AlignRight);

        threeThirtyA = new QLabel(clockFrame);
        threeThirtyA->setObjectName(QString::fromUtf8("threeThirtyA"));
        threeThirtyA->setFont(font);

        gridLayout_2->addWidget(threeThirtyA, 10, 4, 1, 1);

        quarterMPHLable = new QLabel(clockFrame);
        quarterMPHLable->setObjectName(QString::fromUtf8("quarterMPHLable"));
        quarterMPHLable->setFont(font);
        quarterMPHLable->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(quarterMPHLable, 18, 0, 1, 1, Qt::AlignRight);

        sixtyT = new QLabel(clockFrame);
        sixtyT->setObjectName(QString::fromUtf8("sixtyT"));
        sixtyT->setFont(font);

        gridLayout_2->addWidget(sixtyT, 8, 5, 1, 1);

        quarterGoodCheckBox = new QCheckBox(clockFrame);
        quarterGoodCheckBox->setObjectName(QString::fromUtf8("quarterGoodCheckBox"));
        quarterGoodCheckBox->setFont(font);
        quarterGoodCheckBox->setChecked(false);

        gridLayout_2->addWidget(quarterGoodCheckBox, 17, 2, 1, 1);

        sixtyA = new QLabel(clockFrame);
        sixtyA->setObjectName(QString::fromUtf8("sixtyA"));
        sixtyA->setFont(font);

        gridLayout_2->addWidget(sixtyA, 8, 4, 1, 1);

        sixtyP = new QLabel(clockFrame);
        sixtyP->setObjectName(QString::fromUtf8("sixtyP"));
        sixtyP->setFont(font);

        gridLayout_2->addWidget(sixtyP, 8, 7, 1, 1);

        quarterT = new QLabel(clockFrame);
        quarterT->setObjectName(QString::fromUtf8("quarterT"));
        quarterT->setFont(font1);

        gridLayout_2->addWidget(quarterT, 17, 5, 1, 1);

        label = new QLabel(clockFrame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 9, 0, 1, 1, Qt::AlignRight);

        thousandGoodCheckBox = new QCheckBox(clockFrame);
        thousandGoodCheckBox->setObjectName(QString::fromUtf8("thousandGoodCheckBox"));
        thousandGoodCheckBox->setFont(font);
        thousandGoodCheckBox->setChecked(false);

        gridLayout_2->addWidget(thousandGoodCheckBox, 15, 2, 1, 1);

        dateTimeEdit = new QDateTimeEdit(clockFrame);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        sizePolicy1.setHeightForWidth(dateTimeEdit->sizePolicy().hasHeightForWidth());
        dateTimeEdit->setSizePolicy(sizePolicy1);
        dateTimeEdit->setFont(font);

        gridLayout_2->addWidget(dateTimeEdit, 0, 0, 1, 2);

        label_2 = new QLabel(clockFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 11, 0, 1, 1, Qt::AlignRight);

        sixtyH = new QLabel(clockFrame);
        sixtyH->setObjectName(QString::fromUtf8("sixtyH"));
        sixtyH->setFont(font);

        gridLayout_2->addWidget(sixtyH, 8, 6, 1, 1);

        eighthLabel = new QLabel(clockFrame);
        eighthLabel->setObjectName(QString::fromUtf8("eighthLabel"));
        eighthLabel->setFont(font1);

        gridLayout_2->addWidget(eighthLabel, 12, 0, 1, 1, Qt::AlignRight);

        splitTQ = new QLabel(clockFrame);
        splitTQ->setObjectName(QString::fromUtf8("splitTQ"));

        gridLayout_2->addWidget(splitTQ, 16, 1, 1, 1);

        pressureLabel = new QLabel(clockFrame);
        pressureLabel->setObjectName(QString::fromUtf8("pressureLabel"));
        pressureLabel->setFont(font);

        gridLayout_2->addWidget(pressureLabel, 6, 7, 1, 1);

        sixtyEdit = new QLineEdit(clockFrame);
        sixtyEdit->setObjectName(QString::fromUtf8("sixtyEdit"));
        sizePolicy1.setHeightForWidth(sixtyEdit->sizePolicy().hasHeightForWidth());
        sixtyEdit->setSizePolicy(sizePolicy1);
        sixtyEdit->setFont(font);

        gridLayout_2->addWidget(sixtyEdit, 8, 1, 1, 1);

        quarterH = new QLabel(clockFrame);
        quarterH->setObjectName(QString::fromUtf8("quarterH"));
        quarterH->setFont(font1);

        gridLayout_2->addWidget(quarterH, 17, 6, 1, 1);

        thousandA = new QLabel(clockFrame);
        thousandA->setObjectName(QString::fromUtf8("thousandA"));
        thousandA->setFont(font);

        gridLayout_2->addWidget(thousandA, 15, 4, 1, 1);

        eighthT = new QLabel(clockFrame);
        eighthT->setObjectName(QString::fromUtf8("eighthT"));
        eighthT->setFont(font1);

        gridLayout_2->addWidget(eighthT, 12, 5, 1, 1);

        eighthP = new QLabel(clockFrame);
        eighthP->setObjectName(QString::fromUtf8("eighthP"));
        eighthP->setFont(font1);

        gridLayout_2->addWidget(eighthP, 12, 7, 1, 1);

        threeThirtyEdit = new QLineEdit(clockFrame);
        threeThirtyEdit->setObjectName(QString::fromUtf8("threeThirtyEdit"));
        sizePolicy1.setHeightForWidth(threeThirtyEdit->sizePolicy().hasHeightForWidth());
        threeThirtyEdit->setSizePolicy(sizePolicy1);
        threeThirtyEdit->setFont(font);

        gridLayout_2->addWidget(threeThirtyEdit, 10, 1, 1, 1);

        quarterEdit = new QLineEdit(clockFrame);
        quarterEdit->setObjectName(QString::fromUtf8("quarterEdit"));
        sizePolicy1.setHeightForWidth(quarterEdit->sizePolicy().hasHeightForWidth());
        quarterEdit->setSizePolicy(sizePolicy1);
        quarterEdit->setFont(font1);

        gridLayout_2->addWidget(quarterEdit, 17, 1, 1, 1);

        splitST = new QLabel(clockFrame);
        splitST->setObjectName(QString::fromUtf8("splitST"));
        sizePolicy.setHeightForWidth(splitST->sizePolicy().hasHeightForWidth());
        splitST->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(splitST, 9, 1, 1, 1);

        sixtyGoodCheckBox = new QCheckBox(clockFrame);
        sixtyGoodCheckBox->setObjectName(QString::fromUtf8("sixtyGoodCheckBox"));
        sixtyGoodCheckBox->setFont(font);
        sixtyGoodCheckBox->setChecked(false);

        gridLayout_2->addWidget(sixtyGoodCheckBox, 8, 2, 1, 1);

        thousandD = new QLabel(clockFrame);
        thousandD->setObjectName(QString::fromUtf8("thousandD"));
        thousandD->setFont(font);

        gridLayout_2->addWidget(thousandD, 15, 3, 1, 1);

        label_8 = new QLabel(clockFrame);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 19, 0, 1, 1);

        splitMPH = new QLabel(clockFrame);
        splitMPH->setObjectName(QString::fromUtf8("splitMPH"));

        gridLayout_2->addWidget(splitMPH, 19, 1, 1, 1);


        gridLayout->addWidget(clockFrame, 6, 0, 10, 9);

        extraInfoFrame = new QFrame(TicketDialog);
        extraInfoFrame->setObjectName(QString::fromUtf8("extraInfoFrame"));
        extraInfoFrame->setFrameShape(QFrame::NoFrame);
        extraInfoFrame->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(extraInfoFrame);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        delayEdit = new QLineEdit(extraInfoFrame);
        delayEdit->setObjectName(QString::fromUtf8("delayEdit"));
        delayEdit->setFont(font);

        gridLayout_5->addWidget(delayEdit, 1, 1, 1, 1);

        dialLabel = new QLabel(extraInfoFrame);
        dialLabel->setObjectName(QString::fromUtf8("dialLabel"));
        dialLabel->setFont(font);

        gridLayout_5->addWidget(dialLabel, 0, 0, 1, 1);

        delayLabel = new QLabel(extraInfoFrame);
        delayLabel->setObjectName(QString::fromUtf8("delayLabel"));
        delayLabel->setFont(font);

        gridLayout_5->addWidget(delayLabel, 1, 0, 1, 1);

        dialEdit = new QLineEdit(extraInfoFrame);
        dialEdit->setObjectName(QString::fromUtf8("dialEdit"));
        dialEdit->setFont(font);

        gridLayout_5->addWidget(dialEdit, 0, 1, 1, 1);

        riderWeightSpinBox = new QDoubleSpinBox(extraInfoFrame);
        riderWeightSpinBox->setObjectName(QString::fromUtf8("riderWeightSpinBox"));
        riderWeightSpinBox->setFont(font);
        riderWeightSpinBox->setDecimals(1);
        riderWeightSpinBox->setMaximum(999.000000000000000);
        riderWeightSpinBox->setSingleStep(0.100000000000000);

        gridLayout_5->addWidget(riderWeightSpinBox, 4, 1, 1, 1);

        riderWeightLabel = new QLabel(extraInfoFrame);
        riderWeightLabel->setObjectName(QString::fromUtf8("riderWeightLabel"));
        riderWeightLabel->setFont(font);

        gridLayout_5->addWidget(riderWeightLabel, 4, 0, 1, 1);

        vehicleWeightSpinBox = new QSpinBox(extraInfoFrame);
        vehicleWeightSpinBox->setObjectName(QString::fromUtf8("vehicleWeightSpinBox"));
        vehicleWeightSpinBox->setFont(font);
        vehicleWeightSpinBox->setMaximum(10000);

        gridLayout_5->addWidget(vehicleWeightSpinBox, 3, 1, 1, 1);

        vehicleWeightLabel = new QLabel(extraInfoFrame);
        vehicleWeightLabel->setObjectName(QString::fromUtf8("vehicleWeightLabel"));
        vehicleWeightLabel->setFont(font);

        gridLayout_5->addWidget(vehicleWeightLabel, 3, 0, 1, 1);


        gridLayout->addWidget(extraInfoFrame, 7, 11, 1, 1);

        QWidget::setTabOrder(dateTimeEdit, laneComboBox);
        QWidget::setTabOrder(laneComboBox, dialEdit);
        QWidget::setTabOrder(dialEdit, reactionEdit);
        QWidget::setTabOrder(reactionEdit, sixtyEdit);
        QWidget::setTabOrder(sixtyEdit, threeThirtyEdit);
        QWidget::setTabOrder(threeThirtyEdit, eighthEdit);
        QWidget::setTabOrder(eighthEdit, eighthMPHEdit);
        QWidget::setTabOrder(eighthMPHEdit, thousandEdit);
        QWidget::setTabOrder(thousandEdit, quarterEdit);
        QWidget::setTabOrder(quarterEdit, delayEdit);
        QWidget::setTabOrder(delayEdit, vehicleWeightSpinBox);
        QWidget::setTabOrder(vehicleWeightSpinBox, riderWeightSpinBox);
        QWidget::setTabOrder(riderWeightSpinBox, notesEdit);
        QWidget::setTabOrder(notesEdit, sixtyGoodCheckBox);
        QWidget::setTabOrder(sixtyGoodCheckBox, threeThirtyGoodCheckBox);
        QWidget::setTabOrder(threeThirtyGoodCheckBox, eighthGoodCheckBox);
        QWidget::setTabOrder(eighthGoodCheckBox, thousandGoodCheckBox);
        QWidget::setTabOrder(thousandGoodCheckBox, quarterGoodCheckBox);
        QWidget::setTabOrder(quarterGoodCheckBox, trackTicketsCheckBox);
        QWidget::setTabOrder(trackTicketsCheckBox, vehicleTicketsCheckBox);
        QWidget::setTabOrder(vehicleTicketsCheckBox, windAdjustmentSpinBox);
        QWidget::setTabOrder(windAdjustmentSpinBox, weightAdjustmentSpinBox);

        retranslateUi(TicketDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TicketDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TicketDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TicketDialog);
    } // setupUi

    void retranslateUi(QDialog *TicketDialog)
    {
        TicketDialog->setWindowTitle(QApplication::translate("TicketDialog", "Ticket", nullptr));
        pressure->setText(QApplication::translate("TicketDialog", "pres", nullptr));
        windSpeed->setText(QApplication::translate("TicketDialog", "wSpeed", nullptr));
        currentWindDirectionLabel->setText(QApplication::translate("TicketDialog", "Wind Direction", nullptr));
        currentPressureLabel->setText(QApplication::translate("TicketDialog", "Pressure", nullptr));
        temperature->setText(QApplication::translate("TicketDialog", "temp", nullptr));
        vaporPressure->setText(QApplication::translate("TicketDialog", "vPres", nullptr));
        currentDewPointLabel->setText(QApplication::translate("TicketDialog", "Dew Point", nullptr));
        currentDensityALabel->setText(QApplication::translate("TicketDialog", "Density Altitude", nullptr));
        densityAltitude->setText(QApplication::translate("TicketDialog", "dAlt", nullptr));
        windDirection->setText(QApplication::translate("TicketDialog", "wDir", nullptr));
        windGust->setText(QApplication::translate("TicketDialog", "wGust", nullptr));
        humidity->setText(QApplication::translate("TicketDialog", "hum", nullptr));
        currentTemperatureLabel->setText(QApplication::translate("TicketDialog", "Temperature", nullptr));
        currentWindGustLabel->setText(QApplication::translate("TicketDialog", "Wind Gust", nullptr));
        currentHumidityLabel->setText(QApplication::translate("TicketDialog", "Humidity", nullptr));
        currentWindSpeedLabel->setText(QApplication::translate("TicketDialog", "Wind Speed", nullptr));
        dewPoint->setText(QApplication::translate("TicketDialog", "dPoint", nullptr));
        currentWindGustDirLabel->setText(QApplication::translate("TicketDialog", "Gust Direction", nullptr));
        windGustDir->setText(QApplication::translate("TicketDialog", "gDir", nullptr));
        currentVaporPressureLabel->setText(QApplication::translate("TicketDialog", "Vapor Pressure", nullptr));
        vehicleTicketsCheckBox->setText(QApplication::translate("TicketDialog", "Use all tickets for this vehicle", nullptr));
        trackTicketsCheckBox->setText(QApplication::translate("TicketDialog", "Use all tickets for this track", nullptr));
        windAdjustmentLabel->setText(QApplication::translate("TicketDialog", "1/4mi ET adjustment per 1MPH of wind", nullptr));
        weightAdjustmentLabel->setText(QApplication::translate("TicketDialog", "1/4mi ET adjustment per 1lb of weight", nullptr));
        notesLabel->setText(QApplication::translate("TicketDialog", "Notes", nullptr));
        thousandT->setText(QApplication::translate("TicketDialog", "1000'", nullptr));
        thousandP->setText(QApplication::translate("TicketDialog", "1000'", nullptr));
        laneLabel->setText(QApplication::translate("TicketDialog", "Lane", nullptr));
        eighthA->setText(QApplication::translate("TicketDialog", "1/8", nullptr));
        thousandLable->setText(QApplication::translate("TicketDialog", "1000'", nullptr));
        threeThirtyP->setText(QApplication::translate("TicketDialog", "330'", nullptr));
        threeThirtyLabel->setText(QApplication::translate("TicketDialog", "330'", nullptr));
        label_4->setText(QApplication::translate("TicketDialog", "interval", nullptr));
        temperatureLabel->setText(QApplication::translate("TicketDialog", "Temp.", nullptr));
        sixtyD->setText(QApplication::translate("TicketDialog", "60'", nullptr));
        quarterLable->setText(QApplication::translate("TicketDialog", "1/4", nullptr));
        threeThirtyD->setText(QApplication::translate("TicketDialog", "330'", nullptr));
        densityALabel->setText(QApplication::translate("TicketDialog", "DA", nullptr));
        humidityLabel->setText(QApplication::translate("TicketDialog", "Hum.", nullptr));
        quarterP->setText(QApplication::translate("TicketDialog", "1/4", nullptr));
        splitET->setText(QApplication::translate("TicketDialog", "splitET", nullptr));
        averageLabel->setText(QApplication::translate("TicketDialog", "Avg.", nullptr));
        eighthH->setText(QApplication::translate("TicketDialog", "1/8", nullptr));
        eighthGoodCheckBox->setText(QApplication::translate("TicketDialog", "Good", nullptr));
        eighthD->setText(QApplication::translate("TicketDialog", "1/8", nullptr));
        reactionLabel->setText(QApplication::translate("TicketDialog", "Reaction", nullptr));
        thousandH->setText(QApplication::translate("TicketDialog", "1000'", nullptr));
        threeThirtyH->setText(QApplication::translate("TicketDialog", "330'", nullptr));
        reactionEdit->setInputMask(QString());
        threeThirtyGoodCheckBox->setText(QApplication::translate("TicketDialog", "Good", nullptr));
        quarterD->setText(QApplication::translate("TicketDialog", "1/4", nullptr));
        eighthMPHLabel->setText(QApplication::translate("TicketDialog", "1/8 MPH", nullptr));
        label_3->setText(QApplication::translate("TicketDialog", "interval", nullptr));
        predictedTimesLabel->setText(QApplication::translate("TicketDialog", "Predicted Times", nullptr));
        quarterA->setText(QApplication::translate("TicketDialog", "1/4", nullptr));
        showPredictionsButton->setText(QApplication::translate("TicketDialog", "Show Before/After Predictions", nullptr));
        splitTE->setText(QApplication::translate("TicketDialog", "splitTE", nullptr));
        threeThirtyT->setText(QApplication::translate("TicketDialog", "330'", nullptr));
        sixtyLabel->setText(QApplication::translate("TicketDialog", "60'", nullptr));
        threeThirtyA->setText(QApplication::translate("TicketDialog", "330'", nullptr));
        quarterMPHLable->setText(QApplication::translate("TicketDialog", "1/4 MPH", nullptr));
        sixtyT->setText(QApplication::translate("TicketDialog", "60'", nullptr));
        quarterGoodCheckBox->setText(QApplication::translate("TicketDialog", "Good", nullptr));
        sixtyA->setText(QApplication::translate("TicketDialog", "60'", nullptr));
        sixtyP->setText(QApplication::translate("TicketDialog", "60'", nullptr));
        quarterT->setText(QApplication::translate("TicketDialog", "1/4", nullptr));
        label->setText(QApplication::translate("TicketDialog", "interval", nullptr));
        thousandGoodCheckBox->setText(QApplication::translate("TicketDialog", "Good", nullptr));
        label_2->setText(QApplication::translate("TicketDialog", "interval", nullptr));
        sixtyH->setText(QApplication::translate("TicketDialog", "60'", nullptr));
        eighthLabel->setText(QApplication::translate("TicketDialog", "1/8", nullptr));
        splitTQ->setText(QApplication::translate("TicketDialog", "splitTQ", nullptr));
        pressureLabel->setText(QApplication::translate("TicketDialog", "Pres", nullptr));
        quarterH->setText(QApplication::translate("TicketDialog", "1/4", nullptr));
        thousandA->setText(QApplication::translate("TicketDialog", "1000'", nullptr));
        eighthT->setText(QApplication::translate("TicketDialog", "1/8", nullptr));
        eighthP->setText(QApplication::translate("TicketDialog", "1/8", nullptr));
        splitST->setText(QApplication::translate("TicketDialog", "splitST", nullptr));
        sixtyGoodCheckBox->setText(QApplication::translate("TicketDialog", "Good", nullptr));
        thousandD->setText(QApplication::translate("TicketDialog", "1000'", nullptr));
        label_8->setText(QApplication::translate("TicketDialog", "MPH Split", nullptr));
        splitMPH->setText(QApplication::translate("TicketDialog", "splitMPH", nullptr));
        dialLabel->setText(QApplication::translate("TicketDialog", "Dial", nullptr));
        delayLabel->setText(QApplication::translate("TicketDialog", "Delay", nullptr));
        dialEdit->setInputMask(QString());
        riderWeightLabel->setText(QApplication::translate("TicketDialog", "Rider W.", nullptr));
        vehicleWeightLabel->setText(QApplication::translate("TicketDialog", "Vehicle W.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TicketDialog: public Ui_TicketDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TICKETDIALOG_H
