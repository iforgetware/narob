#include <QSqlDatabase>
#include <QSqlQuery>

#include "dbtablebase.h"
#include "databasemanager.h"

QString columnType(QString col, int del)
{
    // look into using varchar(length) for text fields

    QString type = "";

    switch(del){
    case -4:
    case -3:
    case -2:
        type.append(" TEXT");
        break;

    case -1:
    case 0:
        type.append(" INTEGER");
        if(col == "id"){
            type.append(" PRIMARY KEY");
        }
        break;

    case 1:
    case 2:
    case 3:
    case 13:
        type.append(" REAL");
    }

    return type;
}


DbTableBase::DbTableBase(QString table,
                         Fields fields) :
    mTable(table),
    mFields(fields)
{
}

void DbTableBase::init() const
{
    if(!QSqlDatabase::database().tables().contains(mTable)){

        QString queryText = QString("CREATE TABLE %1 (").arg(mTable);

        foreach(Field field, mFields){

            if(field.mColumn != "id"){
                queryText.append(",");
            }

            queryText.append(field.mColumn);
            queryText.append(columnType(field.mColumn, field.mDelegate));
        }

        queryText.append(")");

        QSqlQuery query;
        query.exec(queryText);
        DatabaseManager::debugQuery(query);

        query.clear();
    }else{
        QSqlRecord existingColumns = QSqlDatabase::database().record(mTable);

        foreach(Field field, mFields){

            if(!existingColumns.contains(field.mColumn)){
                QString queryText = QString("ALTER TABLE %1 ADD COLUMN %2 ")
                                    .arg(mTable)
                                    .arg(field.mColumn);
                queryText.append(columnType(field.mColumn, field.mDelegate));

                QSqlQuery query;
                query.exec(queryText);
                DatabaseManager::debugQuery(query);

                query.clear();
            }
        }
    }
}
