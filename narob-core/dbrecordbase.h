#ifndef DBRECORDBASE_H
#define DBRECORDBASE_H

#include <QSqlRecord>
#include <QString>

#include "narob-core_global.h"

class DbRecordBase : public QSqlRecord
{
public:
    DbRecordBase();

    void setFields(const Fields &fields);
    void init(const QString &table);

protected:
    Fields mFields;
};

#endif // DBRECORDBASE_H
