#include <QSqlQuery>

#include <QDebug>

#include "settings.h"
#include "databasemanager.h"

Fields setSettingsFields()
{
    Fields retFields;

    retFields.append(Field("id", "id", 0, 0));
    retFields.append(Field("emailUser", "Email User", 250, -4));
    retFields.append(Field("emailPW", "Email Password", 250, -4));
    retFields.append(Field("emailHost", "Email Host", 250, -4));
    retFields.append(Field("textNumber", "Text Number", 150, -4));
    retFields.append(Field("textProvider", "Text Provider", 150, -4));

    return retFields;
}

Fields settingsFields = setSettingsFields();

Settings::Settings() :
    DbTableBase()
{
    mFields = settingsFields;
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
        foreach (Field field, mFields) {
            settings->setValue(field.mColumn, query.value(field.mColumn));
        }
    }

    query.clear();

    return settings;
}

void Settings::updateSettings(DbRecordBase *settings)
{
    QSqlQuery query;
    query.prepare("UPDATE settings set ("
                  "emailUser,"
                  "emailPW,"
                  "emailHost,"
                  "textNumber,"
                  "textProvider"
                  ") = ("
                  ":emailUser,"
                  ":emailPW,"
                  ":emailHost,"
                  ":textNumber,"
                  ":textProvider"
                  ") WHERE id=1");
    query.bindValue(":emailUser", settings->value("emailUser"));
    query.bindValue(":emailPW", settings->value("emailPW"));
    query.bindValue(":emailHost", settings->value("emailHost"));
    query.bindValue(":textNumber", settings->value("textNumber"));
    query.bindValue(":textProvider", settings->value("textProvider"));

    query.exec();
    DatabaseManager::debugQuery(query);

}
