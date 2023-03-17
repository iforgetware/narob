#include "trackhistorywidget.h"

#include "delegates.h"

#include <QDebug>

TrackHistoryWidget::TrackHistoryWidget(std::shared_ptr<Vehicle> vehicle,
                                      int trackId,
                                      QWidget* parent) :
    TableDisplayWidgetBase("Tickets", parent)
{
    TicketsTrackModel* ticketsTrackModel = new TicketsTrackModel(vehicle->value("id").toInt(),
                                                                 trackId,
                                                                 this);
    ui->tableView->setModel(ticketsTrackModel);
    mModel = ticketsTrackModel;

    ui->tableView->setItemDelegateForColumn(mModel->fieldIndex("raceId"),
                                            new RaceColumnDelegate(this));

    setupColumns(TICKET_FIELDS);

    hide("vehicleId");
    hide("trackId");

    initTable();

    mModel->sort(mModel->fieldIndex("dateTime"), Qt::DescendingOrder);
}
