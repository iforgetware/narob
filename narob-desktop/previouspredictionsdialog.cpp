#include "previouspredictionsdialog.h"
#include "ui_previouspredictionsdialog.h"

PreviousPredictionsDialog::PreviousPredictionsDialog(PredictionsModel *predictionsModel,
                                                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviousPredictionsDialog),
    mPredictionsModel(predictionsModel),
    mPreviousPredictionsWidget(new PreviousPredictionsWidget(mPredictionsModel,
                                                             this))
{
    ui->setupUi(this);

    ui->gridLayout->addWidget(mPreviousPredictionsWidget, 0, 0);
}

PreviousPredictionsDialog::~PreviousPredictionsDialog()
{
    delete ui;
}
