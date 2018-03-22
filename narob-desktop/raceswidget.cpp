#include "raceswidget.h"

#include "racedialog.h"

RacesWidget::RacesWidget(QWidget *parent) :
    TableEditWidgetBase(parent)
{
    setTitle("Races");

    mRacesModel = new RacesModel(ui->tableView);

    mModel = mRacesModel;

    ui->tableView->setModel(mRacesModel);

    setupColumns(mRacesModel->mFields);

    initTable();

    connect(mAddButton, &QPushButton::clicked,
            this, &RacesWidget::addRace);

    connect(mEditButton, &QPushButton::clicked,
            this, &RacesWidget::editRace);

    connect(mDeleteButton, &QPushButton::clicked,
            this, &RacesWidget::deleteRace);

    connect(ui->tableView, &QTableView::doubleClicked,
            this, &RacesWidget::editRace);
}

void RacesWidget::addRace()
{
    RaceDialog *raceDialog = new RaceDialog();
    connect(raceDialog, &RaceDialog::ready,
            this, &RacesWidget::updateModels);

    raceDialog->exec();
}

void RacesWidget::editRace()
{
    if(selected()){
        int rRow = getSelection();

        RaceDialog *raceDialog = new RaceDialog(rRow, this);
        connect(raceDialog, &RaceDialog::ready,
                this, &RacesWidget::updateModels);

        raceDialog->exec();
    }
}

void RacesWidget::deleteRace()
{
    if(selected()){
        int rRow = getSelection();

        mRacesModel->removeRow(rRow);
        mRacesModel->submitAll();
        updateModels();
    }
}

void RacesWidget::updateModels()
{
    mRacesModel->select();
}

Race* RacesWidget::getSelectedRace()
{
    return mRacesModel->getRace(getSelection());
}
