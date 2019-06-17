#ifndef LOGBOOKTAB_H
#define LOGBOOKTAB_H

#include <QWidget>

#include "ticketswidget.h"

namespace Ui {
class LogbookTab;
}

class LogbookTab : public QWidget
{
    Q_OBJECT

public:
    explicit LogbookTab(TicketsModel* model,
                        QWidget *parent = nullptr);
    ~LogbookTab();
    void updateAllModels();

private:
    Ui::LogbookTab *ui;
    TicketsWidget *mTicketsWidget;
};

#endif // LOGBOOKTAB_H
