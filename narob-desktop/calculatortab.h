#ifndef CALCULATORTAB_H
#define CALCULATORTAB_H

#include <memory>

#include "predictions.h"
#include "vehicles.h"
#include "tickets.h"
#include "races.h"
#include "observations.h"
#include "trace.h"

#include <QWidget>
#include <QTimer>
#include <QChartView>
#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>
#include <QLabel>


QT_CHARTS_USE_NAMESPACE

namespace Ui {
class CalculatorTab;
}

class CalculatorTab : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorTab(TicketsLogbookModel* tLModel,
                           std::shared_ptr<Vehicle> vehicle,
                           std::shared_ptr<Race> race,
                           QWidget *parent = nullptr);
    ~CalculatorTab();

private:
    void setupGraph();
    void updateDisplay();
    void formatNumberLabel(const QVariant &value,
                           QLabel *label,
                           const int decimals);
    void updatePLabel(const QString &field,
                      QLabel *label);

    Ui::CalculatorTab *ui;
    TicketsLogbookModel *mTicketsLogbookModel;
    PredictionsModel *mPredictionsModel;
    Observation mObservation;
    Prediction mCurrentPrediction;
    QTimer *mFactorTimer;
    QChartView *mChartView;
    QLineSeries *mEighthMedian;
    QLineSeries *mQuarterMedian;
    QScatterSeries *mEighthRunsScatter;
    QScatterSeries *mQuarterRunsScatter;
    QValueAxis *mEighthDAAxis;
    QValueAxis *mEighthETAxis;
    QValueAxis *mQuarterDAAxis;
    QValueAxis *mQuarterETAxis;
    bool mQuarterGraph;

private slots:
    void makePrediction();
    void onTrackTicketsCheckboxChange();
    void onVehicleTicketsCheckboxChange();
    void onFactorChange();
    void onLengthToggle();
};

#endif // CALCULATORTAB_H
