#ifndef VEHICLES_H
#define VEHICLES_H

#include <memory>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

const Fields VEHICLE_FIELDS{
            Field("id", "id", 0, 0),

            Field("number", "Number", 70, -4),
            Field("compClass", "Class", 70, -4),
            Field("weight", "Weight", 60, 0),

            Field("windAdjustment", "Wn Adj", 60, 3),
            Field("weightAdjustment", "Wt Adj", 60, 3),
            Field("textNumber", "Text Number", 110, -4),
            Field("textProvider", "Text Provider", 110, -4),

            Field("lastOilChange", "Last Oil Change", 160, -3),
            Field("lastTireChange", "Last Tire Change", 160, -3)};


class Vehicles : public DbTableBase
{
public:
    explicit Vehicles();
};


class NAROBCORESHARED_EXPORT Vehicle : public DbRecordBase
{
public:
    explicit Vehicle();
    int passesSinceOilChange() const;
    int passesSinceTireChange() const;
};


class NAROBCORESHARED_EXPORT VehiclesModel : public ModelBase
{
    Q_OBJECT

public:
    explicit VehiclesModel(QObject *parent = nullptr);

    std::shared_ptr<Vehicle> vehicleForRow(const int row) const;
};

#endif // VEHICLES_H
