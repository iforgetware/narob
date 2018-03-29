#include "ticketdialog.h"
#include "ui_ticketdialog.h"
#include "observations.h"

#include <QDebug>

TicketDialog::TicketDialog(Vehicle* vehicle,
                           Race* race,
                           int row,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TicketDialog),
    mVehicle(vehicle),
    mRace(race)
{
    ui->setupUi(this);

    setupModel();

    if(row == -1){
        mTicketsModel->insertRow(mTicketsModel->rowCount(QModelIndex()));

        QModelIndex vIndex = mTicketsModel->index(mTicketsModel->rowCount(QModelIndex()) - 1,
                                                  mTicketsModel->fieldIndex("vehicleId"));
        mTicketsModel->setData(vIndex, mVehicle->value("id").toInt());

        QModelIndex tIndex = mTicketsModel->index(mTicketsModel->rowCount(QModelIndex()) - 1,
                                                  mTicketsModel->fieldIndex("trackId"));
        mTicketsModel->setData(tIndex, mRace->value("trackId").toInt());

        QModelIndex rIndex = mTicketsModel->index(mTicketsModel->rowCount(QModelIndex()) - 1,
                                                  mTicketsModel->fieldIndex("raceId"));
        mTicketsModel->setData(rIndex, mRace->value("id").toInt());

        QModelIndex wIndex = mTicketsModel->index(mTicketsModel->rowCount(QModelIndex()) - 1,
                                                  mTicketsModel->fieldIndex("vehicleWeight"));
        mTicketsModel->setData(wIndex, mVehicle->value("weight").toInt());

        mMapper->toLast();
    }else{
        mMapper->setCurrentModelIndex(mTicketsModel->index(row, 0));
    }

    connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &TicketDialog::dateTimeChanged);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &TicketDialog::onButtonBoxAccepted);

    createUi();
}

TicketDialog::~TicketDialog()
{
    delete ui;
}

void TicketDialog::setupModel()
{
    mTicketsModel = new TicketsModel(mVehicle, this);

    mMapper = new QDataWidgetMapper(this);

    mMapper->setModel(mTicketsModel);

    mMapper->addMapping(ui->dateTimeEdit, mTicketsModel->fieldIndex("dateTime"));
    mMapper->addMapping(ui->laneComboBox, mTicketsModel->fieldIndex("lane"));
    mMapper->addMapping(ui->dialEdit, mTicketsModel->fieldIndex("dial"));
    mMapper->addMapping(ui->reactionEdit, mTicketsModel->fieldIndex("reaction"));
    mMapper->addMapping(ui->sixtyEdit, mTicketsModel->fieldIndex("sixty"));
    mMapper->addMapping(ui->threeThirtyEdit, mTicketsModel->fieldIndex("threeThirty"));
    mMapper->addMapping(ui->eighthEdit, mTicketsModel->fieldIndex("eighth"));
    mMapper->addMapping(ui->eighthMPHEdit, mTicketsModel->fieldIndex("eighthMPH"));
    mMapper->addMapping(ui->eighthGoodCheckBox, mTicketsModel->fieldIndex("eighthGood"));
    mMapper->addMapping(ui->thousandEdit, mTicketsModel->fieldIndex("thousand"));
    mMapper->addMapping(ui->quarterEdit, mTicketsModel->fieldIndex("quarter"));
    mMapper->addMapping(ui->quarterMPHEdit, mTicketsModel->fieldIndex("quarterMPH"));
    mMapper->addMapping(ui->quarterGoodCheckBox, mTicketsModel->fieldIndex("quarterGood"));
    mMapper->addMapping(ui->delayEdit, mTicketsModel->fieldIndex("delay"));
    mMapper->addMapping(ui->vehicleWeightEdit, mTicketsModel->fieldIndex("vehicleWeight"));
    mMapper->addMapping(ui->riderWeightEdit, mTicketsModel->fieldIndex("riderWeight"));
    mMapper->addMapping(ui->temperatureEdit, mTicketsModel->fieldIndex("temperature"));
    mMapper->addMapping(ui->humidityEdit, mTicketsModel->fieldIndex("humidity"));
    mMapper->addMapping(ui->pressureEdit, mTicketsModel->fieldIndex("pressure"));
    mMapper->addMapping(ui->vaporPressureEdit, mTicketsModel->fieldIndex("vaporPressure"));
    mMapper->addMapping(ui->dewPointEdit, mTicketsModel->fieldIndex("dewPoint"));
    mMapper->addMapping(ui->densityAltitudeEdit, mTicketsModel->fieldIndex("densityAltitude"));
    mMapper->addMapping(ui->windSpeedEdit, mTicketsModel->fieldIndex("windSpeed"));
    mMapper->addMapping(ui->windGustEdit, mTicketsModel->fieldIndex("windGust"));
    mMapper->addMapping(ui->windDirectionEdit, mTicketsModel->fieldIndex("windDirection"));

    mMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

void vInt(QLineEdit *edit)
{
    edit->setValidator(new QIntValidator(edit));
}

void vDouble(QLineEdit *edit, int d)
{
    edit->setValidator(new QDoubleValidator(0, 1000, d, edit));
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

void TicketDialog::onButtonBoxAccepted()
{
    mMapper->submit();
    mTicketsModel->submitAll();
    emit ready();
}

void TicketDialog::dateTimeChanged(const QDateTime &dateTime)
{
    Q_UNUSED(dateTime);

    setWeather();

    return;
}

void TicketDialog::setWeather()
{
    ObservationsModel* observationsModel = new ObservationsModel(this);
    Observation* observation = new Observation();

    observation = observationsModel->observationForTime(ui->dateTimeEdit->dateTime());

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
