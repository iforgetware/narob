#include "racedialog.h"
#include "ui_racedialog.h"

#include <QDebug>
#include <QSqlRelationalDelegate>

RaceDialog::RaceDialog(int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RaceDialog)
{
    ui->setupUi(this);

    setupModel();

    if(row == -1){
        mRacesModel->insertRow(mRacesModel->rowCount(QModelIndex()));
        mMapper->toLast();
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
    mRacesModel = new RacesModel(this);

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
    emit ready();
}
