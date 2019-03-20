#include <QSqlField>
#include <QDebug>

#include "dbrecordbase.h"

DbRecordBase::DbRecordBase(QString table,
                           Fields fields) :
    QSqlRecord(),
    mTable(table),
    mFields(fields)
{
    foreach(Field field, mFields){
        switch(field.mDelegate){
        case -4:
        case -3:
        case -2:
            append(QSqlField(field.mColumn, QVariant::String, mTable));
            break;

        case -1:
        case 0:
            append(QSqlField(field.mColumn, QVariant::Int, mTable));
            break;

        case 1:
        case 2:
        case 3:
        case 13:
            append(QSqlField(field.mColumn, QVariant::Double, mTable));
        }
    }
}

void DbRecordBase::populate(QSqlRecord rec)
{
    foreach(Field field, mFields){
        setValue(field.mColumn, rec.value(field.mColumn));
    }
}
