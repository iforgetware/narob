#ifndef PREVIOUSPREDICTIONSTAB_H
#define PREVIOUSPREDICTIONSTAB_H

#include <QWidget>

#include "previouspredictionswidget.h"
namespace Ui {
class PreviousPredictionsTab;
}

class PreviousPredictionsTab : public QWidget
{
    Q_OBJECT

public:
    explicit PreviousPredictionsTab(PredictionsModel *model,
                                    QWidget *parent = nullptr);
    ~PreviousPredictionsTab();

public slots:
    void updateModel();

private:
    Ui::PreviousPredictionsTab *ui;
    PreviousPredictionsWidget *mPreviousPredictionsWidget;
};

#endif // PREVIOUSPREDICTIONSTAB_H
