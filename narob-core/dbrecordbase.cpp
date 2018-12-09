#include <QSqlField>
#include <QDebug>

#include "dbrecordbase.h"

DbRecordBase::DbRecordBase(QString table,
                           Fields fields) :
    QSqlRecord(),
    mTable(table),
    mFields(fields)
{

}

void DbRecordBase::init()
{
    foreach(Field field, mFields){
        switch(field.mDelegate){
        case -4:
        case -3:
        case -2:
            this->append(QSqlField(field.mColumn, QVariant::String, mTable));
            break;

        case -1:
        case 0:
            this->append(QSqlField(field.mColumn, QVariant::Int, mTable));
            break;

        case 1:
        case 2:
        case 3:
        case 13:
            this->append(QSqlField(field.mColumn, QVariant::Double, mTable));
        }
    }
}

void DbRecordBase::populate(QSqlRecord rec)
{
    foreach(Field field, mFields){
        this->setValue(field.mColumn, rec.value(field.mColumn));
    }
}
