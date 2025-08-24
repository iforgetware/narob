#include "ticketdialog.h"
#include "ui_ticketdialog.h"
#include "observations.h"
#include "ticketpredictionsdialog.h"

#include <math.h>

#include <QDebug>

TicketDialog::TicketDialog(TicketsLogbookModel *tLModel,
                           TicketsRaceModel *tRModel,
                           std::shared_ptr<Vehicle> vehicle,
                           std::shared_ptr<Race> race,
                           int row,
                           QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::TicketDialog),
    mVehicle(vehicle),
    mRace(race),
    mObservationsModel(new ObservationsModel(this)),
    mTicketsLogbookModel(tLModel),
    mTicketsRaceModel(tRModel),
    mDateTimer(new QTimer(this)),
    mFactorTimer(new QTimer(this))
{
    ui->setupUi(this);

    setupModel();

    createUi();

    setModelRow(row);

    ui->weightAdjustmentSpinBox->setValue(mVehicle->value("weightAdjustment").toDouble());
    ui->windAdjustmentSpinBox->setValue(mVehicle->value("windAdjustment").toDouble());

    mId = mModel->data(indexForField("id")).toInt();

    mPredictedRun = new Prediction(mTicketsLogbookModel,
                                   mVehicle->value("id").toInt(),
                                   mRace->value("trackId").toInt(),
                                   mRace->value("id").toInt(),
                                   mId);

    if(row == -1){
        mModel->setData(indexForField("vehicleId"),
                        mVehicle->value("id"));

        mModel->setData(indexForField("trackId"),
                        mRace->value("trackId"));

        mModel->setData(indexForField("raceId"),
                        mRace->value("id"));

        ui->vehicleWeightSpinBox->setValue(mVehicle->value("weight").toInt());
        ui->riderWeightSpinBox->setValue(mTicketsLogbookModel->lastWeight());

        QDateTime cDT;
        cDT.setDate(QDate::currentDate());
        cDT.setTime(QTime(QTime::currentTime().hour(),
                          QTime::currentTime().minute()));
        ui->dateTimeEdit->setDateTime(cDT);










        // add light good check box
        // this poses a problem
        // can't be negative because they exist
        // maybe blank? maybe seperate field?


        ui->sixtyGoodCheckBox->setChecked(true);
        ui->threeThirtyGoodCheckBox->setChecked(true);
        ui->eighthGoodCheckBox->setChecked(true);
        ui->thousandGoodCheckBox->setChecked(true);
        ui->quarterGoodCheckBox->setChecked(true);
    }else{
        formatDoubleEdit("delay", ui->delayEdit, 3);
        formatDoubleEdit("reaction", ui->reactionEdit, 3);
        formatDoubleEdit("eighthMPH", ui->eighthMPHEdit, 2);
        formatDoubleEdit("quarterMPH", ui->quarterMPHEdit, 2);
        formatDoubleEdit("dial", ui->dialEdit, 2);








        // add light edit

        formatClockEdit("sixty", ui->sixtyEdit, ui->sixtyGoodCheckBox);
        formatClockEdit("threeThirty", ui->threeThirtyEdit, ui->threeThirtyGoodCheckBox);
        formatClockEdit("eighth", ui->eighthEdit, ui->eighthGoodCheckBox);
        formatClockEdit("thousand", ui->thousandEdit, ui->thousandGoodCheckBox);
        formatClockEdit("quarter", ui->quarterEdit, ui->quarterGoodCheckBox);

        updateSplits();
    }

    updateWeather();

    connect(ui->dateTimeEdit,
            &QDateTimeEdit::dateTimeChanged,
            this,
            &TicketDialog::onDateChange);

    connect(ui->sixtyEdit,
            &QLineEdit::textChanged,
            this,
            &TicketDialog::updateSplits);

    connect(ui->threeThirtyEdit,
            &QLineEdit::textChanged,
            this,
            &TicketDialog::updateSplits);

    connect(ui->eighthEdit,
            &QLineEdit::textChanged,
            this,
            &TicketDialog::updateSplits);

    connect(ui->thousandEdit,
            &QLineEdit::textChanged,
            this,
            &TicketDialog::updateSplits);

    connect(ui->quarterEdit,
            &QLineEdit::textChanged,
            this,
            &TicketDialog::updateSplits);

    connect(ui->eighthMPHEdit,
            &QLineEdit::textChanged,
            this,
            &TicketDialog::updateSplits);

    connect(ui->quarterMPHEdit,
            &QLineEdit::textChanged,
            this,
            &TicketDialog::updateSplits);

    connect(ui->vehicleWeightSpinBox,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            &TicketDialog::onFactorChange);

    connect(ui->riderWeightSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &TicketDialog::onFactorChange);

    connect(ui->windAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &TicketDialog::onFactorChange);

    connect(ui->weightAdjustmentSpinBox,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this,
            &TicketDialog::onFactorChange);

    connect(ui->trackTicketsCheckBox,
            &QCheckBox::checkStateChanged,
            this,
            &TicketDialog::onTrackTicketsCheckboxChange);

    connect(ui->vehicleTicketsCheckBox,
            &QCheckBox::checkStateChanged,
            this,
            &TicketDialog::onVehicleTicketsCheckboxChange);

    connect(ui->temperatureEdit,
            &QLineEdit::textChanged,
            this,
            &TicketDialog::onDateChange);

    connect(ui->humidityEdit,
            &QLineEdit::textChanged,
            this,
            &TicketDialog::onDateChange);

    connect(ui->pressureEdit,
            &QLineEdit::textChanged,
            this,
            &TicketDialog::onDateChange);

    connect(ui->windSpeedEdit,
            &QLineEdit::textChanged,
            this,
            &TicketDialog::onDateChange);

    connect(ui->windDirectionEdit,
            &QLineEdit::textChanged,
            this,
            &TicketDialog::onDateChange);

    connect(mDateTimer, &QTimer::timeout,
            this, &TicketDialog::updateWeather);

    connect(mFactorTimer, &QTimer::timeout,
            this, &TicketDialog::updatePrediction);

    connect(ui->showPredictionsButton, &QPushButton::clicked,
            this, &TicketDialog::onShowPredictionsClicked);

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &TicketDialog::onButtonBoxAccepted);

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


}

