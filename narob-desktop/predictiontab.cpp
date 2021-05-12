#include "predictiontab.h"
#include "ui_predictiontab.h"
#include "predictions.h"

#include <QDebug>
#include <QVector>

PredictionTab::PredictionTab(TicketsLogbookModel *tLModel,
                             std::shared_ptr<Vehicle> vehicle,
                             std::shared_ptr<Race> race,
                             QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PredictionTab),
    mCurrentPrediction(new Prediction(tLModel,
                                      vehicle->value("id").toInt(),
                                      race->value("trackId").toInt(),
                                      race->value("id").toInt(),
                                      0)),
    mTicketsLogbookModel(tLModel),
    mPredictionsModel(new PredictionsModel(vehicle->value("id").toInt(),
                                           race->value("id").toInt(),
                                           0,
                                           this)),
    mCurrentPredictionTab(new CurrentPredictionTab(mCurrentPrediction,
                                                   tLModel,
                                                   mPredictionsModel,
                                                   vehicle,
                                                   this)),
    mPredictionGraphTab(new PredictionGraphTab(mCurrentPrediction,
                                               this)),
    mPreviousPredictionsTab(new PreviousPredictionsTab(mPredictionsModel,
                                                       this))
{
    ui->setupUi(this);

    ui->tabWidget->setTabsClosable(false);

    ui->tabWidget->addTab(mCurrentPredictionTab, "Current Prediction");
    ui->tabWidget->addTab(mPredictionGraphTab, "Prediction Graph");
    ui->tabWidget->addTab(mPreviousPredictionsTab, "Previous Predictions");

    connect(mCurrentPredictionTab,
            &CurrentPredictionTab::predictionUpdated,
            mPredictionGraphTab,
            &PredictionGraphTab::updateGraph);

    connect(mCurrentPredictionTab,
            &CurrentPredictionTab::predictionWrittenToDB,
            mPreviousPredictionsTab,
            &PreviousPredictionsTab::updateModel);

}

PredictionTab::~PredictionTab()
{
    delete ui;
}

void PredictionTab::UpdateAllModels()
{
    mPredictionGraphTab->updateGraph();
    mPreviousPredictionsTab->updateModel();
}

void PredictionTab::UpdateGraph()
{
    mPredictionGraphTab->updateGraph();
}
