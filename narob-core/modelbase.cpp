#include "modelbase.h"

ModelBase::ModelBase(QObject *parent) :
    QSqlRelationalTableModel(parent, DatabaseManager::instance().database())
{
    // this may not be needed, or may have to be someplace else

    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void ModelBase::setHeaders()
{
    foreach(Field field, mFields){
        setHeaderData(fieldIndex(field.mColumn),
                      Qt::Horizontal,
                      field.mHeading);
        //setHeaderData(field.mColumn, Qt::Horizontal, field.mHeading);
    }
    select();
}

//bool ModelBase::isIndexValid(const QModelIndex& index) const
//{
//    qDebug("in isIndexValid");
//    if (index.row() < 0
//            || index.row() >= rowCount()
//            || !index.isValid()) {
//        return false;
//    }
//    return true;
//}
