#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QObject>

#include "settings.h"
#include "databasemanager.h"

class SettingsModel : public QObject
{
    Q_OBJECT
public:
    explicit SettingsModel(QObject *parent = nullptr);

    Settings *getSettings() const { return mSettings; }
    void updateSettings(Settings *settings);

private:
    DatabaseManager &mDb;
    Settings *mSettings;
};

#endif // SETTINGSMODEL_H
