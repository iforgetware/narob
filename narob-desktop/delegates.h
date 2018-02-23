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

class mySqlRelationalDelegate : public QSqlRelationalDelegate
{
    Q_OBJECT
public:
    explicit mySqlRelationalDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

signals:

public slots:

};

#endif // DELEGATES_H
