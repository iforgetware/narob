#include "predictiontab.h"
#include "ui_predictiontab.h"
#include "predictions.h"
#include "settings.h"
#include "smtp.h"

#include <QDebug>
#include <QVector>

PredictionTab::PredictionTab(TicketsModel *model,
                             std::shared_ptr<Vehicle> vehicle,
                             std::shared_ptr<Race> race,
                             QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PredictionTab),
    mTicketsModel(model),
    mPredictionsModel(new PredictionsModel(vehicle->value("id").toInt(),
                                           race->value("id").toInt(),
                                           0,
                                           this)),
    mPreviousPredictionsWidget(new PreviousPredictionsWidget(
                                   mPredictionsModel,
                                   this)),
    mCurrentPrediction(Prediction(model,
                                  vehicle->value("id").toInt(),
                                  race->value("trackId").toInt(),
                                  race->value("id").toInt(),
                                  0)),
    mAutoTimer(new QTimer(this)),
    mFactorTimer(new QTimer(this))
{
    ui->setupUi(this);

    ui->gridLayout_2->addWidget(mPreviousPredictionsWidget, 0, 0);

    ui->vehicleWeightSpinBox->setValue(vehicle->value("weight").toInt());
    ui->riderWeightSpinBox->setValue(mTicketsModel->lastWeight());

    ui->weightAdjustmentSpinBox->setValue(vehicle->value("weightAdjustment")
                                          .toDouble());
    ui->windAdjustmentSpinBox->setValue(vehicle->value("windAdjustment")
                                        .toDouble());
    ui->textProviderComboBox->setCurrentText(vehicle->value("textProvider")
                                             .toString());
    ui->textNumberEdit->setText(vehicle->value("textNumber")
                                .toString());

    connect(ui->vehicleWeightSpinBox,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            &PredictionTab::onFactorChange);

    connect(ui->riderWeightSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &PredictionTab::onFactorChange);

    connect(ui->windAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &PredictionTab::onFactorChange);

    connect(ui->weightAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &PredictionTab::onFactorChange);

    connect(ui->trackTicketsCheckBox,
            &QCheckBox::stateChanged,
            this,
            &PredictionTab::onTrackTicketsCheckboxChange);

    connect(ui->vehicleTicketsCheckBox,
            &QCheckBox::stateChanged,
            this,
            &PredictionTab::onVehicleTicketsCheckboxChange);

    connect(mAutoTimer, &QTimer::timeout,
            this, &PredictionTab::makePrediction);

    connect(mFactorTimer, &QTimer::timeout,
            this, &PredictionTab::makePrediction);

    mAutoTimer->start(60000);
}

PredictionTab::~PredictionTab()
{
    delete mAutoTimer;
    delete mFactorTimer;
    delete ui;
}

void PredictionTab::UpdateAllModels()
{
    mPreviousPredictionsWidget->updateModel();
}

void PredictionTab::makePrediction()
{
    mCurrentPrediction.predictClocks(QDateTime(),
                                     ui->riderWeightSpinBox->value(),
                                     ui->vehicleWeightSpinBox->value(),
                                     ui->windAdjustmentSpinBox->value(),
                                     ui->weightAdjustmentSpinBox->value(),
                                     ui->vehicleTicketsCheckBox->isChecked(),
                                     ui->trackTicketsCheckBox->isChecked());

    int minute = mCurrentPrediction.value("dateTime")
                 .toDateTime()
                 .time()
                 .minute();

    if(minute % 1 == 0){ // DEV ONLY - chenge to 5 or add setting to settings
        writePredictionToDb();
    }

    updateDisplay();

    mFactorTimer->stop();
}

void PredictionTab::writePredictionToDb()
{
    if(mCurrentPrediction.value("temperature").toDouble() > 0){
        mPredictionsModel->addRow(mCurrentPrediction);

        if(ui->eToPhoneCheckBox->isChecked() || ui->qToPhoneCheckBox->isChecked()){
            sendPage();
        }

        while(mPredictionsModel->rowCount(QModelIndex()) > 5){
            mPredictionsModel->removeRow(mPredictionsModel->rowCount(QModelIndex()) - 1);
            mPredictionsModel->submitAll();
            mPreviousPredictionsWidget->updateModel();
        }
    }
}

