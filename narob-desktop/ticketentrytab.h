#ifndef TICKETENTRYTAB_H
#define TICKETENTRYTAB_H

#include <QWidget>

#include "vehicles.h"
#include "races.h"
#include "tickets.h"
#include "ticketseditwidget.h"

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
    void updateAllModels();
private:
    Ui::TicketEntryTab *ui;
    TicketsEditWidget *mTicketsEditWidget;
};

#endif // TICKETENTRYTAB_H
