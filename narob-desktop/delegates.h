#ifndef DECIMALDELEGATES_H
#define DECIMALDELEGATES_H

#include <QStyledItemDelegate>

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

#endif // DECIMALDELEGATES_H
