#include "settings.h"

#include <QSettings>
#include <QDebug>
#include <QCoreApplication>

QHash<QString, QVariant> Settings::mSettingsCache;

QVariant Settings::get(const QString &setting)
{
    auto sCIndex = mSettingsCache.find(setting);

    if(sCIndex != mSettingsCache.end())
    {
        return sCIndex.value();
    }else{
        QSettings settings;
        QVariant value = settings.value(setting,
                                        DEFAULT_SETTINGS[setting]);
        mSettingsCache.insert(setting, value.toString());
        return value;
    }
}

void Settings::set(const QString &setting, const QVariant &value)
{
    QSettings settings;
    settings.setValue(setting, value.toString());
    mSettingsCache.insert(setting, value.toString());
}
