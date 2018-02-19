#include "predictionswidget.h"

PredictionsWidget::PredictionsWidget(PredictionsModel* model,
                                     QWidget *parent) :
    TableWidgetBase(parent),
    mPredictionsModel(model)
{
    setTitle("Predictions");

    mModel = mPredictionsModel;

    ui->tableView->setModel(mPredictionsModel);

    setupColumns(mPredictionsModel->mFields);

    hideColumn(mPredictionsModel->fieldIndex("raceId"));
    hideColumn(mPredictionsModel->fieldIndex("vehicleId"));

    initTable();
}
