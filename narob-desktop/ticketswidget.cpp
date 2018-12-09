#include "ticketswidget.h"
//#include "ticketstrackmodel.h"

#include "delegates.h"

#include <QDebug>

TicketsWidget::TicketsWidget(TicketsModel *model,
                             int trackId,
                             QWidget* parent) :
    TableDisplayWidgetBase(parent),
    mTicketsModel(model)
{
    setTitle("Tickets");

    mModel = mTicketsModel;

    if(trackId){
        TicketsTrackModel* ticketsTrackModel = new TicketsTrackModel(trackId, this);
        ticketsTrackModel->setSourceModel(mTicketsModel);
        ui->tableView->setModel(ticketsTrackModel);
    }else{
        ui->tableView->setModel(mTicketsModel);
    }

    ui->tableView->setItemDelegateForColumn(2, new TrackColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(3, new RaceColumnDelegate(this));

    setupColumns(TICKET_FIELDS);

    hide("vehicleId");
    hide("predictionId");

    if(trackId){
        hide("trackId");
    }

    initTable();
}
