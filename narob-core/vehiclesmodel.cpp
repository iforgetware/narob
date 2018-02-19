#include "vehiclesmodel.h"

using namespace std;

VehiclesModel::VehiclesModel(QObject *parent) :
    ModelBase(parent),
    mDb(DatabaseManager::instance()),
    mVehicles(mDb.vehicleDao.vehicles())
{
    setTable("vehicles");

    mFields.append(Field("number", "Number", 70, 0));
    mFields.append(Field("compClass", "Class", 70, 0));
    mFields.append(Field("weight", "Weight", 70, 0));

    setHeaders();

    select();
}

Vehicle* VehiclesModel::getVehicle(const int id)
{
    return mVehicles.at(id);
}

QModelIndex VehiclesModel::addVehicle(const Vehicle &vehicle)
{
    int rowIndex = rowCount();

    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    Vehicle* newVehicle = new Vehicle(vehicle);
    mDb.vehicleDao.addVehicle(*newVehicle);
    mVehicles.append(newVehicle);
    endInsertRows();

    return index(rowIndex, 0);
}

//void VehiclesModel::updateVehicle(const Vehicle *vehicle)
//{
//    mDb.vehicleDao.updateVehicle(vehicle);
//}

int VehiclesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mVehicles.size();
}

bool VehiclesModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0
            || row >= rowCount()
            || count < 0
            || (row + count) > rowCount()) {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while (countLeft--) {
        const Vehicle& vehicle = *mVehicles.at(row + countLeft);
        mDb.vehicleDao.removeVehicle(vehicle.id());
    }
    mVehicles.erase(mVehicles.begin() + row,
                  mVehicles.begin() + row + count);
    endRemoveRows();
    return true;
}