void PredictionTab::updateDisplay()
{
    updatePLabel("sixtyD", ui->sixtyD);
    updatePLabel("threeThirtyD", ui->threeThirtyD);
    updatePLabel("eighthD", ui->eighthD);
    updatePLabel("thousandD", ui->thousandD);
    updatePLabel("quarterD", ui->quarterD);

    updatePLabel("sixtyA", ui->sixtyA);
    updatePLabel("threeThirtyA", ui->threeThirtyA);
    updatePLabel("eighthA", ui->eighthA);
    updatePLabel("thousandA", ui->thousandA);
    updatePLabel("quarterA", ui->quarterA);

    updatePLabel("sixtyT", ui->sixtyT);
    updatePLabel("threeThirtyT", ui->threeThirtyT);
    updatePLabel("eighthT", ui->eighthT);
    updatePLabel("thousandT", ui->thousandT);
    updatePLabel("quarterT", ui->quarterT);

    updatePLabel("sixtyH", ui->sixtyH);
    updatePLabel("threeThirtyH", ui->threeThirtyH);
    updatePLabel("eighthH", ui->eighthH);
    updatePLabel("thousandH", ui->thousandH);
    updatePLabel("quarterH", ui->quarterH);

    updatePLabel("sixtyP", ui->sixtyP);
    updatePLabel("threeThirtyP", ui->threeThirtyP);
    updatePLabel("eighthP", ui->eighthP);
    updatePLabel("thousandP", ui->thousandP);
    updatePLabel("quarterP", ui->quarterP);
}

void PredictionTab::pageLine(QString line, QString field, int decimals)
{
    if(decimals == -3){
        mPage.append(QString(line)
                     .arg(QString(mCurrentPrediction.value(field)
                             .toTime().toString("hh:mm"))));
    }else if(decimals == 0){
        mPage.append(QString(line)
                     .arg(QString::number(mCurrentPrediction
                                     .value(field)
                                     .toInt())));
    }else{
        mPage.append(QString(line)
                     .arg(QString::number(mCurrentPrediction
                                         .value(field)
                                         .toDouble())));
    }
}

void PredictionTab::sendPage()
{
    if(Settings::get("emailUser").toString() == ""
       || Settings::get("emailHost").toString() == ""
       || Settings::get("emailPW").toString() == ""){
        qDebug("No email settings to page with - WRITE CODE");
    }else{
        mPage = "\n";

        QString suffix = QString("@%1")
                         .arg(TEXT_SUFFIXES
                              .value(ui->textProviderComboBox->currentText()));

        pageLine("%1\n", "dateTime", -3);
        pageLine("Temp -> %1\n", "temperature", 1);
        pageLine("Humid -> %1\n", "humidity", 1);
        pageLine("Press -> %1\n", "pressure", 2);
        pageLine("Vap P -> %1\n", "vaporPressure", 2);
        pageLine("Dew P -> %1\n", "dewPoint", 1);
        pageLine("D Alt -> %1\n", "densityAltitude", 0);
        pageLine("W Speed -> %1\n", "windSpeed", 0);
        pageLine("W Gust -> %1\n", "windGust", 0);
        pageLine("W Dir -> %1\n", "windDirection", 0);

        Smtp *smtpW = new Smtp(this);
        //connect(smtpW, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        smtpW->sendMail(QString("%1%2")
                        .arg(ui->textNumberEdit->text())
                        .arg(suffix),
                        "Weather",
                        mPage);

        mPage = "\n";

        if(ui->eToPhoneCheckBox->isChecked()){
            pageLine("%1\n", "dateTime", -3);
            pageLine("By d alt -> %1\n", "eighthD", 3);
            pageLine("Average -> %1\n", "eighthA", 3);

            Smtp *smtpE = new Smtp(this);
            //connect(smtpE, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtpE->sendMail(QString("%1%2")
                            .arg(ui->textNumberEdit->text())
                            .arg(suffix),
                            "1/8",
                            mPage);
        }

        mPage = "\n";

        if(ui->qToPhoneCheckBox->isChecked()){
            pageLine("%1\n", "dateTime", -3);
            pageLine("By d alt -> %1\n", "quarterD", 3);
            pageLine("Average -> %1\n", "quarterA", 3);

            Smtp *smtpQ = new Smtp(this);
            //connect(smtpQ, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            smtpQ->sendMail(QString("%1%2")
                            .arg(ui->textNumberEdit->text())
                            .arg(suffix),
                            "1/4",
                            mPage);
        }
    }
}

void PredictionTab::mailSent(QString status)
{
    if(status == "Message sent")
    {
        qDebug("page sent");
    }
}

void PredictionTab::updatePLabel(const QString &field, QLabel *label)
{
    if(mCurrentPrediction.value(field).toDouble() == 0.0){
        label->setText("");
    }else{
        label->setText(QString::number(mCurrentPrediction.value(field)
                                       .toDouble(),
                                       'f',
                                       3));
    }
}

void PredictionTab::onTrackTicketsCheckboxChange(){
    if(ui->trackTicketsCheckBox->isChecked()){
            ui->vehicleTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void PredictionTab::onVehicleTicketsCheckboxChange(){
    if(ui->vehicleTicketsCheckBox->isChecked()){
        ui->trackTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void PredictionTab::onFactorChange()
{
    mFactorTimer->start(CHANGE_DELAY);
}
