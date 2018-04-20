#include <QSqlField>

#include "dbrecordbase.h"

DbRecordBase::DbRecordBase()
{

}

void DbRecordBase::setFields(const Fields &fields)
{
    mFields = fields;
}

void DbRecordBase::init(const QString &table)
{
    foreach(Field field, mFields){
        switch(field.mDelegate){
        case -4:
        case -3:
        case -2:
            this->append(QSqlField(field.mColumn, QVariant::String, table));
            break;

        case -1:
        case 0:
            this->append(QSqlField(field.mColumn, QVariant::Int, table));
            break;

        case 1:
        case 2:
        case 3:
            this->append(QSqlField(field.mColumn, QVariant::Double, table));
        }
    }
}
