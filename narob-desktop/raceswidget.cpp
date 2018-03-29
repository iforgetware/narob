#include "raceswidget.h"

#include "racedialog.h"

RacesWidget::RacesWidget(QWidget *parent) :
    TableEditWidgetBase(parent)
{
    setTitle("Races");

    mRacesModel = new RacesModel(ui->tableView);

    mModel = mRacesModel;

    ui->tableView->setModel(mRacesModel);

    setupColumns(mRacesModel->fields());

    initTable();

    connect(mAddButton, &QPushButton::clicked,
            this, &RacesWidget::addRace);

    connect(mEditButton, &QPushButton::clicked,
            this, &RacesWidget::editRace);

    connect(ui->tableView, &QTableView::doubleClicked,
            this, &RacesWidget::editRace);

    hideColumn(mRacesModel->fieldIndex("trackId"));
}

void RacesWidget::addRace()
{
    RaceDialog *raceDialog = new RaceDialog(-1, this);
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

Race* RacesWidget::getSelectedRace()
{
    return mRacesModel->getRace(getSelection());
}
