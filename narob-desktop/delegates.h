#ifndef DELEGATES_H
#define DELEGATES_H

#include <QStyledItemDelegate>
#include <QSqlRelationalDelegate>


class BoolDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit BoolDelegate(QObject *parent = 0);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class TimeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit TimeDelegate(QObject *parent = 0);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class DateTimeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit DateTimeDelegate(QObject* parent = 0);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class OneDecimalDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit OneDecimalDelegate(QObject *parent = 0);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class TwoDecimalDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit TwoDecimalDelegate(QObject *parent = 0);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class ThreeDecimalDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ThreeDecimalDelegate(QObject *parent = 0);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class RaceColumnDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit RaceColumnDelegate(QObject* parent = 0);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};



class TrackColumnDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit TrackColumnDelegate(QObject* parent = 0);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


#endif // DELEGATES_H
