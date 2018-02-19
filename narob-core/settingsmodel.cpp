#include "settingsmodel.h"

SettingsModel::SettingsModel(QObject *parent) :
    QObject(parent),
    mDb(DatabaseManager::instance())
{
    mSettings = mDb.settingsDao.getSettings();
}

void SettingsModel::updateSettings(Settings *settings)
{
    mSettings = settings;
    mDb.settingsDao.updateSettings(mSettings);
}
