#include "ticketstrackmodel.h"

TicketsTrackModel::TicketsTrackModel(int trackId, QObject *parent) :
    QSortFilterProxyModel(parent),
    mTrackId(trackId)
{
}

bool TicketsTrackModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex trackIndex = sourceModel()->index(sourceRow, 2, sourceParent);

    return sourceModel()->data(trackIndex).toInt() == mTrackId;
}

//bool TicketsRaceModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
//{

//}
