#include <QHBoxLayout>
#include <QPushButton>

#include "tableeditwidgetbase.h"
#include "ui_tablewidgetbase.h"

TableEditWidgetBase::TableEditWidgetBase(QWidget *parent) :
    TableWidgetBase(parent)
{
}

TableEditWidgetBase::~TableEditWidgetBase()
{
}

void TableEditWidgetBase::initTable()
{
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->verticalHeader()->setVisible(false);
    hideColumn(mModel->fieldIndex("id"));

    mAddButton = new QPushButton("Add", this);
    mEditButton = new QPushButton("Edit", this);
    mDeleteButton = new QPushButton("Delete", this);

    QFrame* buttonFrame = new QFrame(this);
    QHBoxLayout* bFLayout = new QHBoxLayout(buttonFrame);

    bFLayout->addWidget(mAddButton);
    bFLayout->addSpacerItem(new QSpacerItem(1,
                                            1,
                                            QSizePolicy::Expanding,
                                            QSizePolicy::Fixed));
    bFLayout->addWidget(mEditButton);
    bFLayout->addSpacerItem(new QSpacerItem(1,
                                            1,
                                            QSizePolicy::Expanding,
                                            QSizePolicy::Fixed));
    bFLayout->addWidget(mDeleteButton);

    buttonFrame->setLayout(bFLayout);

    ui->gridLayout->addWidget(buttonFrame);

    connect(mDeleteButton, &QPushButton::clicked,
            this, &TableEditWidgetBase::deleteSelectedRow);

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

QModelIndex TableEditWidgetBase::getSelectionIndex()
{
    if(selected()){
        return ui->tableView->selectionModel()->currentIndex();
    }else{
        return QModelIndex();
    }
}

void TableEditWidgetBase::deleteSelectedRow()
{
    if(selected()){
        mModel->removeRow(getSelection());
        mModel->submitAll();
        updateModels();
    }
}

void TableEditWidgetBase::updateModels()
{
    mModel->select();
}
