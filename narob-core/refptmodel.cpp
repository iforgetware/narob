#include "refptmodel.h"

RefPTModel::RefPTModel(QObject *parent) :
    ModelBase(parent),
    mDb(DatabaseManager::instance()),
    mRefPT(mDb.refPTDao.refPT())
{
    setTable("refPT");

    // fields

    // setHeaders();

    select();
}

QModelIndex RefPTModel::addRefPT(const RefPT &refPT)
{
    int rowIndex = rowCount();

    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    RefPT* newRefPT = new RefPT(refPT);
    mDb.refPTDao.addRefPT(*newRefPT);
    mRefPT.append(newRefPT);
    endInsertRows();

    return index(rowIndex, 0);
}

int RefPTModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mRefPT.size();
}

bool RefPTModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0
            || row >= rowCount()
            || count < 0
            || (row + count) > rowCount()) {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while (countLeft--) {
        const RefPT& refPT = *mRefPT.at(row + countLeft);
        mDb.refPTDao.removeRefPT(refPT.id());
    }
    mRefPT.erase(mRefPT.begin() + row,
                 mRefPT.begin() + row + count);
    endRemoveRows();
    return true;
}
