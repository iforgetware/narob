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
    explicit TableWidgetBase(const QString title, QWidget *parent = nullptr);
    ~TableWidgetBase();

    void updateModel();

protected:
//    void setTitle(const QString &title);
    void setupColumns(const Fields &fields);
    void hide(const QString &columnName);

    Ui::TableWidgetBase *ui;
    ModelBase *mModel;
    QString mTitle;
};

#endif // TABLEWIDGETBASE_H
