#ifndef RACES_H
#define RACES_H

#include <memory>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

const Fields RACE_FIELDS{
            Field("id", "id", 0, 0),
            Field("date", "Date", 100, -2),
            Field("name", "Name", 150, -4),
            Field("trackId", "Track", 150, 0)};


class Races : public DbTableBase
{
public:
    explicit Races();
};


class NAROBCORESHARED_EXPORT Race : public DbRecordBase
{
public:
    explicit Race();
};


class NAROBCORESHARED_EXPORT RacesModel : public ModelBase
{
    Q_OBJECT

public:
    explicit RacesModel(QObject *parent = nullptr);

    std::shared_ptr<Race> raceForRow(const int row) const;
    std::unique_ptr<Race> raceForId(const int id) const;
};

#endif // RACES_H
