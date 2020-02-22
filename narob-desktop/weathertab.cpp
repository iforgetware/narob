#include "weathertab.h"
#include "ui_weathertab.h"
#include "observationswidget.h"

#include "settings.h"

#include <QTimer>

#include <QDebug>

WeatherTab::WeatherTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeatherTab),
    mObservationsModel(new ObservationsModel(this)),
    mAdjustmentLabel(new QLabel(this)),
    mObservationsWidget(new ObservationsWidget(this)),
    mWeatherGraphWidget(new WeatherGraphWidget(this))
{
    ui->setupUi(this);

    mAdjustmentLabel->setFont(QFont("Cantarell", 20, QFont::Bold));

    ui->gridLayout->addWidget(mAdjustmentLabel, 0, 0, Qt::AlignCenter);
    ui->gridLayout->addWidget(mObservationsWidget, 1, 0);
    ui->gridLayout->addWidget(mWeatherGraphWidget, 2, 0);

    updateAdjustmentDisplay();
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
                &WeatherStation::newWeatherWritten,
                this,
                &WeatherTab::updateAdjustmentDisplay);

        connect(mWeatherStation,
                &WeatherStation::sendObservation,
                mWeatherGraphWidget,
                &WeatherGraphWidget::handleNewWeather);
    }
}

void WeatherTab::updateAdjustmentDisplay()
{
    QString aD = "Using ";

    if(Settings::get("useConsole").toBool()){
        aD +="console";
    }else{
        aD += "transmitter";
    }

    aD += " with ";

    if(Settings::get("useOffsets").toBool()){
        aD += " temperature offset: ";
        aD += QString::number(Settings::get("tempOffset").toDouble(), 'f', 3);
        aD += " and humidity offset: ";
        aD += QString::number(Settings::get("humOffset").toDouble(), 'f', 3);
    }else{
        aD += " no offsets";
    }

    aD +=".";

    mAdjustmentLabel->setText(aD);
}
