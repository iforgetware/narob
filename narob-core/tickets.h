#ifndef TICKETS_H
#define TICKETS_H

#include <QVector>

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


class NAROBCORESHARED_EXPORT Ticket : public DbRecordBase
{
public:
    explicit Ticket();
};


class NAROBCORESHARED_EXPORT TicketsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit TicketsModel(Vehicle *vehicle,
                          QObject *parent = 0);
    QVector<Ticket*> tickets();

private:
    Vehicle *mVehicle;
};

#endif // TICKETS_H
