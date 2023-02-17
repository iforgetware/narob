#ifndef AUTOTAB_H
#define AUTOTAB_H

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
class AutoTab;
}

class AutoTab : public QWidget
{
    Q_OBJECT

public:
    explicit AutoTab(TicketsLogbookModel *tLModel,
                     std::shared_ptr<Vehicle> vehicle,
                     std::shared_ptr<Race> race,
                     QWidget *parent = nullptr);
    ~AutoTab();

public slots:
    void updateAllModels();

private:
    void startAutoTimer();
    void stopAutoTimer();
    void setupGraph();
    void updateDisplay();
    void updateGraph();
    void updatePLabel(const QString &field,
                      QLabel *label);

    void writePredictionToDb();
    void sendPage();
    void pageLine(QString line, QString field, int decimals);
    void mailSent(QString);

    Ui::AutoTab *ui;

    Prediction mCurrentPrediction;

    PredictionsModel *mPredictionsModel;
    TicketsLogbookModel *mTicketsLogbookModel;

    Observation mObservation;

    QString mPage;

    QTimer *mAutoTimer;
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
    void autoPredict();
    void makePrediction();
    void onAutoCheckboxChange();
    void onTrackTicketsCheckboxChange();
    void onVehicleTicketsCheckboxChange();
    void onFactorChange();
    void onLengthToggle();
    void onShowPreviousPredictionsClicked();
};

#endif // AUTOTAB_H
