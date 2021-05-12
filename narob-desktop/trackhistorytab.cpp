#include "trackhistorytab.h"
#include "ui_trackhistorytab.h"

#include <QDebug>

TrackHistoryTab::TrackHistoryTab(std::shared_ptr<Vehicle> vehicle,
                                 int trackId,
                                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrackHistoryTab)
{
    ui->setupUi(this);

    mTrackHistoryWidget = new TrackHistoryWidget(vehicle,
                                                 trackId,
                                                 this);
    ui->gridLayout->addWidget(mTrackHistoryWidget, 0, 0);
}

TrackHistoryTab::~TrackHistoryTab()
{
    delete ui;
}

void TrackHistoryTab::updateAllModels()
{
    mTrackHistoryWidget->updateModel();
}
