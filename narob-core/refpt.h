#ifndef REFPT_H
#define REFPT_H

#include <QString>

#include "narob-core_global.h"

class NAROBCORESHARED_EXPORT RefPT
{
public:
    explicit RefPT();
    explicit RefPT(const RefPT &refPT);

    int id() const { return mId; }
    void setId(const int &id) { mId = id; }

    int predictionId() const { return mPredictionId; }
    void setPredictionId(const int predictionId) {mPredictionId = predictionId; }

    int ticketId() const { return mTicketId; }
    void setTicketId(const int ticketId) { mTicketId = ticketId; }

    QString distance() const { return mDistance; }
    void setDistance(const QString &distance) { mDistance = distance; }

private:
    int mId;

    int mPredictionId;
    int mTicketId;
    QString mDistance;
};

#endif // REFPT_H
