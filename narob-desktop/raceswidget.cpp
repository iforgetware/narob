#include "raceswidget.h"

#include "racedialog.h"

RacesWidget::RacesWidget(QWidget *parent) :
    TableEditWidgetBase("Races", parent)
{
    mRacesModel = new RacesModel(ui->tableView);

    mModel = mRacesModel;

    ui->tableView->setModel(mRacesModel);

    setupColumns(RACE_FIELDS);

    init();

    connect(mAddButton, &QPushButton::clicked,
            this, &RacesWidget::addRace);

    connect(mEditButton, &QPushButton::clicked,
            this, &RacesWidget::editRace);

    connect(ui->tableView, &QTableView::doubleClicked,
            this, &RacesWidget::editRace);

    hide("trackId");
}

void RacesWidget::addRace()
{
    RaceDialog *raceDialog = new RaceDialog(-1, this);
    connect(raceDialog, &RaceDialog::ready,
            this, &RacesWidget::updateModel);

    raceDialog->exec();
}

void RacesWidget::editRace()
{
    if(selected()){
        RaceDialog *raceDialog = new RaceDialog(selectedRow(),
                                                this);
        connect(raceDialog, &RaceDialog::ready,
                this, &RacesWidget::updateModel);

        raceDialog->exec();
    }
}

std::shared_ptr<Race> RacesWidget::selectedRace() const
{
    return mRacesModel->raceForRow(selectedRow());
}
