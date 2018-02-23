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

//    mTicketsModel->setRelation(mTicketsModel->fieldIndex("raceId"), QSqlRelation("races", "id", "name"));

//    if(trackId){
//        TicketsTrackModel* ticketsTrackModel = new TicketsTrackModel(trackId, this);
//        ticketsTrackModel->setSourceModel(mTicketsModel);
//        ui->tableView->setModel(ticketsTrackModel);
//    }else{
//        mTicketsModel->setRelation(mTicketsModel->fieldIndex("trackId"), QSqlRelation("tracks", "id", "name"));
        ui->tableView->setModel(mTicketsModel);
//    }

//    mTicketsModel->select();

    ui->tableView->setItemDelegate(new mySqlRelationalDelegate(this));
    ui->tableView->setItemDelegateForColumn(2, new mySqlRelationalDelegate(this));
    ui->tableView->setItemDelegateForColumn(3, new mySqlRelationalDelegate(this));


    setupColumns(mTicketsModel->mFields);

    hideColumn(mTicketsModel->fieldIndex("vehicleId"));
    hideColumn(mTicketsModel->fieldIndex("predictionId"));

    if(trackId){
        hideColumn(mTicketsModel->fieldIndex("trackId"));
    }

    initTable();
}
