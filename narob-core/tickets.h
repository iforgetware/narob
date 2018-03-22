#ifndef TICKETS_H
#define TICKETS_H

#include <QSqlRecord>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"
#include "vehicles.h"

#include "narob-core_global.h"

class Tickets : public DbTableBase
{
public:
    explicit Tickets();
};


class Ticket : public DbRecordBase
{
public:
    explicit Ticket();
};


class TicketsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit TicketsModel(Vehicle *vehicle,
                          QObject *parent = 0);


private:
    Vehicle *mVehicle;
};

#endif // TICKETS_H
