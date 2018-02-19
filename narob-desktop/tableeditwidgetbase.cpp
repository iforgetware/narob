#include "tableeditwidgetbase.h"
#include "ui_tableeditwidgetbase.h"

#include "delegates.h"

TableEditWidgetBase::TableEditWidgetBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableEditWidgetBase)
{
    ui->setupUi(this);
}

TableEditWidgetBase::~TableEditWidgetBase()
{
    delete ui;
}

void TableEditWidgetBase::initTable()
{
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // could add the following, but would have to abstract out edit slot
    // could also go in each widget without abstraction
    //connect(ui->tableView, &QTableView::doubleClicked, this, "edit");

    // consider this instead of manually setting widths

    //ui->tableView->resizeColumnsToContents();


    // see what this does

    //ui->tableView->horizontalHeader()->setStretchLastSection();

    ui->tableView->verticalHeader()->setVisible(false);
    hideColumn(0);
    show();
}

bool TableEditWidgetBase::selected()
{
    return ui->tableView->selectionModel()->hasSelection();
}

int TableEditWidgetBase::getSelection()
{
    if(selected()){
        return ui->tableView->selectionModel()->currentIndex().row();
    }else{
        return 0;
    }
}

void TableEditWidgetBase::setTitle(const QString &title)
{
    mTitle = title;
    ui->title->setText(mTitle);
}

void TableEditWidgetBase::hideColumn(const int &column)
{
    ui->tableView->setColumnHidden(column, true);
}

void TableEditWidgetBase::setupColumns(const Fields &fields)
{
    foreach(Field field, fields){
        ui->tableView->setColumnWidth(mModel->fieldIndex(field.mColumn), field.mWidth);
        switch (field.mDelegate){
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
