#include "observationswidget.h"

ObservationsWidget::ObservationsWidget(QWidget *parent) :
    TableDisplayWidgetBase(parent)
{
    setTitle("Observations");

    mObservationsModel = new ObservationsModel(ui->tableView);

    mModel = mObservationsModel;

    ui->tableView->setModel(mObservationsModel);

    setupColumns(OBSERVATION_FIELDS);

    initTable();
}

