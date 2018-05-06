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

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogBase::onButtonBoxAccepted);
}

TrackDialog::~TrackDialog()
{
    delete ui;
}

void TrackDialog::setupModel()
{
    mModel = new TracksModel(this);

    mMapper = new QDataWidgetMapper(this);
    mMapper->setModel(mModel);
    mMapper->addMapping(ui->nameEdit, 1);
    mMapper->addMapping(ui->elevationEdit, 2);
    mMapper->addMapping(ui->bearingEdit, 3);
    mMapper->addMapping(ui->radioSpinBox, 4);

    mMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

void TrackDialog::createUi()
{
    ui->elevationEdit->setValidator(new QIntValidator(ui->elevationEdit));
    ui->bearingEdit->setValidator(new QIntValidator(0, 360, ui->bearingEdit));
}
