#ifndef VEHICLEDAO_H
#define VEHICLEDAO_H

#include <QSqlDatabase>
#include <QVector>

#include "vehicle.h"

class VehicleDao
{
public:
    VehicleDao(QSqlDatabase &database);
    void init() const;

    void addVehicle(Vehicle &vehicle) const;
    void updateVehicle(const Vehicle *vehicle) const;
    void removeVehicle(int id) const;
    QVector<Vehicle*> vehicles() const;

private:
    QSqlDatabase &mDatabase;
};

#endif // VEHICLEDAO_H
