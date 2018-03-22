#include <QSqlQuery>
#include <QSqlField>

#include "vehicles.h"

Fields setVehicleFields()
{
    Fields retFields;

    retFields.append(Field("number", "Number", 70, 0));
    retFields.append(Field("compClass", "Class", 70, 0));
    retFields.append(Field("weight", "Weight", 70, 0));

    return retFields;
}

Fields vehicleFields = setVehicleFields();

Vehicles::Vehicles() :
    DbTableBase()
{
    mFields = vehicleFields;
    mTable = "vehicles";
}


Vehicle::Vehicle() :
    DbRecordBase()
{
    mFields = vehicleFields;
    init("vehicles");
}

VehiclesModel::VehiclesModel(QObject *parent) :
    ModelBase(parent)
{
    setTable("vehicles");

    mFields = vehicleFields;

    setHeaders();

    select();
}

Vehicle* VehiclesModel::getVehicle(const int row)
{
    QSqlRecord rec = record(row);
    Vehicle *vehicle = new Vehicle();
    foreach (Field field, mFields) {
        vehicle->setValue(field.mColumn, rec.value(field.mColumn));
    }
    return vehicle;
}

Vehicle* VehiclesModel::firstVehicle()
{
    return getVehicle(1);
}
