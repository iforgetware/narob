#include "vehicledao.h"

#include <QSqlQuery>
#include <QVariant>

#include "vehicle.h"
#include "databasemanager.h"

using namespace std;

VehicleDao::VehicleDao(QSqlDatabase &database) :
    mDatabase(database)
{
}

void VehicleDao::init() const
{
    if(!mDatabase.tables().contains("vehicles")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE vehicles ("
                   "id INTEGER PRIMARY KEY,"
                   "number TEXT,"
                   "compClass TEXT,"
                   "weight INTEGER)");
        DatabaseManager::debugQuery(query);
    }
}

void VehicleDao::addVehicle(Vehicle &vehicle) const
{
    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO vehicles ("
                  "number,"
                  "compClass,"
                  "weight"
                  ") VALUES ("
                  ":number, "
                  ":compClass, "
                  ":weight"
                  ")");

    query.bindValue(":number", vehicle.number());
    query.bindValue(":compClass", vehicle.compClass());
    query.bindValue(":weight", vehicle.weight());

    query.exec();

    DatabaseManager::debugQuery(query);

    vehicle.setId(query.lastInsertId().toInt());
}

void VehicleDao::updateVehicle(const Vehicle *vehicle) const
{
    QSqlQuery query(mDatabase);

    query.prepare("UPDATE vehicles SET "
                  "number=:number,"
                  "compClass=:compClass,"
                  "weight "
                  "WHERE id=:id");

    query.bindValue(":number", vehicle->number());
    query.bindValue(":compClass", vehicle->compClass());
    query.bindValue(":weight", vehicle->weight());
    query.bindValue(":id", vehicle->id());

    query.exec();

    DatabaseManager::debugQuery(query);
}

void VehicleDao::removeVehicle(int id) const
{
    QSqlQuery query(mDatabase);

    query.prepare("DELETE from vehicles WHERE id=:id");

    query.bindValue(":id", id);

    query.exec();

    DatabaseManager::debugQuery(query);
}

QVector<Vehicle *> VehicleDao::vehicles() const
{
    QSqlQuery query("SELECT * FROM vehicles", mDatabase);

    query.exec();

    QVector<Vehicle*> list;

    while(query.next()) {
        Vehicle* vehicle = new Vehicle();
        vehicle->setId(query.value("id").toInt());
        vehicle->setNumber(query.value("number").toString());
        vehicle->setCompClass(query.value("compClass").toString());
        vehicle->setWeight(query.value("weight").toInt());

        list.append(vehicle);
    }

    return list;
}
