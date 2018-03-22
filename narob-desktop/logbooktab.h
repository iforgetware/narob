#ifndef LOGBOOKTAB_H
#define LOGBOOKTAB_H

#include <QWidget>

#include "vehicles.h"
#include "tickets.h"

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

private:
    Ui::LogbookTab *ui;
};

#endif // LOGBOOKTAB_H
