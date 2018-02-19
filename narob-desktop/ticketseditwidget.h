#ifndef TICKETSEDITWIDGET_H
#define TICKETSEDITWIDGET_H

#include "ticketsmodel.h"
#include "ticketsracemodel.h"
#include "tableeditwidgetbase.h"
#include "ui_tableeditwidgetbase.h"

#include "vehicle.h"
#include "race.h"

using namespace std;

class TicketsEditWidget : public TableEditWidgetBase
{
    Q_OBJECT

public:
    explicit TicketsEditWidget(TicketsModel* model,
                               Vehicle* vehicle,
                               Race* race,
                               QWidget *parent = 0);

private slots:
    void addTicket();
    void editTicket();
    void deleteTicket();

private:
    TicketsModel *mTicketsModel;
    TicketsRaceModel* mTicketsRaceModel;

    Vehicle* mVehicle;
    Race* mRace;
};

#endif // TICKETEDITSWIDGET_H
