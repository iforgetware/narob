#ifndef MODELBASE_H
#define MODELBASE_H

#include <QSqlRelationalTableModel>

#include "narob-core_global.h"
#include "databasemanager.h"

struct Field
{
    QString mColumn;
    QString mHeading;
    int mWidth;
    int mDelegate;

    Field ()
    {
        mColumn = "";
        mHeading = "";
        mWidth = 0;
        mDelegate = -1;
    }

    Field (QString column, QString heading, int width, int decimals)
    {
        mColumn = column;
        mHeading = heading;
        mWidth = width;
        mDelegate = decimals;
    }
};

typedef QVector<Field> Fields;

class NAROBCORESHARED_EXPORT ModelBase : public QSqlRelationalTableModel
{
    Q_OBJECT

private:
    //bool isIndexValid(const QModelIndex &index) const;

public:
    ModelBase(QObject *parent = 0);

    void setHeaders();

    Fields mFields;
};

#endif // MODELBASE_H
