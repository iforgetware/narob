#ifndef TABLEEDITWIDGETBASE_H
#define TABLEEDITWIDGETBASE_H

#include <QPushButton>

#include "tablewidgetbase.h"

class TableEditWidgetBase : public TableWidgetBase
{
    Q_OBJECT

public:
    explicit TableEditWidgetBase(QWidget *parent = 0);
    ~TableEditWidgetBase();

    void initTable();

    bool selected();
    int getSelection();
    QModelIndex getSelectionIndex();

    void deleteSelectedRow();

    void updateModels();

protected:
    QPushButton *mAddButton;
    QPushButton *mEditButton;
    QPushButton *mDeleteButton;
};

#endif // TABLEEDITWIDGETBASE_H
