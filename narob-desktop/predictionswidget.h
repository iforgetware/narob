#ifndef PREDICTIONSWIDGET_H
#define PREDICTIONSWIDGET_H

#include "predictionsmodel.h"
#include "tablewidgetbase.h"
#include "ui_tablewidgetbase.h"

class PredictionsWidget : public TableWidgetBase
{
    Q_OBJECT

public:
    explicit PredictionsWidget(PredictionsModel* model,
                               QWidget* parent = 0);

private:
    PredictionsModel* mPredictionsModel;
};

#endif // PREDICTIONSWIDGET_H
