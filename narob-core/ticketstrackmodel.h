#ifndef TICKETSTRACKMODEL_H
#define TICKETSTRACKMODEL_H

#include <QSortFilterProxyModel>

#include "narob-core_global.h"

class NAROBCORESHARED_EXPORT TicketsTrackModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    TicketsTrackModel(int trackId, QObject* parent);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
//    bool lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const;

private:
    int mTrackId;
};

#endif // TICKETSTRACKMODEL_H
