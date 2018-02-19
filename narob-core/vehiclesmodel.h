#ifndef VEHICLESMODEL_H
#define VEHICLESMODEL_H

#include <QVector>

#include "modelbase.h"

#include "narob-core_global.h"
#include "vehicle.h"
#include "databasemanager.h"

class NAROBCORESHARED_EXPORT VehiclesModel : public ModelBase
{
    Q_OBJECT

public:
    VehiclesModel(QObject *parent = 0);

    Vehicle* getVehicle(const int id);
    QModelIndex addVehicle(const Vehicle &vehicle);
//    void updateVehicle(const Vehicle *vehicle);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

private:
    DatabaseManager &mDb;
    QVector<Vehicle*> mVehicles;
};

#endif // VEHICLESMODEL_H
