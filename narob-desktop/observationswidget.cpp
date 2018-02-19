#include "observationswidget.h"

ObservationsWidget::ObservationsWidget(ObservationsModel *model, QWidget *parent) :
    TableWidgetBase(parent),
    mObservationsModel(model)
{
    setTitle("Observations");

    mModel = mObservationsModel;

    ui->tableView->setModel(mObservationsModel);

    setupColumns(mObservationsModel->mFields);

    initTable();
}

