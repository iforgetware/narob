#ifndef TRACKHISTORYTAB_H
#define TRACKHISTORYTAB_H

#include <QWidget>

#include "vehicles.h"
#include "tracks.h"
#include "tickets.h"
#include "trackhistorywidget.h"

namespace Ui {
class TrackHistoryTab;
}

class TrackHistoryTab : public QWidget
{
    Q_OBJECT

public:
    explicit TrackHistoryTab(//TicketsLogbookModel* model,
                             std::shared_ptr<Vehicle> vehicle,
                             int trackId,
                             QWidget* parent = nullptr);
    ~TrackHistoryTab();
    void updateAllModels();

private:
    Ui::TrackHistoryTab* ui;
    TrackHistoryWidget *mTrackHistoryWidget;
    TicketsTrackModel *mTicketsTrackModel;
};

#endif // TRACKHISTORYTAB_H
