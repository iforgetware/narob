#ifndef RACEDAO_H
#define RACEDAO_H

#include <QSqlDatabase>
#include <QVector>

#include "race.h"

class RaceDao
{
public:
    RaceDao(QSqlDatabase &database);
    void init() const;

//    Race* getRace(int id) const;

    void addRace(Race &race) const;
//    void updateRace(const Race *race) const;
    void removeRace(int id) const;
    QVector<Race*> races() const;

private:
    QSqlDatabase &mDatabase;
};

#endif // RACEDAO_H
