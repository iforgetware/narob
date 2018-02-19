#ifndef TICKETSMODEL_H
#define TICKETSMODEL_H

#include <QVector>

#include "narob-core_global.h"
#include "modelbase.h"
#include "ticket.h"
#include "vehicle.h"
#include "databasemanager.h"

class NAROBCORESHARED_EXPORT TicketsModel : public ModelBase
{
    Q_OBJECT

public:
    TicketsModel(Vehicle* vehicle,
                 QObject* parent = 0);

    QModelIndex addTicket(const Ticket &ticket);

    QVector<Ticket*> tickets(){ return mTickets; }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

private:
    DatabaseManager &mDb;
    Vehicle* mVehicle;
    QVector<Ticket*> mTickets;
};

#endif // TICKETSMODEL_H
