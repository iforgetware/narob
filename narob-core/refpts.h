#ifndef REFPTS_H
#define REFPTS_H

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

class RefPTs : public DbTableBase
{
public:
    explicit RefPTs();
};


class NAROBCORESHARED_EXPORT RefPT : public DbRecordBase
{
public:
    explicit RefPT();
};


class NAROBCORESHARED_EXPORT RefPTsModel : public ModelBase
{
    Q_OBJECT

public:
    explicit RefPTsModel(QObject *parent = 0);

    void addRefPT(RefPT refPT);
};

#endif // REFPTS_H
