#include "logbooktab.h"
#include "ui_logbooktab.h"
#include "ticketswidget.h"

LogbookTab::LogbookTab(TicketsModel *model,
                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogbookTab)
{
    ui->setupUi(this);

    TicketsWidget* ticketsWidget = new TicketsWidget(model,
                                                     0,
                                                     this);
    ui->gridLayout->addWidget(ticketsWidget, 0, 0);
}

LogbookTab::~LogbookTab()
{
    delete ui;
}
