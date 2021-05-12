#ifndef WEATHERGRAPHWIDGET_H
#define WEATHERGRAPHWIDGET_H

#include <QWidget>
#include <QChartView>
#include <QLineSeries>
#include <QScatterSeries>
#include <QDateTimeAxis>
#include <QTimer>
#include <QSpinBox>

#include "observations.h"
#include "trace.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class WeatherGraphWidget;
}

class WeatherGraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherGraphWidget(QWidget *parent = nullptr);
    ~WeatherGraphWidget();

private:
    Ui::WeatherGraphWidget *ui;

    QChartView *mChartView;

    QDateTimeAxis *mXAxis;

    Trace *mTTrace;
    Trace *mHTrace;
    Trace *mPTrace;
    Trace *mDTrace;

    QSpinBox *mDaysSpinBox;
    QTimer *mFactorTimer;

public slots:
    void handleNewWeather(Observation o);

private slots:
    void onFactorChange();
    void handleGraphDaysChange();
};

#endif // WEATHERGRAPHWIDGET_H
