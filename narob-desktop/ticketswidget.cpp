#include "ticketswidget.h"
//#include "ticketstrackmodel.h"

#include "delegates.h"

#include <QDebug>

TicketsWidget::TicketsWidget(TicketsModel *model,
                             int trackId,
                             QWidget* parent) :
    TableDisplayWidgetBase("Tickets", parent),
    mTicketsModel(model)
{
    mModel = mTicketsModel;

    if(trackId){
        TicketsTrackModel* ticketsTrackModel = new TicketsTrackModel(trackId, this);
        ticketsTrackModel->setSourceModel(mTicketsModel);
        ui->tableView->setModel(ticketsTrackModel);
    }else{
        ui->tableView->setModel(mTicketsModel);
    }

    setupColumns(TICKET_FIELDS);

    ui->tableView->setItemDelegateForColumn(mModel->fieldIndex("trackId"),
                                            new TrackColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(mModel->fieldIndex("raceId"),
                                            new RaceColumnDelegate(this));

    hide("vehicleId");

    if(trackId){
        hide("trackId");
    }

    initTable();
}
