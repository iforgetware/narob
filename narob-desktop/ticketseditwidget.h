#ifndef TICKETSEDITWIDGET_H
#define TICKETSEDITWIDGET_H

#include "tickets.h"
#include "ticketsracemodel.h"
#include "tableeditwidgetbase.h"
#include "ui_tablewidgetbase.h"

#include "vehicles.h"
#include "races.h"

class TicketsEditWidget : public TableEditWidgetBase
{
    Q_OBJECT

public:
    explicit TicketsEditWidget(TicketsModel *model,
                               Vehicle* vehicle,
                               Race* race,
                               QWidget *parent = 0);

private slots:
    void addTicket();
    void editTicket();

private:
    TicketsModel *mTicketsModel;
    TicketsRaceModel* mTicketsRaceModel;

    Vehicle* mVehicle;
    Race* mRace;
};

#endif // TICKETEDITSWIDGET_H
