#ifndef TABLEEDITWIDGETBASE_H
#define TABLEEDITWIDGETBASE_H

#include <QWidget>

#include "modelbase.h"

namespace Ui {
class TableEditWidgetBase;
}

class TableEditWidgetBase : public QWidget
{
    Q_OBJECT

public:
    explicit TableEditWidgetBase(QWidget *parent = 0);
    ~TableEditWidgetBase();

    void initTable();

    bool selected();
    int getSelection();

    void setTitle(const QString &title);
    void hideColumn(const int &column);
    void setupColumns(const Fields &fields);

protected:
    Ui::TableEditWidgetBase *ui;
    ModelBase *mModel;

private:
    QString mTitle;
};

#endif // TABLEEDITWIDGETBASE_H
