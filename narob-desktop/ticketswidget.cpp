#include "ticketswidget.h"
#include "ticketstrackmodel.h"

#include "delegates.h"

#include <QDebug>

TicketsWidget::TicketsWidget(TicketsModel *model,
                             int trackId,
                             QWidget* parent) :
    TableWidgetBase(parent),
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

    setupColumns(mTicketsModel->mFields);

    hideColumn(mTicketsModel->fieldIndex("vehicleId"));
    hideColumn(mTicketsModel->fieldIndex("predictionId"));

    if(trackId){
        hideColumn(mTicketsModel->fieldIndex("trackId"));
    }

    initTable();
}
