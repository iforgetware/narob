#ifndef TICKETSEDITWIDGET_H
#define TICKETSEDITWIDGET_H

#include <memory>

#include "tickets.h"
#include "tableeditwidgetbase.h"
#include "ui_tablewidgetbase.h"

#include "vehicles.h"
#include "races.h"

class TicketsEditWidget : public TableEditWidgetBase
{
    Q_OBJECT

public:
    explicit TicketsEditWidget(TicketsLogbookModel *tLModel,
                               std::shared_ptr<Vehicle> vehicle,
                               std::shared_ptr<Race> race,
                               QWidget *parent = nullptr);


private slots:
    void addTicket();
    void editTicket();

private:
    TicketsLogbookModel* mTicketsLogbookModel;
    TicketsRaceModel* mTicketsRaceModel;

    std::shared_ptr<Vehicle> mVehicle;
    std::shared_ptr<Race> mRace;
};

#endif // TICKETEDITSWIDGET_H
