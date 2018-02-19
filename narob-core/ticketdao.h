#ifndef TICKETDAO_H
#define TICKETDAO_H

#include <QSqlDatabase>
#include <QVector>

#include "ticket.h"

class TicketDao
{
public:
    TicketDao(QSqlDatabase &database);

    void init() const;

    void addTicket(Ticket &ticket) const;
    void removeTicket(int id) const;
    QVector<Ticket*> ticketsForVehicle(int vehicleId) const;

private:
    QSqlDatabase &mDatabase;
};

#endif // TICKETDAO_H
