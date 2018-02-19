#ifndef SETTINGSDAO_H
#define SETTINGSDAO_H

#include <QSqlDatabase>

#include "settings.h"

class SettingsDao
{
public:
    SettingsDao(QSqlDatabase &database);
    void init() const;

    void updateSettings(const Settings *settings) const;
    Settings *getSettings() const;

private:
    QSqlDatabase &mDatabase;
};

#endif // SETTINGSDAO_H
