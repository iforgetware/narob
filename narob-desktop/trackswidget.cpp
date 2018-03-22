#include "trackswidget.h"

#include "trackdialog.h"

TracksWidget::TracksWidget(QWidget *parent) :
    TableEditWidgetBase(parent)
{
    setTitle("Tracks");

    mTracksModel = new TracksModel(ui->tableView);

    mModel  = mTracksModel;

    ui->tableView->setModel(mTracksModel);

    setupColumns(mTracksModel->fields());

    initTable();

    connect(mAddButton, &QPushButton::clicked,
            this, &TracksWidget::addTrack);

    connect(mEditButton, &QPushButton::clicked,
            this, &TracksWidget::editTrack);

    connect(mDeleteButton, &QPushButton::clicked,
            this, &TracksWidget::deleteTrack);

    connect(ui->tableView, &QTableView::doubleClicked,
            this, &TracksWidget::editTrack);
}

void TracksWidget::addTrack()
{
    TrackDialog *trackDialog = new TrackDialog();
    connect(trackDialog, &TrackDialog::ready,
            this, &TracksWidget::updateModels);

    trackDialog->exec();
}

void TracksWidget::editTrack()
{
    if(selected()){
        int tRow = getSelection();

        TrackDialog *trackDialog = new TrackDialog(tRow);
        connect(trackDialog, &TrackDialog::ready,
                this, &TracksWidget::updateModels);

        trackDialog->exec();
    }
}

void TracksWidget::deleteTrack()
{
    if(selected()){
        int tRow = getSelection();

        mTracksModel->removeRow(tRow);
        mTracksModel->submitAll();
        updateModels();
    }
}

void TracksWidget::updateModels()
{
    mTracksModel->select();
}

Track* TracksWidget::getSelectedTrack()
{
    return mTracksModel->getTrack(getSelection());
}
