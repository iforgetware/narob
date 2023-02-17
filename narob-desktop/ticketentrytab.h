#ifndef TICKETENTRYTAB_H
#define TICKETENTRYTAB_H

#include <memory>

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
    explicit TicketEntryTab(TicketsLogbookModel* tLModel,
                            std::shared_ptr<Vehicle> vehicle,
                            std::shared_ptr<Race> race,
                            QWidget *parent = nullptr);
    ~TicketEntryTab();

signals:
    void ticketsUpdated();

private:
    void updateAllModels();

    Ui::TicketEntryTab *ui;
    TicketsEditWidget *mTicketsEditWidget;
    TicketsLogbookModel *mTicketsLogbookModel;
};

#endif // TICKETENTRYTAB_H
