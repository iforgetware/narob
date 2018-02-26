#include "delegates.h"
#include <QTime>
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QDebug>
#include <QSqlRecord>

#include "racesmodel.h"
#include "tracksmodel.h"

BoolDelegate::BoolDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
}

QString BoolDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale);

    if(value == 0){
        return "No";
    }else{
        return "Yes";
    }
}

TimeDelegate::TimeDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
}

QString TimeDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    QString formattedTime = locale.toString(value.toTime(), "h:mmA");

    return formattedTime;
}

OneDecimalDelegate::OneDecimalDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
}

QString OneDecimalDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    QString formattedNumber = locale.toString(value.toDouble(), 'f', 1);

    return formattedNumber;
}

TwoDecimalDelegate::TwoDecimalDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
}

QString TwoDecimalDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    QString formattedNumber = locale.toString(value.toDouble(), 'f', 2);

    return formattedNumber;
}

ThreeDecimalDelegate::ThreeDecimalDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
}

QString ThreeDecimalDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    QString formattedNumber = locale.toString(value.toDouble(), 'f', 3);

    return formattedNumber;
}


RaceColumnDelegate::RaceColumnDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
}

QString RaceColumnDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale);

    RacesModel* racesModel = new RacesModel();
    return racesModel->raceName(value.toInt());
}


TrackColumnDelegate::TrackColumnDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
}

QString TrackColumnDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale);

    TracksModel* tracksModel = new TracksModel();
    return tracksModel->trackName(value.toInt());
}
