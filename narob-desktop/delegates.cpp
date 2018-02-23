#include "delegates.h"
#include <QTime>
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QDebug>
#include <QSqlRecord>

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


mySqlRelationalDelegate::mySqlRelationalDelegate(QObject *parent) :
    QSqlRelationalDelegate (parent)
{
    qDebug("in mySRD constructor");
}

QWidget *mySqlRelationalDelegate::createEditor(QWidget *aParent,
                                               const QStyleOptionViewItem &option,
                                               const QModelIndex &index) const
{
    qDebug("in mySRD createEditor");

//    QSqlRelationalTableModel sqlModel =index.model();
    const QSqlRelationalTableModel* sqlModel = qobject_cast<const QSqlRelationalTableModel*>(index.model());
//    const QSqlRelationalTableModel sqlModel = qobject_cast<const QSqlRelationalTableModel>(index.model());

    QSqlTableModel* childModel = new QSqlTableModel(sqlModel ? sqlModel->relationModel(index.column()) : 0);
    if (!childModel )
    {
        const QSortFilterProxyModel* proxyModel = qobject_cast<const QSortFilterProxyModel*>(index.model());
        if (proxyModel)
        {
            sqlModel = qobject_cast<QSqlRelationalTableModel*>(proxyModel->sourceModel());
            childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;
        }
    }

    if (!childModel)
    {
        return QItemDelegate::createEditor(aParent, option, index);
    }

    QComboBox* combo = new QComboBox(aParent);

    combo->setModel(childModel);
    combo->setModelColumn(childModel->fieldIndex(sqlModel->relation(index.column()).displayColumn()));
    combo->installEventFilter(const_cast<mySqlRelationalDelegate*>(this));
    return combo;
}

void mySqlRelationalDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug("in mySRD setEditorData");

    QString strVal = "";
    const QSqlRelationalTableModel* sqlModel = qobject_cast<const QSqlRelationalTableModel*>(index.model());
    if (!sqlModel )
    {
        const QSortFilterProxyModel* proxyModel = qobject_cast<const QSortFilterProxyModel *>(index.model());
        if (proxyModel) {
            strVal = proxyModel->data(index).toString();
        }
    } else {
        strVal = sqlModel->data(index).toString();
    }

    QComboBox* combo = new QComboBox(qobject_cast<QComboBox*>(editor));

    if (strVal.isEmpty() || !combo) {
        QItemDelegate::setEditorData(editor, index);
        return;
    }
    combo->setCurrentIndex(combo->findText(strVal));
}

void mySqlRelationalDelegate::setModelData(QWidget *editor,
                                           QAbstractItemModel *model,
                                           const QModelIndex &index) const
{
    qDebug("in mySRD setModelData");

    if (!index.isValid())
        return;
    QSqlRelationalTableModel* sqlModel = qobject_cast<QSqlRelationalTableModel*>(model);

    QSortFilterProxyModel* proxyModel = NULL;
    if (!sqlModel )
    {
        proxyModel = qobject_cast<QSortFilterProxyModel*>(model);
        if (proxyModel)
            sqlModel = qobject_cast<QSqlRelationalTableModel*>(proxyModel->sourceModel());
    }
    QSqlTableModel *childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;

    QComboBox* combo = new QComboBox(qobject_cast<QComboBox*>(editor));
    if (!combo) { // File:SqlModelchildModel ||
        QItemDelegate::setModelData(editor, model, index);
        return;
    }
    int currentItem = combo->currentIndex();

    if(!childModel){
        QItemDelegate::setModelData(editor, model, index);
        return;
    }

    qDebug() << index.column();
    qDebug() << sqlModel->relation(index.column()).displayColumn();
    qDebug("1");
    qDebug() << childModel->fieldIndex(sqlModel->relation(index.column()).displayColumn());

    int childColIndex = childModel->fieldIndex(sqlModel->relation(index.column()).displayColumn());

    int childEditIndex = childModel->fieldIndex(sqlModel->relation(index.column()).indexColumn());
    if (proxyModel) {

        proxyModel->setData(index, childModel->data(childModel->index(currentItem, childColIndex), Qt::DisplayRole), Qt::DisplayRole);
        proxyModel->setData(index, childModel->data(childModel->index(currentItem, childEditIndex), Qt::EditRole), Qt::EditRole);
    } else {
        sqlModel->setData(index, childModel->data(childModel->index(currentItem, childColIndex), Qt::DisplayRole), Qt::DisplayRole);
        sqlModel->setData(index, childModel->data(childModel->index(currentItem, childEditIndex), Qt::EditRole), Qt::EditRole);
    }

    return;
}
