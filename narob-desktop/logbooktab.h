#ifndef LOGBOOKTAB_H
#define LOGBOOKTAB_H

#include <QWidget>

#include "logbookwidget.h"

namespace Ui {
class LogbookTab;
}

class LogbookTab : public QWidget
{
    Q_OBJECT

public:
    explicit LogbookTab(TicketsLogbookModel *tLModel,
                        QWidget *parent = nullptr);
    ~LogbookTab();
    void updateAllModels();

private:
    Ui::LogbookTab *ui;
    LogbookWidget *mLogbookWidget;
};

#endif // LOGBOOKTAB_H
