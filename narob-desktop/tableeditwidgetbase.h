#ifndef TABLEEDITWIDGETBASE_H
#define TABLEEDITWIDGETBASE_H

#include <QPushButton>

#include "tablewidgetbase.h"

class TableEditWidgetBase : public TableWidgetBase
{
    Q_OBJECT

public:
    explicit TableEditWidgetBase(const QString title, QWidget *parent = nullptr);
    ~TableEditWidgetBase();

    void init();

    bool selected() const;
    int selectedRow() const;

    void deleteSelectedRow();

protected:
    QPushButton *mAddButton;
    QPushButton *mEditButton;
    QPushButton *mDeleteButton;
};

#endif // TABLEEDITWIDGETBASE_H