TicketDialog::~TicketDialog()
{
    delete mDateTimer;
    delete mFactorTimer;
    delete mPredictedRun;
    delete ui;
}

void TicketDialog::setupModel()
{
    mModel = mTicketsRaceModel;

    mMapper->setModel(mModel);

    mMapper->addMapping(ui->dateTimeEdit, mModel->fieldIndex("dateTime"));
    mMapper->addMapping(ui->laneComboBox, mModel->fieldIndex("lane"));
    mMapper->addMapping(ui->dialEdit, mModel->fieldIndex("dial"));
    mMapper->addMapping(ui->reactionEdit, mModel->fieldIndex("reaction"));
    mMapper->addMapping(ui->sixtyEdit, mModel->fieldIndex("sixty"));
    mMapper->addMapping(ui->threeThirtyEdit, mModel->fieldIndex("threeThirty"));
    mMapper->addMapping(ui->eighthEdit, mModel->fieldIndex("eighth"));
    mMapper->addMapping(ui->eighthMPHEdit, mModel->fieldIndex("eighthMPH"));
    mMapper->addMapping(ui->thousandEdit, mModel->fieldIndex("thousand"));
    mMapper->addMapping(ui->quarterEdit, mModel->fieldIndex("quarter"));
    mMapper->addMapping(ui->quarterMPHEdit, mModel->fieldIndex("quarterMPH"));
    mMapper->addMapping(ui->delayEdit, mModel->fieldIndex("delay"));
    mMapper->addMapping(ui->vehicleWeightSpinBox, mModel->fieldIndex("vehicleWeight"));
    mMapper->addMapping(ui->riderWeightSpinBox, mModel->fieldIndex("riderWeight"));
    mMapper->addMapping(ui->notesEdit, mModel->fieldIndex("notes"));
    mMapper->addMapping(ui->temperatureEdit, mModel->fieldIndex("temperatureM"));
    mMapper->addMapping(ui->humidityEdit, mModel->fieldIndex("humidityM"));
    mMapper->addMapping(ui->pressureEdit, mModel->fieldIndex("pressureM"));
    mMapper->addMapping(ui->windDirectionEdit, mModel->fieldIndex("windDirectionM"));
    mMapper->addMapping(ui->windSpeedEdit, mModel->fieldIndex("windSpeedM"));
}

