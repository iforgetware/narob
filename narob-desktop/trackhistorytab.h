#ifndef TRACKHISTORYTAB_H
#define TRACKHISTORYTAB_H

#include <QWidget>

#include "vehicle.h"
#include "track.h"
#include "ticketsmodel.h"

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

private:
    Ui::TrackHistoryTab* ui;
};

#endif // TRACKHISTORYTAB_H
