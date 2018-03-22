#ifndef REFPTS_H
#define REFPTS_H

#include <QSqlRecord>

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

class RefPTs : public DbTableBase
{
public:
    explicit RefPTs();
};


class RefPT : public DbRecordBase
{
public:
    explicit RefPT();
};


class RefPTsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit RefPTsModel(QObject *parent = 0);
};

#endif // REFPTS_H
