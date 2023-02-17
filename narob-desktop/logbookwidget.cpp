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
\
    setupColumns(TICKET_FIELDS);

    ui->tableView->setItemDelegateForColumn(mModel->fieldIndex("trackId"),
                                            new TrackColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(mModel->fieldIndex("raceId"),
                                            new RaceColumnDelegate(this));

    hide("vehicleId");

    initTable();
}
