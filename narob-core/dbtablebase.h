#ifndef DBTABLEBASE_H
#define DBTABLEBASE_H

#include "narob-core_global.h"

class DbTableBase
{
public:
    DbTableBase(QString table,
                Fields fields);

    void init() const;

private:
    QString mTable;
    Fields mFields;
};

#endif // DBTABLEBASE_H
