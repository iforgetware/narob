#include "observationswidget.h"

ObservationsWidget::ObservationsWidget(QWidget *parent) :
    TableDisplayWidgetBase("Observations", parent)
{
    mObservationsModel = new ObservationsModel(ui->tableView);

    mModel = mObservationsModel;

    ui->tableView->setModel(mObservationsModel);

    setupColumns(OBSERVATION_FIELDS);

    initTable();
}

