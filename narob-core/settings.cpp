#include <QSqlQuery>
#include <QSqlField>

#include "settings.h"

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


Settings::Settings() :
    DbRecordBase()
{
    mFields = settingsFields;
    init("settings");
}

SettingsModel::SettingsModel(QObject *parent) :
    ModelBase(parent)
{
    mFields = settingsFields;
}
