#include "trackdialog.h"
#include "ui_trackdialog.h"

#include <QDebug>

TrackDialog::TrackDialog(TracksModel *model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrackDialog),
    mTracksModel(model)
{
    ui->setupUi(this);

    setupModel();

    if(row == -1){
        Track track;
        QModelIndex tIdx = mTracksModel->addTrack(track);
        mTracksModel->select();
        mMapper->setCurrentModelIndex(tIdx);
        connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &TrackDialog::clearEmptyAdd);
    }else{
        mMapper->setCurrentModelIndex(mTracksModel->index(row, 0));
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &TrackDialog::onButtonBoxAccepted);

    createUi();
}

TrackDialog::~TrackDialog()
{
    delete ui;
}

void TrackDialog::setupModel()
{
    mMapper = new QDataWidgetMapper(this);
    mMapper->setModel(mTracksModel);
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

void TrackDialog::onButtonBoxAccepted()
{
    mMapper->submit();
    mTracksModel->submitAll();
}

void TrackDialog::clearEmptyAdd()
{
    mTracksModel->removeRow(mTracksModel->rowCount()-1);
}
