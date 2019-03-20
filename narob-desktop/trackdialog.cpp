#include "trackdialog.h"
#include "ui_trackdialog.h"

#include <QDebug>

TrackDialog::TrackDialog(int row, QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::TrackDialog)
{
    ui->setupUi(this);

    setupModel();

    createUi();

    setModelRow(row);

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &DialogBase::onButtonBoxAccepted);
}

TrackDialog::~TrackDialog()
{
    delete ui;
}

void TrackDialog::setupModel()
{
    mModel = new TracksModel(this);

    mMapper->setModel(mModel);
    mMapper->addMapping(ui->nameEdit, mModel->fieldIndex("name"));
    mMapper->addMapping(ui->elevationEdit, mModel->fieldIndex("elevation"));
    mMapper->addMapping(ui->bearingEdit, mModel->fieldIndex("bearing"));
    mMapper->addMapping(ui->radioSpinBox, mModel->fieldIndex("radio"));
}

void TrackDialog::createUi()
{
    ui->elevationEdit->setValidator(new QIntValidator(ui->elevationEdit));
    ui->bearingEdit->setValidator(new QIntValidator(0, 360, ui->bearingEdit));
}
