#include <QHBoxLayout>
#include <QPushButton>

#include "tableeditwidgetbase.h"
#include "ui_tablewidgetbase.h"

TableEditWidgetBase::TableEditWidgetBase(const QString title, QWidget *parent) :
    TableWidgetBase(title, parent)
{
}

TableEditWidgetBase::~TableEditWidgetBase()
{
}

void TableEditWidgetBase::init()
{
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->verticalHeader()->setVisible(false);
    hide("id");

    QString item = mTitle.chopped(1);
    mAddButton = new QPushButton("Add " + item, this);
    mEditButton = new QPushButton("Edit " + item, this);
    mDeleteButton = new QPushButton("Delete " + item, this);

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
}

bool TableEditWidgetBase::selected() const
{
    return ui->tableView->selectionModel()->hasSelection();
}

int TableEditWidgetBase::selectedRow() const
{
    if(selected()){
        return ui->tableView->selectionModel()->currentIndex().row();
    }else{
        return 0;
    }
}

void TableEditWidgetBase::deleteSelectedRow()
{
    if(selected()){
        mModel->removeRow(selectedRow());
        mModel->submitAll();
        updateModel();
    }
}