void vInt(QLineEdit *edit)
{
    edit->setValidator(new QIntValidator(edit));
}

void vDouble(QLineEdit *edit, int d)
{
    edit->setValidator(new QDoubleValidator(-2, 1000, d, edit));
}

void TicketDialog::createUi()
{
    vDouble(ui->delayEdit, 3);
    ui->laneComboBox->addItems(QStringList() << "Left" << "Right");
    vDouble(ui->dialEdit, 2);
    vDouble(ui->reactionEdit, 3);
    vDouble(ui->sixtyEdit, 3);
    vDouble(ui->threeThirtyEdit, 3);
    vDouble(ui->eighthEdit, 3);
    vDouble(ui->eighthMPHEdit, 2);
    vDouble(ui->thousandEdit, 3);
    vDouble(ui->quarterEdit, 3);
    vDouble(ui->quarterMPHEdit, 2);
}

void TicketDialog::updateWeather()
{
    mObservation = mObservationsModel->observationForTime(ui->dateTimeEdit->dateTime());

    double t = ui->temperatureEdit->text().toDouble();
    double h = ui->humidityEdit->text().toDouble();
    double p = ui->pressureEdit->text().toDouble();
    int wd = ui->windDirectionEdit->text().toInt();
    int ws = ui->windSpeedEdit->text().toInt();

    if(t != 0.0 || h != 0.0 || p != 0.0 || wd != 0 || ws != 0){
        mObservation.overrideObservation(t, h, p, wd, ws);
    }

    mObservation.calcDA();

    updateWValue("temperature");
    updateWValue("humidity");
    updateWValue("pressure");
    updateWValue("vaporPressure");
    updateWValue("dewPoint");
    updateWValue("densityAltitude");
    updateWValue("windSpeed");
    updateWValue("windGust");
    updateWValue("windDirection");
    updateWValue("windGustDirection");

    updateWLabel("temperature", ui->temperature, 1);
    updateWLabel("humidity", ui->humidity, 1);
    updateWLabel("pressure", ui->pressure, 2);
    updateWLabel("vaporPressure", ui->vaporPressure, 2);
    updateWLabel("dewPoint", ui->dewPoint, 1);
    updateWLabel("densityAltitude", ui->densityAltitude, 0);
    updateWLabel("windSpeed", ui->windSpeed, 0);
    updateWLabel("windGust", ui->windGust, 0);
    updateWLabel("windDirection", ui->windDirection, 0);
    updateWLabel("windGustDirection", ui->windGustDir, 0);

    mDateTimer->stop();

    updatePrediction();
}

void TicketDialog::updateSplits()
{
    updateSValue("splitST",
                 fabs(ui->threeThirtyEdit->text().toDouble()) -
                 fabs(ui->sixtyEdit->text().toDouble())
                 );
    updateSValue("splitTE",
                 fabs(ui->eighthEdit->text().toDouble()) -
                 fabs(ui->threeThirtyEdit->text().toDouble())
                 );

    if(fabs(ui->quarterEdit->text().toDouble()) >
            fabs(ui->eighthEdit->text().toDouble())){

        updateSValue("splitET",
                     fabs(ui->thousandEdit->text().toDouble()) -
                     fabs(ui->eighthEdit->text().toDouble())
                     );
        updateSValue("splitTQ",
                     fabs(ui->quarterEdit->text().toDouble()) -
                     fabs(ui->thousandEdit->text().toDouble())
                     );
        updateSValue("splitMPH",
                     fabs(ui->quarterMPHEdit->text().toDouble()) -
                     fabs(ui->eighthMPHEdit->text().toDouble())
                     );
    }else{
        updateSValue("splitET", 0);
        updateSValue("splitTQ", 0);
        updateSValue("splitMPH", 0);
    }

    updateSLabel("splitST", ui->splitST, 3);
    updateSLabel("splitTE", ui->splitTE, 3);
    updateSLabel("splitET", ui->splitET, 3);
    updateSLabel("splitTQ", ui->splitTQ, 3);
    updateSLabel("splitMPH", ui->splitMPH, 2);
}

