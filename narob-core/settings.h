#ifndef SETTINGS_H
#define SETTINGS_H

#include "dbtablebase.h"
#include "dbrecordbase.h"
#include "modelbase.h"

#include "narob-core_global.h"

#include <QHash>
#include <QVariant>

const QHash<QString, QVariant> DEFAULT_SETTINGS{{"windAdjustment", 0.0},
                                                {"weightAdjustment", 0.0},
                                                {"textNumber", ""},
                                                {"textProvider", ""},
                                                {"emailUser", ""},
                                                {"emailPW", ""},
                                                {"emailHost", ""},
                                                {"useOffsets", false},
                                                {"tempOffset", 0.0},
                                                {"humOffset", 0.0},
                                                {"useConsole", false}};


class NAROBCORESHARED_EXPORT Settings
{
public:
    static QVariant get(const QString &name);
    static void set(const QString &name, const QVariant &value);

private:
    Settings() {}

    static QHash<QString, QVariant> mSettingsCache;
};

#endif // SETTINGS_H
