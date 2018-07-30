#ifndef LOGBOOKTAB_H
#define LOGBOOKTAB_H

#include <QWidget>

#include "vehicles.h"
#include "tickets.h"
#include "ticketswidget.h"

namespace Ui {
class LogbookTab;
}

class LogbookTab : public QWidget
{
    Q_OBJECT

public:
    explicit LogbookTab(TicketsModel* model,
                        QWidget *parent = 0);
    ~LogbookTab();
    void updateAllModels();

private:
    Ui::LogbookTab *ui;
    TicketsWidget *mTicketsWidget;
};

#endif // LOGBOOKTAB_H
