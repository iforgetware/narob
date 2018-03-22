#ifndef TABLEDISPLAYWIDGETBASE_H
#define TABLEDISPLAYWIDGETBASE_H

#include "tablewidgetbase.h"

class TableDisplayWidgetBase : public TableWidgetBase
{
    Q_OBJECT

public:
    explicit TableDisplayWidgetBase(QWidget *parent = 0);
    ~TableDisplayWidgetBase();

    void initTable();
};

#endif // TABLEDISPLAYWIDGETBASE_H
