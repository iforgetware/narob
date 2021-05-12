#ifndef NAROBCORE_GLOBAL_H
#define NAROBCORE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QVector>
#include <QPointF>
#include <QMap>
#include <QColor>

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

typedef QList<QPointF> Points;

struct Line
{
    double mSlope;
    double mIntercept;

    Line()
    {
        mSlope = 0;
        mIntercept = 0;
    }

    Line(Points &pts)
    {
        int nPoints = pts.size();

        qreal sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

        for(int i = 0; i < nPoints; i++) {
            sumX += pts[i].rx();
            sumY += pts[i].ry();
            sumXY += pts[i].rx() * pts[i].ry();
            sumX2 += pts[i].rx() * pts[i].rx();
        }

        double xMean = sumX / nPoints;
        double yMean = sumY / nPoints;
        double denominator = sumX2 - sumX * xMean;

        if(denominator == 0.0){
            denominator = 0.000001;
        }

        mSlope = (sumXY - (sumX * yMean)) / denominator;
        mIntercept = yMean - (mSlope * xMean);
    }

    double getYforX(double x)
    {
        return (mSlope * x) + mIntercept;
    }
};

const int CHANGE_DELAY = 1000;

const QColor T_COLOR = Qt::red;
const QColor H_COLOR = Qt::blue;
const QColor P_COLOR = Qt::darkYellow;
const QColor A_COLOR = Qt::gray;
const QColor D_COLOR = Qt::darkBlue;

const QMap<QString, QString> TEXT_SUFFIXES{{"Alltel", "message.alltel.com"},
                                            {"AT&T", "txt.att.net"},
                                            {"Boost Mobile", "myboostmobile.com"},
                                            {"Cricket Wireless", "mms.cricketwireless.net"},
                                            {"Sprint", "messaging.sprintpcs.com"},
                                            {"T-Mobile", "momail.net"},
                                            {"U.S. Cellular", "email.uscc.net"},
                                            {"Verizon", "vtext.com"},
                                            {"Virgin Mobile", "vmobl.com"},
                                            {"Republic Wireless", "text.republicwireless.com"}};

const double IN_TO_MB = 33.86389;
const double MB_TO_IN = 1 / IN_TO_MB;
const double FT_TO_M = 0.3048;
const double M_TO_FT = 1 / FT_TO_M;

inline double formatNum(double num, int decimals)
{
    return QString::number(num, 'f', decimals).toDouble();
}

#if defined(NAROBCORE_LIBRARY)
#  define NAROBCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define NAROBCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NAROBCORE_GLOBAL_H
