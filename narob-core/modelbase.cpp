#include "modelbase.h"

ModelBase::ModelBase(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void ModelBase::setHeaders()
{
    foreach(Field field, mFields){
        setHeaderData(fieldIndex(field.mColumn),
                      Qt::Horizontal,
                      field.mHeading);
    }
    select();
}
