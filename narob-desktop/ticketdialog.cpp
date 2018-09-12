#include "ticketdialog.h"
#include "ui_ticketdialog.h"
#include "observations.h"
#include "ticketpredictionsdialog.h"

#include <math.h>

#include <QSqlQuery>
#include <QDebug>

TicketDialog::TicketDialog(Vehicle* vehicle,
                           Race* race,
                           int row,
                           QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::TicketDialog),
    mSettingsTable(new Settings),
    mVehicle(vehicle),
    mRace(race),
    mObservationsModel(new ObservationsModel(this)),
    mDateTimer(new QTimer(this)),
    mFactorTimer(new QTimer(this))
{
    ui->setupUi(this);

    setupModel();

    createUi();

    setModelRow(row);

    mSettings = mSettingsTable->getSettings();

    ui->weightAdjustmentSpinBox->setValue(mSettings->value("weightAdjustment").toDouble());
    ui->windAdjustmentSpinBox->setValue(mSettings->value("windAdjustment").toDouble());

//    QModelIndex iIndex = mModel->index(mRow,
//                                       mModel->fieldIndex("id"));
//    mId = mModel->data(iIndex).toInt();
    mId = mModel->data(indexForField("id")).toInt();

    mPredictionsModel = new PredictionsModel(mVehicle,
                                             mRace,
                                             mId,
                                             this);

    if(row == -1){
        mModel->setData(indexForField("vehicleId"),
                        mVehicle->value("id").toInt());

        mModel->setData(indexForField("trackId"),
                        mRace->value("trackId").toInt());

        mModel->setData(indexForField("raceId"),
                        mRace->value("id").toInt());

        ui->vehicleWeightSpinBox->setValue(mVehicle->value("weight").toInt());

        TicketsModel *ticketsModel = new TicketsModel(mVehicle, this);
        ui->riderWeightSpinBox->setValue(ticketsModel->lastWeight());
        delete ticketsModel;

        QDateTime cDT;
        cDT.setDate(QDate::currentDate());
        cDT.setTime(QTime(QTime::currentTime().hour(), QTime::currentTime().minute()));
        ui->dateTimeEdit->setDateTime(cDT);

        updateWeather();

        ui->sixtyGoodCheckBox->setChecked(true);
        ui->threeThirtyGoodCheckBox->setChecked(true);
        ui->eighthGoodCheckBox->setChecked(true);
        ui->thousandGoodCheckBox->setChecked(true);
        ui->quarterGoodCheckBox->setChecked(true);

//        ui->temperature->setText("");
//        ui->humidity->setText("");
//        ui->pressure->setText("");
//        ui->vaporPressure->setText("");
//        ui->dewPoint->setText("");
//        ui->densityAltitude->setText("");
//        ui->windSpeed->setText("");
//        ui->windGust->setText("");
//        ui->windDirection->setText("");
    }else{
        formatDoubleEdit("delay", ui->delayEdit, 3);
        formatDoubleEdit("reaction", ui->reactionEdit, 3);
        formatDoubleEdit("eighthMPH", ui->eighthMPHEdit, 2);
        formatDoubleEdit("quarterMPH", ui->quarterMPHEdit, 2);
        formatDoubleEdit("dial", ui->dialEdit, 2);

        formatClockEdit("sixty", ui->sixtyEdit, ui->sixtyGoodCheckBox);
        formatClockEdit("threeThirty", ui->threeThirtyEdit, ui->threeThirtyGoodCheckBox);
        formatClockEdit("eighth", ui->eighthEdit, ui->eighthGoodCheckBox);
        formatClockEdit("thousand", ui->thousandEdit, ui->thousandGoodCheckBox);
        formatClockEdit("quarter", ui->quarterEdit, ui->quarterGoodCheckBox);
    }

    updateDisplay();

    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged,
            this, &TicketDialog::onDateChange);

    connect(ui->vehicleWeightSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &TicketDialog::onFactorChange);

    connect(ui->riderWeightSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &TicketDialog::onFactorChange);

    connect(ui->windAdjustmentSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &TicketDialog::onFactorChange);

    connect(ui->weightAdjustmentSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &TicketDialog::onFactorChange);

    connect(ui->showPredictionsButton, &QPushButton::clicked,
            this, &TicketDialog::onShowPredictionsClicked);

    connect(mDateTimer, &QTimer::timeout,
            this, &TicketDialog::updateWeather);

    connect(mFactorTimer, &QTimer::timeout,
            this, &TicketDialog::updateDisplay);

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &TicketDialog::onButtonBoxAccepted);
}

