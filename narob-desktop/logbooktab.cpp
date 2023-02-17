#include "logbooktab.h"
#include "ui_logbooktab.h"

LogbookTab::LogbookTab(TicketsLogbookModel *tLModel,
                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogbookTab)
{
    ui->setupUi(this);

    mLogbookWidget = new LogbookWidget(tLModel,
                                       this);
    ui->gridLayout->addWidget(mLogbookWidget, 0, 0);
}

LogbookTab::~LogbookTab()
{
    delete ui;
}

void LogbookTab::updateAllModels()
{
    mLogbookWidget->updateModel();
}
