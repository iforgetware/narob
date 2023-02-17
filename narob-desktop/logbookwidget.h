#ifndef LOGBOOKWIDGET_H
#define LOGBOOKWIDGET_H

#include "tickets.h"
#include "tabledisplaywidgetbase.h"
#include "ui_tablewidgetbase.h"

class LogbookWidget : public TableDisplayWidgetBase
{
    Q_OBJECT

public:
    explicit LogbookWidget(TicketsLogbookModel* tLModel,
                           QWidget* parent = nullptr);

private:
    TicketsLogbookModel* mTicketsLogbookModel;
};

#endif // LOGBOOKWIDGET_H
