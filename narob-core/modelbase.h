#ifndef MODELBASE_H
#define MODELBASE_H

#include <QSqlRelationalTableModel>
#include <QSqlRecord>

#include "narob-core_global.h"

class ModelBase : public QSqlRelationalTableModel
{
    Q_OBJECT

public:
    ModelBase(QString table,
              Fields fields,
              QObject *parent = 0);

    void setHeaders();
    Fields fields() { return mFields; }
    void addRow(QSqlRecord rec);

protected:
    Fields mFields;
};

#endif // MODELBASE_H
