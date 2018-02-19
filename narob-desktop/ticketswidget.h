#ifndef TICKETSWIDGET_H
#define TICKETSWIDGET_H

#include "ticketsmodel.h"
#include "tablewidgetbase.h"
#include "ui_tablewidgetbase.h"

class TicketsWidget : public TableWidgetBase
{
    Q_OBJECT

public:
    explicit TicketsWidget(TicketsModel* model,
                           int trackId = 0,
                           QWidget* parent = 0);

private:
    TicketsModel* mTicketsModel;
};

#endif // TICKETSWIDGET_H
