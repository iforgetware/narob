#ifndef DBTABLEBASE_H
#define DBTABLEBASE_H

#include <QVector>

#include "narob-core_global.h"

class DbTableBase
{
public:
    DbTableBase();

    void init() const;

protected:
    Fields mFields;
    QString mTable;
};

#endif // DBTABLEBASE_H
