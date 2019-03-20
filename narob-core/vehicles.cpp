#include "vehicles.h"
#include "tickets.h"

Vehicles::Vehicles() :
    DbTableBase("vehicles",
                VEHICLE_FIELDS)
{
}


Vehicle::Vehicle() :
    DbRecordBase("vehicles",
                 VEHICLE_FIELDS)
{
}

int Vehicle::passesSinceOilChange() const
{
    TicketsModel ticketsModel(value("id").toInt());

    return ticketsModel.ticketsSinceDateTime(value("lastOilChange")
                                             .toDateTime());
}

int Vehicle::passesSinceTireChange() const
{
    TicketsModel ticketsModel(value("id").toInt());

    return ticketsModel.ticketsSinceDateTime(value("lastTireChange")
                                             .toDateTime());
}


VehiclesModel::VehiclesModel(QObject *parent) :
    ModelBase("vehicles",
              VEHICLE_FIELDS,
              parent)
{
}

std::shared_ptr<Vehicle> VehiclesModel::vehicleForRow(const int row) const
{
    auto vehicle = std::make_shared<Vehicle>();
    vehicle->populate(record(row));

    return vehicle;
}
