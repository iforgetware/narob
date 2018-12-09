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
                           QWidget *parent = nullptr);
    ~PredictionTab();
    void UpdateAllModels();

private:
    void writePredictionToDb();
    void updateDisplay();
    void sendPage();
    void pageLine(QString line, QString field, int decimals);
    void mailSent(QString);
    void formatNumberLabel(const QVariant &value,
                           QLabel *label,
                           const int decimals);
    void updatePLabel(const QString &field,
                      QLabel *label);

    Ui::PredictionTab* ui;
    Vehicle *mVehicle;
    Race *mRace;
    Settings *mSettingsTable;
    DbRecordBase *mSettings;
    TicketsModel *mTicketsModel;
    PredictionsModel *mPredictionsModel;
    Prediction mCurrentPrediction;
    PreviousPredictionsWidget *mPreviousPredictionsWidget;
    QString mPage;
    QTimer *mAutoTimer;
    QTimer *mFactorTimer;

private slots:
    void makePrediction();
    void onTrackTicketsCheckboxChange();
    void onVehicleTicketsCheckboxChange();
    void onFactorChange();
};

#endif // PREDICTIONTAB_H
