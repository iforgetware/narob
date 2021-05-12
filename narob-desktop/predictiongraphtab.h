#ifndef PREDICTIONGRAPHTAB_H
#define PREDICTIONGRAPHTAB_H

#include <QWidget>
#include <QChartView>
#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>

#include "predictions.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class PredictionGraphTab;
}

class PredictionGraphTab : public QWidget
{
    Q_OBJECT

public:
    explicit PredictionGraphTab(Prediction *prediction,
                                QWidget *parent = nullptr);
    ~PredictionGraphTab();

public slots:
    void updateGraph();

private:
    void setupGraph();

    Ui::PredictionGraphTab *ui;
    Prediction *mCurrentPrediction;
    QChartView *mChartView;
    QLineSeries *mEighthMedian;
    QLineSeries *mQuarterMedian;
    QScatterSeries *mEighthRunsScatter;
    QScatterSeries *mQuarterRunsScatter;
    QScatterSeries *mECPScatter;
    QScatterSeries *mQCPScatter;
    QValueAxis *mEighthDAAxis;
    QValueAxis *mEighthETAxis;
    QValueAxis *mQuarterDAAxis;
    QValueAxis *mQuarterETAxis;
    bool mQuarterGraph;

private slots:
    void onLengthToggle();
};

#endif // PREDICTIONGRAPHTAB_H
