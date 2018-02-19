#include "raceswidget.h"

#include "racedialog.h"
#include <QDebug>

RacesWidget::RacesWidget(QWidget *parent) : TableEditWidgetBase(parent)
{
    setTitle("Races");

    mRacesModel = new RacesModel(ui->tableView);

    mModel = mRacesModel;

    ui->tableView->setModel(mRacesModel);

    connect(ui->addButton, &QPushButton::clicked,
            this, &RacesWidget::addRace);

    connect(ui->editButton, &QPushButton::clicked,
            this, &RacesWidget::editRace);

    connect(ui->deleteButton, &QPushButton::clicked,
            this, &RacesWidget::deleteRace);

    setupColumns(mRacesModel->mFields);

    initTable();
}

void RacesWidget::addRace()
{
    RaceDialog *raceDialog = new RaceDialog(mRacesModel, -1, this);

    raceDialog->exec();
}

void RacesWidget::editRace()
{
    if(selected()){
        int rRow = getSelection();

        RaceDialog *raceDialog = new RaceDialog(mRacesModel, rRow, this);

        raceDialog->exec();
    }
}

void RacesWidget::deleteRace()
{
    if(selected()){
        int rRow = getSelection();

        mRacesModel->removeRow(rRow);
        mRacesModel->select();
    }
}

Race* RacesWidget::getSelectedRace()
{
    return mRacesModel->getRace(getSelection());
}
