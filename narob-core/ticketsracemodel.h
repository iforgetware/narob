#ifndef TICKETSRACEMODEL_H
#define TICKETSRACEMODEL_H

#include <QSortFilterProxyModel>

#include "narob-core_global.h"

class NAROBCORESHARED_EXPORT TicketsRaceModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    TicketsRaceModel(int raceId, QObject* parent);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
//    bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const;

private:
    int mRaceId;
};

#endif // TICKETSRACEMODEL_H
