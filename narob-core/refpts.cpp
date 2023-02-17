#include "refpts.h"

Fields refPTFields()
{
    Fields f;

    f << Field("id", "id", 0, 0)
      << Field("predictionId", "PredictionId", 0, 0)
      << Field("ticketId", "TicketId", 0, 0)
      << Field("clock", "Clock", 70, -4);

    return f;
}

RefPTs::RefPTs() :
    DbTableBase()
{
    mFields = refPTFields();
    mTable = "refPTs";
}


RefPT::RefPT() :
    DbRecordBase()
{
    mFields = refPTFields();
    init("refPTs");
}

RefPTsModel::RefPTsModel(QObject *parent) :
    ModelBase("refPTs",
              refPTFields(),
              parent)
{
}
