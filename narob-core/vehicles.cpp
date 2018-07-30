#include "vehicles.h"

Fields vehicleFields()
{
    Fields f;

    f.append(Field("id", "id", 0, 0));
    f.append(Field("number", "Number", 70, -4));
    f.append(Field("compClass", "Class", 70, -4));
    f.append(Field("weight", "Weight", 70, 0));

    return f;
}

Vehicles::Vehicles() :
    DbTableBase()
{
    mFields = vehicleFields();
    mTable = "vehicles";
}


Vehicle::Vehicle() :
    DbRecordBase()
{
    mFields = vehicleFields();
    init("vehicles");
}

VehiclesModel::VehiclesModel(QObject *parent) :
    ModelBase("vehicles",
              vehicleFields(),
              parent)
{
}

Vehicle* VehiclesModel::getVehicle(const int row)
{
    Vehicle *vehicle = new Vehicle();
    vehicle->populate(record(row));

    return vehicle;
}
