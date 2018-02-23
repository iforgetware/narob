#include "refpt.h"

RefPT::RefPT() :
    mId(-1),

    mPredictionId(-1),
    mTicketId(-1),
    mDistance("")
{
}

RefPT::RefPT(const RefPT &refPT) :
    mId(refPT.id()),

    mPredictionId(refPT.predictionId()),
    mTicketId(refPT.ticketId()),
    mDistance(refPT.distance())
{
}
