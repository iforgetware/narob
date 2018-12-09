#ifndef SETTINGS_H
#define SETTINGS_H

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

static Fields SETTINGS_FIELDS{Field("id", "id", 0, 0),
            Field("windAdjustment", "Wind Adjustment", 50, 3),
            Field("weightAdjustment", "Weight Adjustment", 50, 3),
            Field("textNumber", "Text Number", 150, -4),
            Field("textProvider", "Text Provider", 150, -4),
            Field("emailUser", "Email User", 250, -4),
            Field("emailPW", "Email Password", 250, -4),
            Field("emailHost", "Email Host", 250, -4)};


class NAROBCORESHARED_EXPORT Settings : public DbTableBase
{
public:
    explicit Settings();
    DbRecordBase *getSettings();
    void updateSettings(DbRecordBase *settings);
};

#endif // SETTINGS_H
