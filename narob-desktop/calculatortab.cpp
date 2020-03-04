#include "calculatortab.h"
#include "ui_calculatortab.h"

CalculatorTab::CalculatorTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculatorTab)
{
    ui->setupUi(this);
}

CalculatorTab::~CalculatorTab()
{
    delete ui;
}
