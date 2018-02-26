#ifndef PREDICTIONTAB_H
#define PREDICTIONTAB_H

#include "modelbase.h"
#include "prediction.h"
#include "vehicle.h"
#include "race.h"
#include "predictionsmodel.h"
#include "ticketsmodel.h"
#include "observationsmodel.h"
#include "refptmodel.h"

#include "settingsmodel.h"

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
    void getWeather(Prediction* prediction);
    QVector<Ticket*> validTickets(const QString &distance);
    void predictEighth(Prediction *prediction);
    void predictQuarter(Prediction *prediction);
    double windCorrection(int windSpeed, int windDirection);
    double weightCorrection(double w1, double w2);

    Ui::PredictionTab* ui;
    Vehicle* mVehicle;
    Race* mRace;
    QTimer* mAutoTimer;
    Settings* mSettings;
    PredictionsModel* mPredictionsModel;
    TicketsModel* mTicketsModel;
    ObservationsModel* mObservationsModel;
    RefPTModel* mRefPTModel;

private slots:
    void resetTimer(int);
    void makeAutoPrediction();
    void sendPage(const Prediction *prediction);
    void mailSent(QString);
};

#endif // PREDICTIONTAB_H
