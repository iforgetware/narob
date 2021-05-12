#ifndef MODELBASE_H
#define MODELBASE_H

#include <QSqlRelationalTableModel>
#include <QSqlRecord>

#include "narob-core_global.h"

class NAROBCORESHARED_EXPORT ModelBase : public QSqlRelationalTableModel
{
    Q_OBJECT

public:
    ModelBase(QString table,
              Fields fields,
              QObject *parent = nullptr);

    void setHeaders();
    void addRow(QSqlRecord &rec);

private:
    Fields mFields;
};

#endif // MODELBASE_H
