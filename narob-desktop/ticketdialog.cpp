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
    mObservationsModel(new ObservationsModel(this))
//    mRefPTsModel(new RefPTsModel(this))
{
    ui->setupUi(this);

    setupModel();

    createUi();

    setModelRow(row);

    mSettings = mSettingsTable->getSettings();

    ui->weightAdjustmentSpinBox->setValue(mSettings->value("weightAdjustment").toDouble());
    ui->windAdjustmentSpinBox->setValue(mSettings->value("windAdjustment").toDouble());

    QModelIndex iIndex = mModel->index(mRow,
                                       mModel->fieldIndex("id"));
    mId = mModel->data(iIndex).toInt();

    mPredictionsModel = new PredictionsModel(mVehicle,
                                             mRace,
                                             mId,
                                             this);

    if(row == -1){
        QModelIndex vIndex = mModel->index(mRow,
                                           mModel->fieldIndex("vehicleId"));
        mModel->setData(vIndex, mVehicle->value("id").toInt());

        QModelIndex tIndex = mModel->index(mRow,
                                           mModel->fieldIndex("trackId"));
        mModel->setData(tIndex, mRace->value("trackId").toInt());

        QModelIndex rIndex = mModel->index(mRow,
                                           mModel->fieldIndex("raceId"));
        mModel->setData(rIndex, mRace->value("id").toInt());

//        QModelIndex wIndex = mModel->index(mRow,
//                                           mModel->fieldIndex("vehicleWeight"));
//        mModel->setData(wIndex, mVehicle->value("weight").toInt());

        ui->vehicleWeightSpinBox->setValue(mVehicle->value("weight").toInt());

        TicketsModel *ticketsModel = new TicketsModel(mVehicle, this);
        ui->riderWeightSpinBox->setValue(ticketsModel->lastWeight());
        delete ticketsModel;

        QDateTime cDT;
        cDT.setDate(QDate::currentDate());
        cDT.setTime(QTime(QTime::currentTime().hour(), QTime::currentTime().minute()));
        ui->dateTimeEdit->setDateTime(cDT);

        setWeather(cDT);

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
        formatDoubleEdit("temperature", ui->temperatureEdit, 1);
        formatDoubleEdit("humidity", ui->humidityEdit, 1);
        formatDoubleEdit("pressure", ui->pressureEdit, 2);
        formatDoubleEdit("vaporPressure", ui->vaporPressureEdit, 2);
        formatDoubleEdit("dewpoint", ui->dewPointEdit, 1);

        formatClockEdit("sixty", ui->sixtyEdit, ui->sixtyGoodCheckBox);
        formatClockEdit("threeThirty", ui->threeThirtyEdit, ui->threeThirtyGoodCheckBox);
        formatClockEdit("eighth", ui->eighthEdit, ui->eighthGoodCheckBox);
        formatClockEdit("thousand", ui->thousandEdit, ui->thousandGoodCheckBox);
        formatClockEdit("quarter", ui->quarterEdit, ui->quarterGoodCheckBox);
    }

    Prediction prediction;
    updatePredictionDisplay(prediction);

    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &TicketDialog::setWeather);

    connect(ui->comparePredictionButton, &QPushButton::clicked,
            this, &TicketDialog::onComparePredictionClicked);

    connect(ui->showPredictionsButton, &QPushButton::clicked,
            this, &TicketDialog::onShowPredictionsClicked);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &TicketDialog::onButtonBoxAccepted);
}

TicketDialog::~TicketDialog()
{
    delete ui;
}

void TicketDialog::formatDoubleEdit(const QString &field,
                                    QLineEdit *edit,
                                    const int decimals)
{
    QModelIndex index = mModel->index(mRow,
                                      mModel->fieldIndex(field));
    double number = mModel->data(index).toDouble();
    edit->setText(QString::number(number, 'f', decimals));
}

void TicketDialog::formatDoubleLabel(const QString &field,
                                     QLabel *label,
                                     const int decimals)
{
    QModelIndex index = mModel->index(mRow,
                                      mModel->fieldIndex(field));
    double number = mModel->data(index).toDouble();
    label->setText(QString::number(number, 'f', decimals));
}

