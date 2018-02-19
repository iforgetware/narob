#ifndef RACESMODEL_H
#define RACESMODEL_H

#include <QVector>

#include "narob-core_global.h"
#include "modelbase.h"
#include "race.h"
#include "databasemanager.h"

using namespace std;

class NAROBCORESHARED_EXPORT RacesModel : public ModelBase
{
    Q_OBJECT

public:
    RacesModel(QObject *parent = 0);

    Race *getRace(const int id);
    QModelIndex addRace(const Race &race);
//    void updateRace(const Race *race);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

private:
    DatabaseManager &mDb;
    QVector<Race*> mRaces;
};

#endif // RACESMODEL_H
