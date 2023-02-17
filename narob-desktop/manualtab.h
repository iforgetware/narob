#ifndef MANUALTAB_H
#define MANUALTAB_H

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
class ManualTab;
}

class ManualTab : public QWidget
{
    Q_OBJECT

public:
    explicit ManualTab(TicketsLogbookModel* tLModel,
                       std::shared_ptr<Vehicle> vehicle,
                       std::shared_ptr<Race> race,
                       QWidget *parent = nullptr);
    ~ManualTab();

public slots:
    void updateAllModels();

private:
    void setupGraph();
    void updateDisplay();
    void updateGraph();
    void updatePLabel(const QString &field,
                      QLabel *label);

    Ui::ManualTab *ui;

    Prediction mCurrentPrediction;

    PredictionsModel *mPredictionsModel;
    TicketsLogbookModel *mTicketsLogbookModel;

    Observation mObservation;

    QTimer *mFactorTimer;

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
    void makePrediction();
    void onTrackTicketsCheckboxChange();
    void onVehicleTicketsCheckboxChange();
    void onFactorChange();
    void onLengthToggle();
};

#endif // MANUALTAB_H