void TicketDialog::updatePrediction()
{
    mPredictedRun->predictByObservation(mObservation,
                                        ui->riderWeightSpinBox->value(),
                                        ui->vehicleWeightSpinBox->value(),
                                        ui->windAdjustmentSpinBox->value(),
                                        ui->weightAdjustmentSpinBox->value(),
                                        ui->vehicleTicketsCheckBox->isChecked(),
                                        ui->trackTicketsCheckBox->isChecked());

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

    mFactorTimer->stop();
}

void TicketDialog::formatDoubleEdit(const QString &field,
                                    QLineEdit *edit,
                                    const int decimals)
{
    double number = mModel->data(indexForField(field)).toDouble();
    edit->setText(QString::number(number, 'f', decimals));
}

void TicketDialog::formatNumberLabel(const QVariant &value,
                                     QLabel *label,
                                     const int decimals)
{
    if(value.toDouble() == 0.0){
        label->setText("");
    }else if(decimals){
        label->setText(QString::number(value.toDouble(), 'f', decimals));
    }else{
        label->setText(QString::number(value.toInt()));
    }
}

void TicketDialog::updatePLabel(const QString &field, QLabel *label)
{
    formatNumberLabel(mPredictedRun->value(field),
                      label,
                      3);
}

void TicketDialog::updateWLabel(const QString &field, QLabel *label, const int decimals)
{
    formatNumberLabel(mModel->data(indexForField(field)),
                      label,
                      decimals);
}

void TicketDialog::updateSLabel(const QString &field, QLabel *label, const int decimals)
{
    formatNumberLabel(mModel->data(indexForField(field)),
                      label,
                      decimals);
}

void TicketDialog::formatClockEdit(const QString &field,
                                   QLineEdit *edit,
                                   QCheckBox *checkBox)
{
    double clock = mModel->data(indexForField(field)).toDouble();
    if(clock <= 0){
        checkBox->setChecked(false);
    }else{
        checkBox->setChecked(true);
    }
    edit->setText(QString::number(fabs(clock), 'f', 3));
}

void TicketDialog::updateWValue(const QString &field)
{
    mModel->setData(indexForField(field),
                    mObservation.value(field));
}

void TicketDialog::updateSValue(const QString &field, double value)
{
    mModel->setData(indexForField(field), value);
}

void TicketDialog::onShowPredictionsClicked()
{
    PredictionsModel *predictionsModel = new PredictionsModel(mVehicle->value("id").toInt(),
                                                              mRace->value("id").toInt(),
                                                              mId,
                                                              this);

    TicketPredictionsDialog *ticketPredictionsDialog
            = new TicketPredictionsDialog(predictionsModel,
                                          mPredictedRun,
                                          this);

    ticketPredictionsDialog->exec();

    delete ticketPredictionsDialog;
}

void TicketDialog::onDateChange()
{
    mDateTimer->start(CHANGE_DELAY);
}

void TicketDialog::onTrackTicketsCheckboxChange(){
    if(ui->trackTicketsCheckBox->isChecked()){
            ui->vehicleTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void TicketDialog::onVehicleTicketsCheckboxChange(){
    if(ui->vehicleTicketsCheckBox->isChecked()){
        ui->trackTicketsCheckBox->setCheckState(Qt::Unchecked);
    }

    onFactorChange();
}

void TicketDialog::onFactorChange()
{
    mFactorTimer->start(CHANGE_DELAY);
}

void TicketDialog::onButtonBoxAccepted()
{






    // add light edit

    handleClockGood(ui->sixtyEdit, ui->sixtyGoodCheckBox);
    handleClockGood(ui->threeThirtyEdit, ui->threeThirtyGoodCheckBox);
    handleClockGood(ui->eighthEdit, ui->eighthGoodCheckBox);
    handleClockGood(ui->thousandEdit, ui->thousandGoodCheckBox);
    handleClockGood(ui->quarterEdit, ui->quarterGoodCheckBox);

    updateSplits();

    mMapper->submit();
    mModel->submitAll();
    emit ready();
}

void TicketDialog::handleClockGood(QLineEdit *edit, QCheckBox *checkBox)
{
    double clockAbs = edit->text().toDouble();
    double clock;

    if(checkBox->isChecked()){
        clock = clockAbs;
    }else{
        clock = -clockAbs;
    }
    edit->setText(QString::number(clock, 'f', 3));
}
