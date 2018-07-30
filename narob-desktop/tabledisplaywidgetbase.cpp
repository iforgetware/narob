#include "tabledisplaywidgetbase.h"
#include "ui_tablewidgetbase.h"

TableDisplayWidgetBase::TableDisplayWidgetBase(QWidget *parent) :
    TableWidgetBase(parent)
{
}

TableDisplayWidgetBase::~TableDisplayWidgetBase()
{
}

void TableDisplayWidgetBase::initTable()
{
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->verticalHeader()->setVisible(false);
    hide("id");
    show();
}
