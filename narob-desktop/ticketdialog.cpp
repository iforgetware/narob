#include "ticketdialog.h"
#include "ui_ticketdialog.h"
#include "observations.h"

#include <QDebug>

TicketDialog::TicketDialog(Vehicle* vehicle,
                           Race* race,
                           int row,
                           QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::TicketDialog),
    mVehicle(vehicle),
    mRace(race),
    mObservationsModel(new ObservationsModel(this))
{
    ui->setupUi(this);

    setupModel();

    createUi();

    setModelRow(row);

    if(row == -1){
        QModelIndex vIndex = mModel->index(mModel->rowCount(QModelIndex()) - 1,
                                           mModel->fieldIndex("vehicleId"));
        mModel->setData(vIndex, mVehicle->value("id").toInt());

        QModelIndex tIndex = mModel->index(mModel->rowCount(QModelIndex()) - 1,
                                           mModel->fieldIndex("trackId"));
        mModel->setData(tIndex, mRace->value("trackId").toInt());

        QModelIndex rIndex = mModel->index(mModel->rowCount(QModelIndex()) - 1,
                                           mModel->fieldIndex("raceId"));
        mModel->setData(rIndex, mRace->value("id").toInt());

        QModelIndex wIndex = mModel->index(mModel->rowCount(QModelIndex()) - 1,
                                           mModel->fieldIndex("vehicleWeight"));
        mModel->setData(wIndex, mVehicle->value("weight").toInt());

        QDateTime cDT;
        cDT.setDate(QDate::currentDate());
        cDT.setTime(QTime(QTime::currentTime().hour(), QTime::currentTime().minute()));
        ui->dateTimeEdit->setDateTime(cDT);
        setWeather(cDT);
    }

    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &TicketDialog::setWeather);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogBase::onButtonBoxAccepted);
}

TicketDialog::~TicketDialog()
{
    delete ui;
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
    mMapper->addMapping(ui->eighthGoodCheckBox, mModel->fieldIndex("eighthGood"));
    mMapper->addMapping(ui->thousandEdit, mModel->fieldIndex("thousand"));
    mMapper->addMapping(ui->quarterEdit, mModel->fieldIndex("quarter"));
    mMapper->addMapping(ui->quarterMPHEdit, mModel->fieldIndex("quarterMPH"));
    mMapper->addMapping(ui->quarterGoodCheckBox, mModel->fieldIndex("quarterGood"));
    mMapper->addMapping(ui->delayEdit, mModel->fieldIndex("delay"));
    mMapper->addMapping(ui->vehicleWeightEdit, mModel->fieldIndex("vehicleWeight"));
    mMapper->addMapping(ui->riderWeightEdit, mModel->fieldIndex("riderWeight"));
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
    vInt(ui->vehicleWeightEdit);
    vDouble(ui->riderWeightEdit, 1);
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
