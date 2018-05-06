#include "dialogbase.h"

DialogBase::DialogBase(QWidget *parent) :
    QDialog(parent)
{
}

void DialogBase::onButtonBoxAccepted()
{
    mMapper->submit();
    mModel->submitAll();
    emit ready();
}

void DialogBase::setModelRow(int row)
{
    if(row == -1){
        mModel->insertRow(mModel->rowCount(QModelIndex()));
        mMapper->toLast();
    }else{
        mMapper->setCurrentModelIndex(mModel->index(row, 0));
    }
}