void TicketDialog::formatClockEdit(const QString &field,
                                   QLineEdit *edit,
                                   QCheckBox *checkBox)
{
    QModelIndex index = mModel->index(mRow,
                                      mModel->fieldIndex(field));
    double clock = mModel->data(index).toDouble();
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
    mMapper->addMapping(ui->temperatureEdit, mModel->fieldIndex("temperature"));
    mMapper->addMapping(ui->humidityEdit, mModel->fieldIndex("humidity"));
    mMapper->addMapping(ui->pressureEdit, mModel->fieldIndex("pressure"));
    mMapper->addMapping(ui->vaporPressureEdit, mModel->fieldIndex("vaporPressure"));
    mMapper->addMapping(ui->dewPointEdit, mModel->fieldIndex("dewPoint"));
    mMapper->addMapping(ui->densityAltitudeEdit, mModel->fieldIndex("densityAltitude"));
    mMapper->addMapping(ui->windSpeedEdit, mModel->fieldIndex("windSpeed"));
    mMapper->addMapping(ui->windGustEdit, mModel->fieldIndex("windGust"));
    mMapper->addMapping(ui->windDirectionEdit, mModel->fieldIndex("windDirection"));
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

void TicketDialog::setWeather(const QDateTime &dateTime)
{
    Observation* observation = new Observation();

    observation = mObservationsModel->observationForTime(dateTime);

    if(observation){
        ui->temperatureEdit->setText(QString::number(observation->value("temperature").toDouble()));
        ui->humidityEdit->setText(QString::number(observation->value("humidity").toDouble()));
        ui->pressureEdit->setText(QString::number(observation->value("pressure").toDouble()));
        ui->vaporPressureEdit->setText(QString::number(observation->value("vaporPressure").toDouble()));
        ui->dewPointEdit->setText(QString::number(observation->value("dewPoint").toDouble()));
        ui->densityAltitudeEdit->setText(QString::number(observation->value("densityAltitude").toInt()));
        ui->windSpeedEdit->setText(QString::number(observation->value("windSpeed").toInt()));
        ui->windGustEdit->setText(QString::number(observation->value("windGust").toInt()));
        ui->windDirectionEdit->setText(QString::number(observation->value("windDirection").toInt()));
    }else{
        qDebug("Weather not found - WRITE CODE");
    }

    delete observation;

    return;
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

void TicketDialog::onComparePredictionClicked()
{
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

//        QVector<RefPT> refPTList;
    prediction.predictClocks(ui->vehicleTicketsCheckBox->isChecked(),
                             ui->trackTicketsCheckBox->isChecked(),
                             ticketsModel);

//    mPredictionsModel->addRow(prediction);
//        int predictionId = mPredictionsModel->query().lastInsertId().toInt();

//        if(refPTList.count()){
//            foreach(RefPT refPT, refPTList){
//                refPT.setValue("predictionId", predictionId);
//                mRefPTsModel->addRow(refPT);
//            }
//        }

    updatePredictionDisplay(prediction);
}

QString TicketDialog::formatClock(const QVariant &clock)
{
    return QString::number(clock.toDouble(), 'f', 3);
}

void TicketDialog::updatePredictionDisplay(Prediction &prediction)
{
    ui->sixtyD->setText(formatClock(prediction.value("sixtyD")));
    ui->threeThirtyD->setText(formatClock(prediction.value("threeThirtyD")));
    ui->eighthD->setText(formatClock(prediction.value("eighthD")));
    ui->thousandD->setText(formatClock(prediction.value("thousandD")));
    ui->quarterD->setText(formatClock(prediction.value("quarterD")));

    ui->sixtyA->setText(formatClock(prediction.value("sixtyA")));
    ui->threeThirtyA->setText(formatClock(prediction.value("threeThirtyA")));
    ui->eighthA->setText(formatClock(prediction.value("eighthA")));
    ui->thousandA->setText(formatClock(prediction.value("thousandA")));
    ui->quarterA->setText(formatClock(prediction.value("quarterA")));

    ui->sixtyT->setText(formatClock(prediction.value("sixtyT")));
    ui->threeThirtyT->setText(formatClock(prediction.value("threeThirtyT")));
    ui->eighthT->setText(formatClock(prediction.value("eighthT")));
    ui->thousandT->setText(formatClock(prediction.value("thousandT")));
    ui->quarterT->setText(formatClock(prediction.value("quarterT")));

    ui->sixtyH->setText(formatClock(prediction.value("sixtyH")));
    ui->threeThirtyH->setText(formatClock(prediction.value("threeThirtyH")));
    ui->eighthH->setText(formatClock(prediction.value("eighthH")));
    ui->thousandH->setText(formatClock(prediction.value("thousandH")));
    ui->quarterH->setText(formatClock(prediction.value("quarterH")));

    ui->sixtyP->setText(formatClock(prediction.value("sixtyP")));
    ui->threeThirtyP->setText(formatClock(prediction.value("threeThirtyP")));
    ui->eighthP->setText(formatClock(prediction.value("eighthP")));
    ui->thousandP->setText(formatClock(prediction.value("thousandP")));
    ui->quarterP->setText(formatClock(prediction.value("quarterP")));
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
//        QTime predictionTime = startTime.addSecs(i * 60);
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
