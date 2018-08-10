#include <QSqlQuery>

#include <QDebug>

#include "settings.h"
#include "databasemanager.h"

Fields settingsFields()
{
    Fields f;

    f << Field("id", "id", 0, 0)
      << Field("windAdjustment", "Wind Adjustment", 50, 3)
      << Field("weightAdjustment", "Weight Adjustment", 50, 3)
      << Field("textNumber", "Text Number", 150, -4)
      << Field("textProvider", "Text Provider", 150, -4)
      << Field("emailUser", "Email User", 250, -4)
      << Field("emailPW", "Email Password", 250, -4)
      << Field("emailHost", "Email Host", 250, -4);

    return f;
}

Settings::Settings() :
    DbTableBase()
{
    mFields = settingsFields();
    mTable = "settings";
}

DbRecordBase *Settings::getSettings()
{
    QSqlQuery query;
    query.exec("SELECT * FROM settings "
               "WHERE id = 1");

    DbRecordBase *settings = new DbRecordBase();
    settings->setFields(mFields);
    settings->init("settings");

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
