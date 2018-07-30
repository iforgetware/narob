#include "trackhistorytab.h"
#include "ui_trackhistorytab.h"

#include <QDebug>

TrackHistoryTab::TrackHistoryTab(TicketsModel* model,
                                 int trackId,
                                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrackHistoryTab)
{
    ui->setupUi(this);

    mTicketsWidget = new TicketsWidget(model,
                                       trackId,
                                       this);
    ui->gridLayout->addWidget(mTicketsWidget, 0, 0);
}

TrackHistoryTab::~TrackHistoryTab()
{
    delete ui;
}

void TrackHistoryTab::updateAllModels()
{
    mTicketsWidget->updateModel();
}
