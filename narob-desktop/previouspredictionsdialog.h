#ifndef PREVIOUSPREDICTIONSDIALOG_H
#define PREVIOUSPREDICTIONSDIALOG_H

#include "predictions.h"
#include "previouspredictionswidget.h"

#include <QDialog>

namespace Ui {
class PreviousPredictionsDialog;
}

class PreviousPredictionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreviousPredictionsDialog(PredictionsModel *predictionsModel,
                                       QWidget *parent = nullptr);
    ~PreviousPredictionsDialog();

private:
    Ui::PreviousPredictionsDialog *ui;
    PredictionsModel *mPredictionsModel;
    PreviousPredictionsWidget *mPreviousPredictionsWidget;
};

#endif // PREVIOUSPREDICTIONSDIALOG_H
