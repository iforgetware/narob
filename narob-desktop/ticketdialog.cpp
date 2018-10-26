#include "ticketdialog.h"
#include "ui_ticketdialog.h"
#include "observations.h"
#include "ticketpredictionsdialog.h"

#include <math.h>

#include <QDebug>

TicketDialog::TicketDialog(Vehicle* vehicle,
                           Race* race,
                           int row,
                           QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::TicketDialog),
    mVehicle(vehicle),
    mRace(race),
    mObservation(new Observation()),
    mObservationsModel(new ObservationsModel(this)),
    mTicketsModel(new TicketsModel(vehicle, this)),
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

    mPredictedRun = new Prediction(mVehicle->value("id").toInt(),
                                   mRace->value("trackId").toInt(),
                                   mRace->value("id").toInt(),
                                   mId);

    if(row == -1){
        mModel->setData(indexForField("vehicleId"),
                        mVehicle->value("id").toInt());

        mModel->setData(indexForField("trackId"),
                        mRace->value("trackId").toInt());

        mModel->setData(indexForField("raceId"),
                        mRace->value("id").toInt());

        ui->vehicleWeightSpinBox->setValue(mVehicle->value("weight").toInt());
        ui->riderWeightSpinBox->setValue(mTicketsModel->lastWeight());

        QDateTime cDT;
        cDT.setDate(QDate::currentDate());
        cDT.setTime(QTime(QTime::currentTime().hour(),
                          QTime::currentTime().minute()));
        ui->dateTimeEdit->setDateTime(cDT);

        updateWeather();

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

        formatClockEdit("sixty", ui->sixtyEdit, ui->sixtyGoodCheckBox);
        formatClockEdit("threeThirty", ui->threeThirtyEdit, ui->threeThirtyGoodCheckBox);
        formatClockEdit("eighth", ui->eighthEdit, ui->eighthGoodCheckBox);
        formatClockEdit("thousand", ui->thousandEdit, ui->thousandGoodCheckBox);
        formatClockEdit("quarter", ui->quarterEdit, ui->quarterGoodCheckBox);
    }

    updateWeather();
    updatePrediction();

    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged,
            this, &TicketDialog::onDateChange);

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

    connect(mDateTimer, &QTimer::timeout,
            this, &TicketDialog::updateWeather);

    connect(mFactorTimer, &QTimer::timeout,
            this, &TicketDialog::updatePrediction);

    connect(ui->showPredictionsButton, &QPushButton::clicked,
            this, &TicketDialog::onShowPredictionsClicked);

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &TicketDialog::onButtonBoxAccepted);
}

TicketDialog::~TicketDialog()
{
    delete mDateTimer;
    delete mFactorTimer;
    delete ui;
}

void TicketDialog::setupModel()
{
    mModel = mTicketsModel;

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
// this should probably be rewritten to use the setWeather method in the
// ticket object
{
    mObservation = mObservationsModel->observationForTime(ui->dateTimeEdit->dateTime());

    if(mObservation){
        updateWValue("temperature");
        updateWValue("humidity");
        updateWValue("pressure");
        updateWValue("vaporPressure");
        updateWValue("dewPoint");
        updateWValue("densityAltitude");
        updateWValue("windSpeed");
        updateWValue("windGust");
        updateWValue("windDirection");
    }else{
        qDebug("Weather not found - WRITE CODE");
    }

    updateWLabel("temperature", ui->temperature, 1);
    updateWLabel("humidity", ui->humidity, 1);
    updateWLabel("pressure", ui->pressure, 2);
    updateWLabel("vaporPressure", ui->vaporPressure, 2);
    updateWLabel("dewPoint", ui->dewPoint, 1);
    updateWLabel("densityAltitude", ui->densityAltitude, 0);
    updateWLabel("windSpeed", ui->windSpeed, 0);
    updateWLabel("windGust", ui->windGust, 0);
    updateWLabel("windDirection", ui->windDirection, 0);

    mDateTimer->stop();

    updatePrediction();
}

void TicketDialog::updatePrediction()
{
    mPredictedRun->setValue("dateTime", ui->dateTimeEdit->dateTime());
    mPredictedRun->setValue("riderWeight", ui->riderWeightSpinBox->value());
    mPredictedRun->setValue("vehicleWeight", ui->vehicleWeightSpinBox->value());
    mPredictedRun->setValue("windAdjustment", ui->windAdjustmentSpinBox->value());
    mPredictedRun->setValue("weightAdjustment", ui->weightAdjustmentSpinBox->value());

    mPredictedRun->predictClocks(ui->vehicleTicketsCheckBox->isChecked(),
                                 ui->trackTicketsCheckBox->isChecked(),
                                 mTicketsModel);

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

void TicketDialog::updateWValue(const QString &field)
{
    mModel->setData(indexForField(field),
                    mObservation->value(field));
}

void TicketDialog::updatePLabel(const QString &field, QLabel *label)
{
    formatNumberLabel(mPredictedRun->value(field), label, 3);
}

void TicketDialog::updateWLabel(const QString &field, QLabel *label, const int decimals)
{
    formatNumberLabel(mModel->data(indexForField(field)),
                      label,
                      decimals);
}

void TicketDialog::onShowPredictionsClicked()
{
    PredictionsModel *predictionsModel = new PredictionsModel(mVehicle,
                                                              mRace,
                                                              mId,
                                                              this);

    Prediction prediction(mVehicle->value("id").toInt(),
                          mRace->value("trackId").toInt(),
                          mRace->value("id").toInt(),
                          mId);

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
                                 mTicketsModel);

        predictionsModel->addRow(prediction);
    }

    TicketPredictionsDialog *ticketPredictionsDialog
            = new TicketPredictionsDialog(predictionsModel, this);

    ticketPredictionsDialog->exec();

    for(int r = 0; r < predictionsModel->rowCount(); r++){
        predictionsModel->removeRow(r);
    }

    predictionsModel->submitAll();
}

void TicketDialog::onDateChange()
{
    mDateTimer->start(CHANGE_DELAY);
}

void TicketDialog::onFactorChange()
{
    mFactorTimer->start(CHANGE_DELAY);
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
