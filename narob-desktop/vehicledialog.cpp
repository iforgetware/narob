#include "vehicledialog.h"
#include "ui_vehicledialog.h"

VehicleDialog::VehicleDialog(int row, QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::VehicleDialog)
{
    ui->setupUi(this);

    setupModel();

    createUi();

    setModelRow(row);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogBase::onButtonBoxAccepted);
}

VehicleDialog::~VehicleDialog()
{
    delete ui;
}

void VehicleDialog::setupModel()
{
    mModel = new VehiclesModel(this);

    mMapper = new QDataWidgetMapper(this);
    mMapper->setModel(mModel);
    mMapper->addMapping(ui->numberEdit, 1);
    mMapper->addMapping(ui->compClassEdit, 2);
    mMapper->addMapping(ui->weightEdit, 3);

    mMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

void VehicleDialog::createUi()
{
    ui->weightEdit->setValidator(new QIntValidator(ui->weightEdit));
}
