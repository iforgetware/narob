#ifndef TABLEWIDGETBASE_H
#define TABLEWIDGETBASE_H

#include <QWidget>

#include "modelbase.h"

namespace Ui {
class TableWidgetBase;
}

class TableWidgetBase : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidgetBase(QWidget *parent = 0);
    ~TableWidgetBase();

    void setTitle(const QString &title);
    void hideColumn(const int &column);
    void setupColumns(const Fields &fields);

protected:
    Ui::TableWidgetBase *ui;
    ModelBase *mModel;
    QString mTitle;
};

#endif // TABLEWIDGETBASE_H
