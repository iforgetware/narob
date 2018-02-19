#ifndef TICKETENTRYTAB_H
#define TICKETENTRYTAB_H

#include <QWidget>

#include "vehicle.h"
#include "race.h"
#include "ticketsmodel.h"

namespace Ui {
class TicketEntryTab;
}

class TicketEntryTab : public QWidget
{
    Q_OBJECT

public:
    explicit TicketEntryTab(TicketsModel* model,
                            Vehicle* vehicle,
                            Race* race,
                            QWidget *parent = 0);
    ~TicketEntryTab();

private:
    Ui::TicketEntryTab *ui;
};

#endif // TICKETENTRYTAB_H
