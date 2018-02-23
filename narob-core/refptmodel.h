#ifndef REFPTMODEL_H
#define REFPTMODEL_H

#include <QVector>

#include "narob-core_global.h"
#include "modelbase.h"
#include "refpt.h"
#include "databasemanager.h"

class NAROBCORESHARED_EXPORT RefPTModel : public ModelBase
{
    Q_OBJECT

public:
    RefPTModel(QObject* parent = 0);

    QModelIndex addRefPT(const RefPT &refPT);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

private:
    DatabaseManager &mDb;
    QVector<RefPT*> mRefPT;
};

#endif // REFPTMODEL_H
