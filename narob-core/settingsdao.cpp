#include "settingsdao.h"

#include <QSqlQuery>
#include <QVariant>

#include "databasemanager.h"

SettingsDao::SettingsDao(QSqlDatabase &database) :
    mDatabase(database)
{
}

void SettingsDao::init() const
{
    if(!mDatabase.database().tables().contains("settings")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE settings ("
                   "id INT PRIMARY KEY,"

                   "emailUser TEXT,"
                   "emailPW TEXT,"
                   "emailHost TEXT,"
                   "textNumber TEXT,"
                   "textProvider TEXT)");
        DatabaseManager::debugQuery(query);

        query.exec("INSERT INTO settings ("
                   "id,"

                   "emailUser,"
                   "emailPW,"
                   "emailHost,"
                   "textNumber,"
                   "textProvider"

                   ") VALUES ("

                   "1,"

                   "'',"
                   "'',"
                   "'',"
                   "'',"
                   "''"
                   ")");
    }
}

void SettingsDao::updateSettings(const Settings *settings) const
{
    QSqlQuery query(mDatabase);

    query.prepare("UPDATE settings SET "
                  "emailUser=:emailUser,"
                  "emailPW=:emailPW,"
                  "emailHost=:emailHost,"
                  "textNumber=:textNumber,"
                  "textProvider=:textProvider "
                  "WHERE id=1");

    query.bindValue(":emailUser", settings->emailUser());
    query.bindValue(":emailPW", settings->emailPW());
    query.bindValue(":emailHost", settings->emailHost());
    query.bindValue(":textNumber", settings->textNumber());
    query.bindValue(":textProvider", settings->textProvider());

    query.exec();

    DatabaseManager::debugQuery(query);
}

Settings* SettingsDao::getSettings() const
{
    QSqlQuery query("SELECT * FROM settings", mDatabase);

    query.exec();

    Settings* settings = new Settings();

    settings->setId(1);

    if(query.next()){
        settings->setEmailUser(query.value("emailUser").toString());
        settings->setEmailPW(query.value("emailPW").toString());
        settings->setEmailHost(query.value("emailHost").toString());
        settings->setTextNumber(query.value("textNumber").toString());
        settings->setTextProvider(query.value("textProvider").toString());
    }

    return settings;
}
