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
        mRow = mModel->rowCount(QModelIndex());
        mModel->insertRow(mRow);
        mMapper->toLast();
    }else{
        mRow = row;
        mMapper->setCurrentModelIndex(mModel->index(row, 0));
    }
}

QModelIndex DialogBase::indexForField(const QString &field)
{
    return mModel->index(mRow,
                         mModel->fieldIndex(field));

}
