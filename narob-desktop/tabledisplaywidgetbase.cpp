#include "tabledisplaywidgetbase.h"
#include "ui_tablewidgetbase.h"

TableDisplayWidgetBase::TableDisplayWidgetBase(const QString title,
                                               QWidget *parent) :
    TableWidgetBase(title, parent)
{
}

TableDisplayWidgetBase::~TableDisplayWidgetBase()
{
}

void TableDisplayWidgetBase::initTable()
{
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->verticalHeader()->setVisible(false);
    hide("id");
    show();
}
