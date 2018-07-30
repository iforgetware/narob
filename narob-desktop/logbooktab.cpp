#include "logbooktab.h"
#include "ui_logbooktab.h"

LogbookTab::LogbookTab(TicketsModel *model,
                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogbookTab)
{
    ui->setupUi(this);

    mTicketsWidget = new TicketsWidget(model,
                                       0,
                                       this);
    ui->gridLayout->addWidget(mTicketsWidget, 0, 0);
}

LogbookTab::~LogbookTab()
{
    delete ui;
}

void LogbookTab::updateAllModels()
{
    mTicketsWidget->updateModel();
}
