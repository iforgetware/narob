#include "logbookwidget.h"

#include "delegates.h"

#include <QDebug>

LogbookWidget::LogbookWidget(TicketsLogbookModel *tLModel,
                             QWidget* parent) :
    TableDisplayWidgetBase("Tickets", parent),
    mTicketsLogbookModel(tLModel)
{
    mModel = mTicketsLogbookModel;

    ui->tableView->setModel(mModel);

    ui->tableView->setItemDelegateForColumn(mModel->fieldIndex("trackId"),
                                            new TrackColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(mModel->fieldIndex("raceId"),
                                            new RaceColumnDelegate(this));

    setupColumns(TICKET_FIELDS);

    hide("vehicleId");

    initTable();

    mModel->sort(mModel->fieldIndex("dateTime"), Qt::DescendingOrder);
}
