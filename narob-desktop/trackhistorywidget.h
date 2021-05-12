#ifndef TRACKHISTORYWIDGET_H
#define TRACKHISTORYWIDGET_H

#include "tickets.h"
#include "tabledisplaywidgetbase.h"
#include "ui_tablewidgetbase.h"

class TrackHistoryWidget : public TableDisplayWidgetBase
{
    Q_OBJECT

public:
    explicit TrackHistoryWidget(//TicketsModel *model,
                                std::shared_ptr<Vehicle> vehicle,
                                int trackId,
                                QWidget* parent = nullptr);

private:
    TicketsModel* mTicketsModel;
};

#endif // TRACKHISTORYWIDGET_H
