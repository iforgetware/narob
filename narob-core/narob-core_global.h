#ifndef NAROBCORE_GLOBAL_H
#define NAROBCORE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QVector>

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
        mDelegate = 0;
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

const int CHANGE_DELAY = 1000;


#if defined(NAROBCORE_LIBRARY)
#  define NAROBCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define NAROBCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NAROBCORE_GLOBAL_H
