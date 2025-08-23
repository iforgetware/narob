#ifndef AUTOTAB_H
#define AUTOTAB_H

#include <memory>

#include "predictions.h"
#include "vehicles.h"
#include "tickets.h"
#include "races.h"
#include "observations.h"
//#include "trace.h"
#include "callout.h"

#include <QWidget>
#include <QTimer>
#include <QChartView>
#include <QLineSeries>
#include <QScatterSeries>
#include <QValueAxis>
#include <QLabel>



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

signals:
    void selectionUpdated();

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

    int mVehicleId;
    int mTrackId;
    int mRaceId;

    Prediction mCurrentPrediction;

    PredictionsModel *mPredictionsModel;
    TicketsLogbookModel *mTicketsLogbookModel;

    Observation mObservation;

    QString mPage;

    QTimer *mAutoTimer;
    QTimer *mFactorTimer;

    QChartView *mEChartView;
    QChartView *mQChartView;
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
    Callout *mEHoverInfo;
    Callout *mQHoverInfo;

private slots:
    void autoPredict();
    void makePrediction();
    void onAutoCheckboxChange();
    void onTrackTicketsCheckboxChange();
    void onVehicleTicketsCheckboxChange();
    void onFactorChange();
    void onShowPreviousPredictionsClicked();
    void onEPointHover(QPointF point, bool state);
    void onQPointHover(QPointF point, bool state);
    void onEPointClick(QPointF point);
    void onQPointClick(QPointF point);
};

#endif // AUTOTAB_H
