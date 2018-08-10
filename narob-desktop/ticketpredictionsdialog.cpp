#include "ticketpredictionsdialog.h"
#include "ui_ticketpredictionsdialog.h"

TicketPredictionsDialog::TicketPredictionsDialog(PredictionsModel *model,
                                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TicketPredictionsDialog),
    mPredictionsModel(model)
{
    ui->setupUi(this);

    mPredictionsWidget = new PredictionsWidget(mPredictionsModel,
                                               this);

    ui->gridLayout_2->addWidget(mPredictionsWidget, 0, 0);
}

TicketPredictionsDialog::~TicketPredictionsDialog()
{
    delete ui;
}
