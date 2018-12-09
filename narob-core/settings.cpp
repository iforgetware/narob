#include <QSqlQuery>

#include <QDebug>

#include "settings.h"
#include "databasemanager.h"

Settings::Settings() :
    DbTableBase("settings",
                SETTINGS_FIELDS)
{
}

DbRecordBase *Settings::getSettings()
{
    QSqlQuery query;
    query.exec("SELECT * FROM settings "
               "WHERE id = 1");

    DbRecordBase *settings = new DbRecordBase("settings",
                                              SETTINGS_FIELDS);
    settings->init();

    if(query.next()){
        settings->populate(query.record());
    }

    query.clear();

    return settings;
}

void Settings::updateSettings(DbRecordBase *settings)
{
    QSqlQuery query;
    query.prepare("UPDATE settings set ("
                  "windAdjustment,"
                  "weightAdjustment,"
                  "textNumber,"
                  "textProvider,"
                  "emailUser,"
                  "emailPW,"
                  "emailHost"
                  ") = ("
                  ":windAdjustment,"
                  ":weightAdjustment,"
                  ":textNumber,"
                  ":textProvider,"
                  ":emailUser,"
                  ":emailPW,"
                  ":emailHost"
                  ") WHERE id=1");
    query.bindValue(":weightAdjustment", settings->value("weightAdjustment"));
    query.bindValue(":windAdjustment", settings->value("windAdjustment"));
    query.bindValue(":textNumber", settings->value("textNumber"));
    query.bindValue(":textProvider", settings->value("textProvider"));
    query.bindValue(":emailUser", settings->value("emailUser"));
    query.bindValue(":emailPW", settings->value("emailPW"));
    query.bindValue(":emailHost", settings->value("emailHost"));

    query.exec();
    DatabaseManager::debugQuery(query);

    query.clear();

}
