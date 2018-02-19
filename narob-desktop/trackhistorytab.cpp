#include "trackhistorytab.h"
#include "ui_trackhistorytab.h"
#include "ticketswidget.h"

#include <QDebug>

TrackHistoryTab::TrackHistoryTab(TicketsModel* model,
                                 int trackId,
                                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrackHistoryTab)
{
    ui->setupUi(this);

    TicketsWidget *ticketsWidget = new TicketsWidget(model,
                                                     trackId,
                                                     this);
    ui->gridLayout->addWidget(ticketsWidget, 0, 0);
}

TrackHistoryTab::~TrackHistoryTab()
{
    delete ui;
}
