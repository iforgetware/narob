#include <QSqlDatabase>
#include <QSqlQuery>

#include "dbtablebase.h"
#include "databasemanager.h"

DbTableBase::DbTableBase()
{

}

void DbTableBase::init() const
{
    // look into using varchar(length) for text fields

    if(!QSqlDatabase::database().tables().contains(mTable)){

        QString queryText = QString("CREATE TABLE %1 (").arg(mTable);

        foreach(Field field, mFields){

            if(field.mColumn != "id"){
                queryText.append(",");
            }

            queryText.append(field.mColumn);
            switch(field.mDelegate){
            case -4:
            case -3:
            case -2:
                queryText.append(" TEXT");
                break;

            case -1:
            case 0:
                queryText.append(" INTEGER");
                if(field.mColumn == "id"){
                    queryText.append(" PRIMARY KEY");
                }
                break;

            case 1:
            case 2:
            case 3:
                queryText.append(" REAL");
            }
        }

        queryText.append(")");

        QSqlQuery query;
        query.exec(queryText);
        DatabaseManager::debugQuery(query);
    }
}
