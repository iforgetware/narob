#include "modelbase.h"

#include <QDebug>

ModelBase::ModelBase(QString table,
                     Fields fields,
                     QObject *parent) :
    QSqlRelationalTableModel(parent),
    mFields(fields)
{
    setTable(table);
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

void ModelBase::addRow(QSqlRecord &rec)
{
    insertRecord(-1, rec);
    submitAll();
    select();
}
