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

    hideColumn(mPredictionsModel->fieldIndex("eTp"));
    hideColumn(mPredictionsModel->fieldIndex("eHp"));
    hideColumn(mPredictionsModel->fieldIndex("ePp"));

    hideColumn(mPredictionsModel->fieldIndex("qTp"));
    hideColumn(mPredictionsModel->fieldIndex("qHp"));
    hideColumn(mPredictionsModel->fieldIndex("qPp"));

    initTable();
}
