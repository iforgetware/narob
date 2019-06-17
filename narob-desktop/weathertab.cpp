#include "weathertab.h"
#include "ui_weathertab.h"
#include "observationswidget.h"

#include <QTimer>

#include <QDebug>

WeatherTab::WeatherTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeatherTab),
    mObservationsModel(new ObservationsModel(this)),
    mObservationsWidget(new ObservationsWidget(this)),
    mWeatherGraphWidget(new WeatherGraphWidget(this))
{
    ui->setupUi(this);

    ui->gridLayout->addWidget(mObservationsWidget, 0, 0);
    ui->gridLayout->addWidget(mWeatherGraphWidget, 1, 0);

    startWeatherStation();
}

WeatherTab::~WeatherTab()
{
    delete ui;
}

void WeatherTab::updateAllModels()
{
    mObservationsWidget->updateModel();
}

void WeatherTab::startWeatherStation()
{
    mWeatherStation = new WeatherStation(mObservationsModel, this);

    connect(mWeatherStation,
            &WeatherStation::sendStatus,
            this,
            &WeatherTab::sendStatus);

    //mWeatherStation->openComPort();

    if(mWeatherStation->isRunning()){
        connect(mWeatherStation,
                &WeatherStation::newWeatherWritten,
                mObservationsWidget,
                &ObservationsWidget::updateModel);

        connect(mWeatherStation,
                &WeatherStation::sendObservation,
                mWeatherGraphWidget,
                &WeatherGraphWidget::handleNewWeather);
    }
}
