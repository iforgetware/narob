#ifndef DELEGATES_H
#define DELEGATES_H

#include <QStyledItemDelegate>


class BoolDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit BoolDelegate(QObject *parent = nullptr);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class DateDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit DateDelegate(QObject *parent = nullptr);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class DateTimeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit DateTimeDelegate(QObject* parent = nullptr);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class OneDecimalDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit OneDecimalDelegate(QObject *parent = nullptr);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class TwoDecimalDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit TwoDecimalDelegate(QObject *parent = nullptr);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class ThreeDecimalDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ThreeDecimalDelegate(QObject *parent = nullptr);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class ClockDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ClockDelegate(QObject *parent = nullptr);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class RaceColumnDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit RaceColumnDelegate(QObject* parent = nullptr);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


class TrackColumnDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit TrackColumnDelegate(QObject* parent = nullptr);
    QString displayText(const QVariant &value, const QLocale &locale) const;
};


#endif // DELEGATES_H
