#ifndef REFPT_H
#define REFPT_H

#include <QString>

#include "narob-core_global.h"

class RefPT : public QDjangoModel
{
public:
    RefPT();

    int id() const { return mId; }
    void setId(const int &id) { mId = id; }

    int predictionId() const { return mPredictionId; }
    void setPrediction(const int predictionId) {mPredictionId = predictionId; }

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
