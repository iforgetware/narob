#ifndef MODELBASE_H
#define MODELBASE_H

#include <QSqlRelationalTableModel>

#include "narob-core_global.h"

class ModelBase : public QSqlRelationalTableModel
{
    Q_OBJECT

public:
    ModelBase(QObject *parent = 0);

    void setHeaders();
    Fields fields() { return mFields; }

protected:
    Fields mFields;
};

#endif // MODELBASE_H
