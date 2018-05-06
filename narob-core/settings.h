#ifndef SETTINGS_H
#define SETTINGS_H

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

class NAROBCORESHARED_EXPORT Settings : public DbTableBase
{
public:
    explicit Settings();
    DbRecordBase *getSettings();
    void updateSettings(DbRecordBase *settings);
};

#endif // SETTINGS_H
