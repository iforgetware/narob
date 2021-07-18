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
    mXAxis(new QDateTimeAxis(mChartView)),
    mFactorTimer(new QTimer(this))
{
    ui->setupUi(this);

    ui->gridLayout->addWidget(mChartView, 0, 0);

    mChartView->setRenderHint(QPainter::Antialiasing);
    mChartView->chart()->setTitle("Weather Trends");
    mXAxis->setFormat("M/d h:mm AP");
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

    mDaysSpinBox = new QSpinBox(this);
    mDaysSpinBox->setSuffix(" Past Days of Weather");

    QFrame* controlFrame = new QFrame(this);
    QHBoxLayout* cFLayout = new QHBoxLayout(controlFrame);

    cFLayout->addSpacerItem(new QSpacerItem(1,
                                            1,
                                            QSizePolicy::Expanding,
                                            QSizePolicy::Fixed));
    cFLayout->addWidget(mDaysSpinBox);
    cFLayout->addSpacerItem(new QSpacerItem(1,
                                            1,
                                            QSizePolicy::Expanding,
                                            QSizePolicy::Fixed));

    controlFrame->setLayout(cFLayout);

    connect(mDaysSpinBox,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            &WeatherGraphWidget::onFactorChange);

    connect(mFactorTimer, &QTimer::timeout,
            this, &WeatherGraphWidget::handleGraphDaysChange);

    ui->gridLayout->addWidget(controlFrame);

    ObservationsModel observationsModel;

    auto observations = observationsModel.observationsForDays(0);

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

void WeatherGraphWidget::handleGraphDaysChange()
{
    mTTrace->clear();
    mHTrace->clear();
    mPTrace->clear();
    mDTrace->clear();

    mXAxis->setRange(QDateTime::currentDateTime().addSecs(60),
                     QDateTime::currentDateTime().addSecs(120));

    ObservationsModel observationsModel;

    auto observations = observationsModel.observationsForDays(mDaysSpinBox->value());

    for(auto&& observation : *observations)
    {
        handleNewWeather(*observation);
    }
}

void WeatherGraphWidget::onFactorChange()
{
    mFactorTimer->start(CHANGE_DELAY);
}
