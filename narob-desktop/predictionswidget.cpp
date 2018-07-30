#include "predictionswidget.h"

PredictionsWidget::PredictionsWidget(PredictionsModel *model,
                                     QWidget *parent) :
    TableDisplayWidgetBase(parent),
    mPredictionsModel(model)
{
    setTitle("Predictions");

    mModel = mPredictionsModel;

    ui->tableView->setModel(mPredictionsModel);

    setupColumns(mPredictionsModel->fields());

    hide("raceId");
    hide("vehicleId");

    hide("eTp");
    hide("eHp");
    hide("ePp");

    hide("qTp");
    hide("qHp");
    hide("qPp");

    initTable();
}
