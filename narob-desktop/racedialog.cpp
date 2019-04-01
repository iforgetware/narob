#include "racedialog.h"
#include "ui_racedialog.h"

#include <QDebug>
#include <QSqlRelationalDelegate>

RaceDialog::RaceDialog(int row, QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::RaceDialog)
{
    ui->setupUi(this);

    setupModel();

    createUi();

    setModelRow(row);

    if(row == -1){
        ui->dateEdit->setDate(QDate::currentDate());
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogBase::onButtonBoxAccepted);
}

RaceDialog::~RaceDialog()
{
    delete ui;
}

void RaceDialog::setupModel()
{
    mModel = new RacesModel(this);

    mMapper->setItemDelegate(new QSqlRelationalDelegate(ui->trackComboBox));

    mMapper->setModel(mModel);

    // These should use fieldIndex({field})
    // trackComboBox sets trackId to the track name when fI() is used

    mMapper->addMapping(ui->dateEdit, 1);
    mMapper->addMapping(ui->nameEdit, 2);
    mMapper->addMapping(ui->trackComboBox, 3);
}

void RaceDialog::createUi()
{
    mModel->relationModel(3)->select();

    ui->trackComboBox->setModel(mModel->relationModel(3));
    ui->trackComboBox->setModelColumn(mModel->relationModel(3)->fieldIndex("name"));
}
