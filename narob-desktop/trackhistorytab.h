#ifndef TRACKHISTORYTAB_H
#define TRACKHISTORYTAB_H

#include <QWidget>

#include "vehicles.h"
#include "tracks.h"
#include "tickets.h"
#include "ticketswidget.h"

namespace Ui {
class TrackHistoryTab;
}

class TrackHistoryTab : public QWidget
{
    Q_OBJECT

public:
    explicit TrackHistoryTab(TicketsModel* model,
                             int trackId,
                             QWidget* parent = 0);
    ~TrackHistoryTab();
    void updateAllModels();

private:
    Ui::TrackHistoryTab* ui;
    TicketsWidget *mTicketsWidget;
};

#endif // TRACKHISTORYTAB_H
