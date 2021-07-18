#include "ticketpredictionsdialog.h"
#include "ui_ticketpredictionsdialog.h"

TicketPredictionsDialog::TicketPredictionsDialog(PredictionsModel *predictionsModel,
                                                 Prediction *predictedRun,
                                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TicketPredictionsDialog),
    mPredictionsModel(predictionsModel),
    mPredictionsWidget(new PredictionsWidget(mPredictionsModel,
                                             this))
{
    ui->setupUi(this);

    foreach(Prediction* prediction, predictedRun->adjacentPredictions()){
        mPredictionsModel->addRow(*prediction);
    }

    ui->gridLayout_2->addWidget(mPredictionsWidget, 0, 0);
}

TicketPredictionsDialog::~TicketPredictionsDialog()
{
    for(int r = 0; r < mPredictionsModel->rowCount(); r++){
        mPredictionsModel->removeRow(r);
    }

    mPredictionsModel->submitAll();

    delete ui;
}
