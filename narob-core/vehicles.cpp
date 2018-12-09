#include "vehicles.h"

Vehicles::Vehicles() :
    DbTableBase("vehicles",
                VEHICLE_FIELDS)
{
}


Vehicle::Vehicle() :
    DbRecordBase("vehicles",
                 VEHICLE_FIELDS)
{
    init();
}

VehiclesModel::VehiclesModel(QObject *parent) :
    ModelBase("vehicles",
              VEHICLE_FIELDS,
              parent)
{
}

Vehicle* VehiclesModel::getVehicle(const int row)
{
    Vehicle *vehicle = new Vehicle();
    vehicle->populate(record(row));

    return vehicle;
}
