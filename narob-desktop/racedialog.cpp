#include "racedialog.h"
#include "ui_racedialog.h"

#include <QSqlRelationalDelegate>
#include <QDebug>

RaceDialog::RaceDialog(RacesModel *model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RaceDialog),
    mRacesModel(model)
{
    ui->setupUi(this);

    setupModel();

    if(row == -1){
        Race race;
        QModelIndex rIdx = mRacesModel->addRace(race);
        mRacesModel->select();
        mMapper->setCurrentModelIndex(rIdx);
        connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &RaceDialog::clearEmptyAdd);
    }else{
        mMapper->setCurrentModelIndex(mRacesModel->index(row, 0));
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &RaceDialog::onButtonBoxAccepted);

    createUi();
}

RaceDialog::~RaceDialog()
{
    delete ui;
}

void RaceDialog::setupModel()
{
    mMapper = new QDataWidgetMapper(this);

    mMapper->setItemDelegate(new QSqlRelationalDelegate(ui->trackComboBox));

    mMapper->setModel(mRacesModel);
    mMapper->addMapping(ui->dateEdit, 1);
    mMapper->addMapping(ui->nameEdit, 2);
    mMapper->addMapping(ui->trackComboBox, 3);

    mMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

void RaceDialog::createUi()
{
    mRacesModel->relationModel(3)->select();

    ui->trackComboBox->setModel(mRacesModel->relationModel(3));
    ui->trackComboBox->setModelColumn(mRacesModel->relationModel(3)->fieldIndex("name"));
}

void RaceDialog::onButtonBoxAccepted()
{
    mMapper->submit();
    mRacesModel->submitAll();
}

void RaceDialog::clearEmptyAdd()
{
    mRacesModel->removeRow(mRacesModel->rowCount()-1);
}
