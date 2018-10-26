#include "weathertab.h"
#include "ui_weathertab.h"
#include "observationswidget.h"

#include <QTimer>

#include <QDebug>

WeatherTab::WeatherTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeatherTab),
    mObservationsModel(new ObservationsModel(this)),
    mObservationsWidget(new ObservationsWidget(this))
{
    ui->setupUi(this);

    ui->gridLayout->addWidget(mObservationsWidget, 0, 0);

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

    if(mWeatherStation->isRunning()){
        connect(mWeatherStation,
                &WeatherStation::newWeatherWritten,
                mObservationsWidget,
                &ObservationsWidget::updateModel);
    }
}
