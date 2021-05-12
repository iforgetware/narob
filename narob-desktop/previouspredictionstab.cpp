#include "previouspredictionstab.h"
#include "ui_previouspredictionstab.h"

PreviousPredictionsTab::PreviousPredictionsTab(PredictionsModel *model,
                                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviousPredictionsTab),
    mPreviousPredictionsWidget(new PreviousPredictionsWidget(
                                   model,
                                   this))
{
    ui->setupUi(this);

    ui->gridLayout->addWidget(mPreviousPredictionsWidget, 0, 0);}

PreviousPredictionsTab::~PreviousPredictionsTab()
{
    delete ui;
}

void PreviousPredictionsTab::updateModel()
{
    mPreviousPredictionsWidget->updateModel();
}
