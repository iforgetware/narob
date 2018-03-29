#ifndef PREDICTIONSWIDGET_H
#define PREDICTIONSWIDGET_H

#include "predictions.h"
#include "tabledisplaywidgetbase.h"
#include "ui_tablewidgetbase.h"

class PredictionsWidget : public TableDisplayWidgetBase
{
    Q_OBJECT

public:
    explicit PredictionsWidget(PredictionsModel *model,
                               QWidget* parent = 0);

private:
    PredictionsModel* mPredictionsModel;
};

#endif // PREDICTIONSWIDGET_H
