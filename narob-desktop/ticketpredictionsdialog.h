#ifndef TICKETPREDICTIONSDIALOG_H
#define TICKETPREDICTIONSDIALOG_H

#include "predictions.h"
#include "predictionswidget.h"

#include <QDialog>

namespace Ui {
class TicketPredictionsDialog;
}

class TicketPredictionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TicketPredictionsDialog(PredictionsModel *model,
                                     QWidget *parent = 0);
    ~TicketPredictionsDialog();

private:
    Ui::TicketPredictionsDialog *ui;
    PredictionsModel *mPredictionsModel;
    PredictionsWidget *mPredictionsWidget;
};

#endif // TICKETPREDICTIONSDIALOG_H
