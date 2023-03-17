#include "trackswidget.h"

#include "trackdialog.h"

TracksWidget::TracksWidget(QWidget *parent) :
    TableEditWidgetBase("Tracks", parent)
{
    mTracksModel = new TracksModel(ui->tableView);

    mModel  = mTracksModel;

    ui->tableView->setModel(mTracksModel);

    init();

    connect(mAddButton, &QPushButton::clicked,
            this, &TracksWidget::addTrack);

    connect(mEditButton, &QPushButton::clicked,
            this, &TracksWidget::editTrack);

    connect(ui->tableView, &QTableView::doubleClicked,
            this, &TracksWidget::editTrack);

    setupColumns(TRACK_FIELDS);

    hide("elevation");
}

void TracksWidget::addTrack()
{
    TrackDialog *trackDialog = new TrackDialog(-1, this);
    connect(trackDialog, &TrackDialog::ready,
            this, &TracksWidget::updateModel);

    trackDialog->exec();
}

void TracksWidget::editTrack()
{
    if(selected()){
        TrackDialog *trackDialog = new TrackDialog(selectedRow(),
                                                   this);
        connect(trackDialog, &TrackDialog::ready,
                this, &TracksWidget::updateModel);

        trackDialog->exec();
    }
}
