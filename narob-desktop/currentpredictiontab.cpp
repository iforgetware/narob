#include "currentpredictiontab.h"
#include "ui_currentpredictiontab.h"

#include "settings.h"
#include "smtp.h"

CurrentPredictionTab::CurrentPredictionTab(Prediction *prediction,
                                           TicketsLogbookModel *tLModel,
                                           PredictionsModel *pModel,
                                           std::shared_ptr<Vehicle> vehicle,
                                           QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentPredictionTab),
    mCurrentPrediction(prediction),
    mPredictionsModel(pModel),
    mTicketsLogbookModel(tLModel),
    mAutoTimer(new QTimer(this)),
    mFactorTimer(new QTimer(this))
{
    ui->setupUi(this);

    ui->vehicleWeightSpinBox->setValue(vehicle->value("weight").toInt());
    ui->riderWeightSpinBox->setValue(tLModel->lastWeight());

    ui->weightAdjustmentSpinBox->setValue(vehicle->value("weightAdjustment")
                                          .toDouble());
    ui->windAdjustmentSpinBox->setValue(vehicle->value("windAdjustment")
                                        .toDouble());
    ui->textProviderComboBox->setCurrentText(vehicle->value("textProvider")
                                             .toString());
    ui->textNumberEdit->setText(vehicle->value("textNumber")
                                .toString());

    for(QLabel *label: {ui->temperatureLabel,
                        ui->sixtyT,
                        ui->threeThirtyT,
                        ui->eighthT,
                        ui->thousandT,
                        ui->quarterT}){
        label->setStyleSheet("color: " + T_COLOR.name());
    }

    for(QLabel *label: {ui->humidityLabel,
                        ui->sixtyH,
                        ui->threeThirtyH,
                        ui->eighthH,
                        ui->thousandH,
                        ui->quarterH}){
        label->setStyleSheet("color: " + H_COLOR.name());
    }

    for(QLabel *label: {ui->pressureLabel,
                        ui->sixtyP,
                        ui->threeThirtyP,
                        ui->eighthP,
                        ui->thousandP,
                        ui->quarterP}){
        label->setStyleSheet("color: " + P_COLOR.name());
    }

    for(QLabel *label: {ui->averageLabel,
                        ui->sixtyA,
                        ui->threeThirtyA,
                        ui->eighthA,
                        ui->thousandA,
                        ui->quarterA}){
        label->setStyleSheet("color: " + A_COLOR.name());
    }

    for(QLabel *label: {ui->densityALabel,
                        ui->sixtyD,
                        ui->threeThirtyD,
                        ui->eighthD,
                        ui->thousandD,
                        ui->quarterD}){
        label->setStyleSheet("color: " + D_COLOR.name());
    }

    connect(ui->vehicleWeightSpinBox,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            &CurrentPredictionTab::onFactorChange);

    connect(ui->riderWeightSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &CurrentPredictionTab::onFactorChange);

    connect(ui->windAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &CurrentPredictionTab::onFactorChange);

    connect(ui->weightAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &CurrentPredictionTab::onFactorChange);

    connect(ui->trackTicketsCheckBox,
            &QCheckBox::stateChanged,
            this,
            &CurrentPredictionTab::onTrackTicketsCheckboxChange);

    connect(ui->vehicleTicketsCheckBox,
            &QCheckBox::stateChanged,
            this,
            &CurrentPredictionTab::onVehicleTicketsCheckboxChange);

    connect(mAutoTimer, &QTimer::timeout,
            this, &CurrentPredictionTab::makePrediction);

    connect(mFactorTimer, &QTimer::timeout,
            this, &CurrentPredictionTab::makePrediction);

    mAutoTimer->start(60000);
}

CurrentPredictionTab::~CurrentPredictionTab()
{
    delete mAutoTimer;
    delete mFactorTimer;
    delete ui;
}
void CurrentPredictionTab::makePrediction()
{
    mCurrentPrediction->predictByTime(QDateTime(),
                                      ui->riderWeightSpinBox->value(),
                                      ui->vehicleWeightSpinBox->value(),
                                      ui->windAdjustmentSpinBox->value(),
                                      ui->weightAdjustmentSpinBox->value(),
                                      ui->vehicleTicketsCheckBox->isChecked(),
                                      ui->trackTicketsCheckBox->isChecked());

    emit predictionUpdated();

    int minute = mCurrentPrediction->value("dateTime")
                 .toDateTime()
                 .time()
                 .minute();

    if(minute % 5 == 0){// DEV ONLY - set back to 5
        writePredictionToDb();
    }

    updateDisplay();

    mFactorTimer->stop();
}

void CurrentPredictionTab::writePredictionToDb()
{
    if(mCurrentPrediction->value("temperature").toDouble() > 0){
        mPredictionsModel->addRow(*mCurrentPrediction);

        if(ui->eToPhoneCheckBox->isChecked() || ui->qToPhoneCheckBox->isChecked()){
            sendPage();
        }

        while(mPredictionsModel->rowCount(QModelIndex()) > 5){
            mPredictionsModel->removeRow(mPredictionsModel->rowCount(QModelIndex()) - 1);
            mPredictionsModel->submitAll();
            emit predictionWrittenToDB();
        }
    }
}

void CurrentPredictionTab::updateDisplay()
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

void CurrentPredictionTab::pageLine(QString line, QString field, int decimals)
{
    if(decimals == -3){
        mPage.append(QString(line)
                     .arg(QString(mCurrentPrediction->value(field)
                             .toTime().toString("hh:mm"))));
    }else if(decimals == 0){
        mPage.append(QString(line)
                     .arg(QString::number(mCurrentPrediction
                                     ->value(field)
                                     .toInt())));
    }else{
        mPage.append(QString(line)
                     .arg(QString::number(mCurrentPrediction
                                         ->value(field)
                                         .toDouble()
                                          ,'f',
                                          decimals)));
    }
}

void CurrentPredictionTab::sendPage()
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

void CurrentPredictionTab::mailSent(QString status)
{
    if(status == "Message sent")
    {
        qDebug("page sent");
    }
}

void CurrentPredictionTab::updatePLabel(const QString &field, QLabel *label)
{
    if(mCurrentPrediction->value(field).toDouble() == 0.0){
        label->setText("");
    }else{
        label->setText(QString::number(mCurrentPrediction->value(field)
                                       .toDouble(),
                                       'f',
                                       3));
    }
}

void CurrentPredictionTab::onTrackTicketsCheckboxChange(){
    if(ui->trackTicketsCheckBox->isChecked()){
            ui->vehicleTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void CurrentPredictionTab::onVehicleTicketsCheckboxChange(){
    if(ui->vehicleTicketsCheckBox->isChecked()){
        ui->trackTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void CurrentPredictionTab::onFactorChange()
{
    mFactorTimer->start(CHANGE_DELAY);
}
