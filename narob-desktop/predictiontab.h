#ifndef PREDICTIONTAB_H
#define PREDICTIONTAB_H

#include "modelbase.h"
#include "predictions.h"
#include "vehicles.h"
#include "races.h"
#include "tickets.h"
#include "observations.h"
#include "refpts.h"
#include "settings.h"

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

private:
    void getWeather(Prediction &prediction);
    QVector<Ticket*> validTickets(const QString &distance);
    void predictEighth(Prediction &prediction);
    void predictQuarter(Prediction &prediction);
    double windCorrection(int windSpeed, int windDirection);
    double weightCorrection(double w1, double w2);

    Ui::PredictionTab* ui;
    Vehicle* mVehicle;
    Race* mRace;
    QTimer* mAutoTimer;
    Settings *mSettingsTable;
    DbRecordBase *mSettings;
    PredictionsModel* mPredictionsModel;
    TicketsModel* mTicketsModel;
    ObservationsModel* mObservationsModel;
    RefPTsModel* mRefPTsModel;
    QVector<RefPT> mRefPTList;

private slots:
    void resetTimer(int);
    void makePrediction();
    void sendPage(const Prediction &prediction);
    void mailSent(QString);
};

#endif // PREDICTIONTAB_H
