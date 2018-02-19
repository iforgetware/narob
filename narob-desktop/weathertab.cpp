#include "weathertab.h"
#include "ui_weathertab.h"
#include "weatherstation.h"
#include "observationswidget.h"

#include <QTimer>

#include <QDebug>

WeatherTab::WeatherTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeatherTab),
    mObservationsModel(new ObservationsModel(this)),
    mObservationsWidget(new ObservationsWidget(mObservationsModel, this))
{
    ui->setupUi(this);

    //mObservationsWidget = new ObservationsWidget(mObservationsModel, this);
    ui->gridLayout->addWidget(mObservationsWidget, 0, 0);

    startWeatherStation();

//    observationsModel = new ObservationsModel();
//    ui->observationsPanel->setTitle("Observations");
//    ui->observationsPanel->initModel(observationsModel);
//    ui->observationsPanel->setHeaderWidths(observationsModel->mHeaders);

//    QTimer *weatherTimer = new QTimer(this);
//    connect(weatherTimer, SIGNAL(timeout()), observationsModel, SLOT(select()));
//    weatherTimer->start(60000);
}

WeatherTab::~WeatherTab()
{
    delete ui;
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
                &ObservationsWidget::refresh);
    }
}
