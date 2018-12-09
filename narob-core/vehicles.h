#ifndef VEHICLES_H
#define VEHICLES_H

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

static Fields VEHICLE_FIELDS{Field("id", "id", 0, 0),
            Field("number", "Number", 70, -4),
            Field("compClass", "Class", 70, -4),
            Field("weight", "Weight", 60, 0),
            Field("windAdjustment", "Wn Adj", 60, 3),
            Field("weightAdjustment", "Wt Adj", 60, 3),
            Field("textNumber", "Text Number", 110, -4),
            Field("textProvider", "Text Provider", 110, -4)};


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
    explicit VehiclesModel(QObject *parent = nullptr);

    Vehicle *getVehicle(const int row);
};

#endif // VEHICLES_H
