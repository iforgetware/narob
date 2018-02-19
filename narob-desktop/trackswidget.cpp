#include "trackswidget.h"

#include "trackdialog.h"

TracksWidget::TracksWidget(QWidget *parent) : TableEditWidgetBase(parent)
{
    setTitle("Tracks");

    mTracksModel = new TracksModel(ui->tableView);

    mModel  = mTracksModel;

    ui->tableView->setModel(mTracksModel);

    connect(ui->addButton, &QPushButton::clicked,
            this, &TracksWidget::addTrack);

    connect(ui->editButton, &QPushButton::clicked,
            this, &TracksWidget::editTrack);

    connect(ui->deleteButton, &QPushButton::clicked,
            this, &TracksWidget::deleteTrack);

    // see note in tablewidgetbase.cpp

    setupColumns(mTracksModel->mFields);

    initTable();
}

void TracksWidget::addTrack()
{
    TrackDialog *trackDialog = new TrackDialog(mTracksModel, -1, this);
//    connect(trackDialog, &TrackDialog::ready, this, &TracksWidget::updateModels);

    trackDialog->exec();
}

void TracksWidget::editTrack()
{
    if(selected()){
        int tRow = getSelection();

        TrackDialog *trackDialog = new TrackDialog(mTracksModel, tRow, this);
//        connect(trackDialog, &TrackDialog::ready, this, &TracksWidget::updateModels);

        trackDialog->exec();
    }
}

void TracksWidget::deleteTrack()
{
    if(selected()){
        int tRow = getSelection();

        mTracksModel->removeRow(tRow);
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
