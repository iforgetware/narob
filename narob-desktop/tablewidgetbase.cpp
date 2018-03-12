#include "tablewidgetbase.h"
#include "ui_tablewidgetbase.h"

#include "delegates.h"

#include <QDebug>

TableWidgetBase::TableWidgetBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWidgetBase)
{
    ui->setupUi(this);
}

TableWidgetBase::~TableWidgetBase()
{
    delete ui;
}

void TableWidgetBase::initTable()
{
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->verticalHeader()->setVisible(false);
    hideColumn(mModel->fieldIndex("id"));
    show();
}

void TableWidgetBase::setTitle(const QString &title)
{
    mTitle = title;
    ui->title->setText(mTitle);
}

void TableWidgetBase::hideColumn(const int &column)
{
    ui->tableView->setColumnHidden(column, true);
}

void TableWidgetBase::setupColumns(const Fields &fields)
{
    foreach(Field field, fields){
        ui->tableView->setColumnWidth(mModel->fieldIndex(field.mColumn), field.mWidth);
        switch (field.mDelegate){
        case -3:
            ui->tableView->setItemDelegateForColumn(mModel->fieldIndex(field.mColumn),
                                                    new DateTimeDelegate(this));
            break;

        case -2:
            ui->tableView->setItemDelegateForColumn(mModel->fieldIndex(field.mColumn),
                                                    new TimeDelegate(this));
            break;

        case -1:
            ui->tableView->setItemDelegateForColumn(mModel->fieldIndex(field.mColumn),
                                                    new BoolDelegate(this));
            break;

        case 1:
            ui->tableView->setItemDelegateForColumn(mModel->fieldIndex(field.mColumn),
                                                    new OneDecimalDelegate(this));
            break;

        case 2:
            ui->tableView->setItemDelegateForColumn(mModel->fieldIndex(field.mColumn),
                                                    new TwoDecimalDelegate(this));
            break;

        case 3:
            ui->tableView->setItemDelegateForColumn(mModel->fieldIndex(field.mColumn),
                                                    new ThreeDecimalDelegate(this));
            break;

        default:
            break;
        }
    }
}
