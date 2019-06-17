#include "weathergraphwidget.h"
#include "ui_weathergraphwidget.h"

#include "observations.h"

#include <QValueAxis>
#include <QDateTimeAxis>
#include <QThread>

#include <QDebug>

WeatherGraphWidget::WeatherGraphWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeatherGraphWidget),
    mChartView(new QChartView(new QChart(), this)),
    mXAxis(new QDateTimeAxis(mChartView))
{
    ui->setupUi(this);

    ui->gridLayout->addWidget(mChartView, 0, 0);

    mChartView->setRenderHint(QPainter::Antialiasing);
    mChartView->chart()->setTitle("Weather Trends");
    mXAxis->setFormat("h:mm AP");
    mChartView->chart()->addAxis(mXAxis, Qt::AlignBottom);
    mXAxis->setRange(QDateTime::currentDateTime().addSecs(60),
                     QDateTime::currentDateTime().addSecs(120));

    mTTrace = new Trace("L",
                        mChartView,
                        mXAxis,
                        "Temperature",
                        1.0,
                        Qt::AlignLeft,
                        T_COLOR,
                        this);

    mHTrace = new Trace("L",
                        mChartView,
                        mXAxis,
                        "Humidity",
                        1.0,
                        Qt::AlignLeft,
                        H_COLOR,
                        this);

    mPTrace = new Trace("L",
                        mChartView,
                        mXAxis,
                        "Pressure",
                        0.01,
                        Qt::AlignRight,
                        P_COLOR,
                        this);

    mDTrace = new Trace("L",
                        mChartView,
                        mXAxis,
                        "Density Altitude",
                        10,
                        Qt::AlignRight,
                        D_COLOR,
                        this);

    ObservationsModel observationsModel;

    auto observations = observationsModel.observationsForToday();

    for(auto&& observation : *observations)
    {
        handleNewWeather(*observation);
    }
}

WeatherGraphWidget::~WeatherGraphWidget()
{
    delete ui;
}

void WeatherGraphWidget::handleNewWeather(Observation o)
{
    QDateTime xDateTime = o.value("dateTime").toDateTime();

    if(xDateTime < mXAxis->min()){
        mXAxis->setMin(xDateTime);
    }

    if(xDateTime > mXAxis->max()){
        mXAxis->setMax(xDateTime);
    }

    qint64 xMS = xDateTime.toMSecsSinceEpoch();

    mTTrace->newPoint(xMS, o.value("temperature").toDouble());
    mHTrace->newPoint(xMS, o.value("humidity").toDouble());
    mPTrace->newPoint(xMS, o.value("pressure").toDouble());
    mDTrace->newPoint(xMS, o.value("densityAltitude").toDouble());
}
