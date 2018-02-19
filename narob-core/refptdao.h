#ifndef REFPTDAO_H
#define REFPTDAO_H

#include <memory>
#include <vector>

class QSqlDatabase;
class RefPT;

class RefPTDao
{
public:
    RefPTDao(QSqlDatabase &database);
    void init() const;

    void addRefPT(RefPT &refPT) const;
    void updateRefPT(const RefPT &refPT) const;
    void removeRefPT(int id) const;
    std::unique_ptr<std::vector<std::unique_ptr<RefPT>>> RefPTs() const;

private:
    QSqlDatabase &mDatabase;
};

#endif // REFPTDAO_H
