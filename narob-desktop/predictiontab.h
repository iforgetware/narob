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
    void formatNumberLabel(const QVariant &value,
                           QLabel *label,
                           const int decimals);
    void updatePLabel(const QString &field,
                      QLabel *label);
    void writePredictionToDb();
    void updateDisplay();
    void sendPage();
    void mailSent(QString);

    Ui::PredictionTab* ui;
    Vehicle *mVehicle;
    Race *mRace;
    Settings *mSettingsTable;
    DbRecordBase *mSettings;
    PredictionsModel *mPredictionsModel;
    Prediction *mCurrentPrediction;
    TicketsModel *mTicketsModel;
    PreviousPredictionsWidget *mPreviousPredictionsWidget;
    QTimer *mAutoTimer;
    QTimer *mFactorTimer;

private slots:
    void onFactorChange();
    void makePrediction();
};

#endif // PREDICTIONTAB_H
