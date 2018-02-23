#include "refptdao.h"

#include <QSqlQuery>
#include <QVariant>

#include "databasemanager.h"

RefPTDao::RefPTDao(QSqlDatabase &database) :
    mDatabase(database)
{
}

void RefPTDao::init() const
{
    // look into using varchar(length) for text fields

    if(!mDatabase.tables().contains("refPT")){
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE refPT ("
                   "id INTEGER PRIMARY KEY,"
                   "predictionId INTEGER,"
                   "ticketId INTEGER,"
                   "distance TEXT)");
        DatabaseManager::debugQuery(query);
    }
}

void RefPTDao::addRefPT(RefPT &refPT) const
{
    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO refPT ("
                  "predictionId,"
                  "ticketId,"
                  "distance"
                  ") VALUES ("
                  ":predictionId, "
                  ":ticketId, "
                  ":distance"
                  ")");

    query.bindValue(":predictionId", refPT.predictionId());
    query.bindValue(":ticketId", refPT.ticketId());
    query.bindValue(":distance", refPT.distance());

    query.exec();

    DatabaseManager::debugQuery(query);

    refPT.setId(query.lastInsertId().toInt());
}

void RefPTDao::removeRefPT(int id) const
{
    QSqlQuery query(mDatabase);

    query.prepare("DELETE from refPT WHERE id=:id");

    query.bindValue(":id", id);

    query.exec();

    DatabaseManager::debugQuery(query);
}

QVector<RefPT*> RefPTDao::refPT() const
{
    QSqlQuery query("SELECT * FROM refPT", mDatabase);

    query.exec();

    QVector<RefPT*> list;

    while(query.next()) {
        RefPT* refPT = new RefPT();
        refPT->setId(query.value("id").toInt());
        refPT->setPredictionId(query.value("predictionId").toInt());
        refPT->setTicketId(query.value("ticketId").toInt());
        refPT->setDistance(query.value("distance").toString());

        list.append(refPT);
    }

    return list;
}
