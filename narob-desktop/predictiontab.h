#ifndef PREDICTIONTAB_H
#define PREDICTIONTAB_H

#include "modelbase.h"
#include "predictions.h"
#include "vehicles.h"
#include "races.h"
#include "tickets.h"
#include "observations.h"
#include "settings.h"
#include "previouspredictionswidget.h"

#include <QWidget>
#include <QTimer>

namespace Ui {
class PredictionTab;
}

class PredictionTab : public QWidget
{
    Q_OBJECT

public:
    explicit PredictionTab(TicketsModel* model,
                           Vehicle *vehicle,
                           Race *race,
                           QWidget *parent = 0);
    ~PredictionTab();
    void UpdateAllModels();

private:
    Ui::PredictionTab* ui;
    Vehicle* mVehicle;
    Race* mRace;
    QTimer* mAutoTimer;
    Settings *mSettingsTable;
    DbRecordBase *mSettings;
    PredictionsModel* mPredictionsModel;
    TicketsModel* mTicketsModel;
    PreviousPredictionsWidget *mPreviousPredictionsWidget;

    QString formatClock(const QVariant &clock);

private slots:
    void makePrediction();
    void writePredictionToDb(Prediction &prediction);
    void updateDisplay(const Prediction &prediction);
    void sendPage(const Prediction &prediction);
    void mailSent(QString);
};

#endif // PREDICTIONTAB_H
