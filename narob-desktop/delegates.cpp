#include "delegates.h"
#include <QTime>
#include <QDebug>

#include <math.h>

#include "races.h"
#include "tracks.h"

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


DateDelegate::DateDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
}

QString DateDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    QString formattedDate = locale.toString(value.toDate(), "M/d/yyyy");

    return formattedDate;
}


DateTimeDelegate::DateTimeDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QString DateTimeDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    QString formattedDateTime = locale.toString(value.toDateTime(), "M/d/yyyy h:mmA");

    return formattedDateTime;
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


ClockDelegate::ClockDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
}

QString ClockDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    QString formattedNumber = locale.toString(fabs(value.toDouble()), 'f', 3);

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
    return racesModel->raceForId(value.toInt())->value("name").toString();
}


TrackColumnDelegate::TrackColumnDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
}

QString TrackColumnDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale);

    TracksModel* tracksModel = new TracksModel();
    return tracksModel->trackForId(value.toInt())->value("name").toString();
}
