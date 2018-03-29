#ifndef VEHICLES_H
#define VEHICLES_H

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

class Vehicles : public DbTableBase
{
public:
    explicit Vehicles();
};


class NAROBCORESHARED_EXPORT Vehicle : public DbRecordBase
{
public:
    explicit Vehicle();
};


class NAROBCORESHARED_EXPORT VehiclesModel : public ModelBase
{
    Q_OBJECT

public:
    explicit VehiclesModel(QObject *parent = 0);

    Vehicle *getVehicle(const int row);
};

#endif // VEHICLES_H