TicketDialog::~TicketDialog()
{
    delete ui;
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
    if(decimals){
        label->setText(QString::number(value.toDouble(), 'f', decimals));
    }else{
        label->setText(QString::number(value.toInt()));
    }
}

void TicketDialog::formatClockEdit(const QString &field,
                                   QLineEdit *edit,
                                   QCheckBox *checkBox)
{
    double clock = mModel->data(indexForField(field)).toDouble();
    if(clock < 0){
        checkBox->setChecked(false);
    }else{
        checkBox->setChecked(true);
    }
    edit->setText(QString::number(fabs(clock), 'f', 3));
}

void TicketDialog::setupModel()
{
    mModel = new TicketsModel(mVehicle, this);

    mMapper = new QDataWidgetMapper(this);

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

    mMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
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
    Observation* observation = new Observation();

    observation = mObservationsModel->observationForTime(ui->dateTimeEdit->dateTime());

    if(observation){
        mModel->setData(indexForField("temperature"),
                        observation->value("temperature"));
        mModel->setData(indexForField("humidity"),
                        observation->value("humidity"));
        mModel->setData(indexForField("pressure"),
                        observation->value("pressure"));
        mModel->setData(indexForField("vaporPressure"),
                        observation->value("vaporPressure"));
        mModel->setData(indexForField("dewPoint"),
                        observation->value("dewPoint"));
        mModel->setData(indexForField("densityAltitude"),
                        observation->value("densityAltitude"));
        mModel->setData(indexForField("windSpeed"),
                        observation->value("windSpeed"));
        mModel->setData(indexForField("windGust"),
                        observation->value("windGust"));
        mModel->setData(indexForField("windDirection"),
                        observation->value("windDirection"));
    }else{
        qDebug("Weather not found - WRITE CODE");
    }

    delete observation;

    updateDisplay();

    mDateTimer->stop();
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

void TicketDialog::onButtonBoxAccepted()
{
    handleClockGood(ui->sixtyEdit, ui->sixtyGoodCheckBox);
    handleClockGood(ui->threeThirtyEdit, ui->threeThirtyGoodCheckBox);
    handleClockGood(ui->eighthEdit, ui->eighthGoodCheckBox);
    handleClockGood(ui->thousandEdit, ui->thousandGoodCheckBox);
    handleClockGood(ui->quarterEdit, ui->quarterGoodCheckBox);

    mMapper->submit();
    mModel->submitAll();
    emit ready();
}

void TicketDialog::updateDisplay()
{
//    ui->temperature->setText(mModel->data(indexForField("temperature")).toString());
    formatNumberLabel(mModel->data(indexForField("temperature")),
                      ui->temperature,
                      1);
    formatNumberLabel(mModel->data(indexForField("humidity")),
                      ui->humidity,
                      1);
    formatNumberLabel(mModel->data(indexForField("pressure")),
                      ui->pressure,
                      2);
    formatNumberLabel(mModel->data(indexForField("vaporPressure")),
                      ui->vaporPressure,
                      2);
    formatNumberLabel(mModel->data(indexForField("dewPoint")),
                      ui->dewPoint,
                      1);
    formatNumberLabel(mModel->data(indexForField("densityAltitude")),
                      ui->densityAltitude,
                      0);
    formatNumberLabel(mModel->data(indexForField("windSpeed")),
                      ui->windSpeed,
                      0);
    formatNumberLabel(mModel->data(indexForField("windGust")),
                      ui->windGust,
                      0);
    formatNumberLabel(mModel->data(indexForField("windDirection")),
                      ui->windDirection,
                      0);

    TicketsModel *ticketsModel = new TicketsModel(mVehicle, this);

    Prediction prediction;

    prediction.setValue("dateTime", ui->dateTimeEdit->dateTime());
    prediction.setValue("vehicleId", mVehicle->value("id").toInt());
    prediction.setValue("raceId", mRace->value("id").toInt());
    prediction.setValue("trackId", mRace->value("trackId").toInt());
    prediction.setValue("ticketId", mId);
    prediction.setValue("riderWeight", ui->riderWeightSpinBox->value());
    prediction.setValue("vehicleWeight", ui->vehicleWeightSpinBox->value());
    prediction.setValue("windAdjustment", ui->windAdjustmentSpinBox->value());
    prediction.setValue("weightAdjustment", ui->weightAdjustmentSpinBox->value());

    prediction.predictClocks(ui->vehicleTicketsCheckBox->isChecked(),
                             ui->trackTicketsCheckBox->isChecked(),
                             ticketsModel);

    formatNumberLabel(prediction.value("sixtyD"), ui->sixtyD, 3);
    formatNumberLabel(prediction.value("threeThirtyD"), ui->threeThirtyD, 3);
    formatNumberLabel(prediction.value("eighthD"), ui->eighthD, 3);
    formatNumberLabel(prediction.value("thousandD"), ui->thousandD, 3);
    formatNumberLabel(prediction.value("quarterD"), ui->quarterD, 3);

    formatNumberLabel(prediction.value("sixtyA"), ui->sixtyA, 3);
    formatNumberLabel(prediction.value("threeThirtyA"), ui->threeThirtyA, 3);
    formatNumberLabel(prediction.value("eighthA"), ui->eighthA, 3);
    formatNumberLabel(prediction.value("thousandA"), ui->thousandA, 3);
    formatNumberLabel(prediction.value("quarterA"), ui->quarterA, 3);

    formatNumberLabel(prediction.value("sixtyT"), ui->sixtyT, 3);
    formatNumberLabel(prediction.value("threeThirtyT"), ui->threeThirtyT, 3);
    formatNumberLabel(prediction.value("eighthT"), ui->eighthT, 3);
    formatNumberLabel(prediction.value("thousandT"), ui->thousandT, 3);
    formatNumberLabel(prediction.value("quarterT"), ui->quarterT, 3);

    formatNumberLabel(prediction.value("sixtyH"), ui->sixtyH, 3);
    formatNumberLabel(prediction.value("threeThirtyH"), ui->threeThirtyH, 3);
    formatNumberLabel(prediction.value("eighthH"), ui->eighthH, 3);
    formatNumberLabel(prediction.value("thousandH"), ui->thousandH, 3);
    formatNumberLabel(prediction.value("quarterH"), ui->quarterH, 3);

    formatNumberLabel(prediction.value("sixtyP"), ui->sixtyP, 3);
    formatNumberLabel(prediction.value("threeThirtyP"), ui->threeThirtyP, 3);
    formatNumberLabel(prediction.value("eighthP"), ui->eighthP, 3);
    formatNumberLabel(prediction.value("thousandP"), ui->thousandP, 3);
    formatNumberLabel(prediction.value("quarterP"), ui->quarterP, 3);

    mFactorTimer->stop();
}

void TicketDialog::onShowPredictionsClicked()
{
    TicketsModel *ticketsModel = new TicketsModel(mVehicle, this);

    Prediction prediction;

    prediction.setValue("vehicleId", mVehicle->value("id").toInt());
    prediction.setValue("raceId", mRace->value("id").toInt());
    prediction.setValue("trackId", mRace->value("trackId").toInt());
    prediction.setValue("ticketId", mId);
    prediction.setValue("riderWeight", ui->riderWeightSpinBox->value());
    prediction.setValue("vehicleWeight", ui->vehicleWeightSpinBox->value());

    prediction.setValue("windAdjustment", ui->windAdjustmentSpinBox->value());
    prediction.setValue("weightAdjustment", ui->weightAdjustmentSpinBox->value());

    QDateTime ticketDateTime = ui->dateTimeEdit->dateTime();
    QTime ticketTime = ticketDateTime.time();
    QTime startTime = ticketTime.addSecs(-300);

    for(int i = 0; i < 11; i++){
        prediction.setValue("dateTime", QDateTime(ticketDateTime.date(),
                                                  startTime.addSecs(i * 60)));

        prediction.predictClocks(ui->vehicleTicketsCheckBox->isChecked(),
                                 ui->trackTicketsCheckBox->isChecked(),
                                 ticketsModel);

        mPredictionsModel->addRow(prediction);
    }
    TicketPredictionsDialog *ticketPredictionsDialog
            = new TicketPredictionsDialog(mPredictionsModel, this);

    ticketPredictionsDialog->exec();

    for(int r = 0;r < mPredictionsModel->rowCount(); r++){
        mPredictionsModel->removeRow(r);
    }
    mPredictionsModel->submitAll();
}

void TicketDialog::onDateChange()
{
    mDateTimer->start(1000);
}

void TicketDialog::onFactorChange()
{
    mFactorTimer->start(1000);
}
