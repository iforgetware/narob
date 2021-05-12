#ifndef PREDICTIONTAB_H
#define PREDICTIONTAB_H

#include <memory>

#include "modelbase.h"
#include "vehicles.h"
#include "races.h"
#include "tickets.h"
#include "observations.h"
#include "currentpredictiontab.h"
#include "predictiongraphtab.h"
#include "previouspredictionstab.h"
#include "trace.h"

#include <QWidget>

namespace Ui {
class PredictionTab;
}

class PredictionTab : public QWidget
{
    Q_OBJECT

public:
    explicit PredictionTab(TicketsLogbookModel* model,
                           std::shared_ptr<Vehicle> vehicle,
                           std::shared_ptr<Race> race,
                           QWidget *parent = nullptr);
    ~PredictionTab();
    void UpdateAllModels();
    void UpdateGraph();

private:
    Ui::PredictionTab* ui;
    Prediction *mCurrentPrediction;
    TicketsLogbookModel *mTicketsLogbookModel;
    PredictionsModel *mPredictionsModel;
    CurrentPredictionTab *mCurrentPredictionTab;
    PredictionGraphTab *mPredictionGraphTab;
    PreviousPredictionsTab *mPreviousPredictionsTab;
};

#endif // PREDICTIONTAB_H
