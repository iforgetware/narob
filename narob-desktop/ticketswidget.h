#ifndef TICKETSWIDGET_H
#define TICKETSWIDGET_H

#include "tickets.h"
#include "tabledisplaywidgetbase.h"
#include "ui_tablewidgetbase.h"

class TicketsWidget : public TableDisplayWidgetBase
{
    Q_OBJECT

public:
    explicit TicketsWidget(TicketsModel *model,
                           int trackId,
                           QWidget* parent = 0);

private:
    TicketsModel* mTicketsModel;
};

#endif // TICKETSWIDGET_H
