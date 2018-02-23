#ifndef REFPTDAO_H
#define REFPTDAO_H

#include <QSqlDatabase>
#include <QVector>

#include "refpt.h"

class RefPTDao
{
public:
    RefPTDao(QSqlDatabase &database);
    void init() const;

    void addRefPT(RefPT &refPT) const;
    void removeRefPT(int id) const;
    QVector<RefPT*> refPT() const;

private:
    QSqlDatabase &mDatabase;
};

#endif // REFPTDAO_H
