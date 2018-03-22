#include "ticketsracemodel.h"

#include <QDebug>

TicketsRaceModel::TicketsRaceModel(int raceId, QObject *parent) :
    QSortFilterProxyModel(parent),
    mRaceId(raceId)
{
}

bool TicketsRaceModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex raceIndex = sourceModel()->index(sourceRow, 3, sourceParent);

    return sourceModel()->data(raceIndex).toInt() == mRaceId;
}
