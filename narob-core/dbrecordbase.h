#ifndef DBRECORDBASE_H
#define DBRECORDBASE_H

#include <QSqlRecord>
#include <QString>

#include "narob-core_global.h"

class DbRecordBase : public QSqlRecord
{
public:
    DbRecordBase(QString table,
                 Fields fields);

    void init();

    void populate(QSqlRecord rec);

private:
    QString mTable;
    Fields mFields;
};

#endif // DBRECORDBASE_H
