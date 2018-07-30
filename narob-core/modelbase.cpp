#include "modelbase.h"

ModelBase::ModelBase(QString table,
                     Fields fields,
                     QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setTable(table);
    mFields = fields;
    setHeaders();
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

void ModelBase::setHeaders()
{
    foreach(Field field, mFields){
        setHeaderData(fieldIndex(field.mColumn),
                      Qt::Horizontal,
                      field.mHeading);
    }
}

void ModelBase::addRow(QSqlRecord rec)
{
    insertRecord(-1, rec);
    submitAll();
    select();
}
