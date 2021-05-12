#include <QDebug>

#include <QSqlQuery>

#include <QtMath>
#include <QThread>

#include "observations.h"

using namespace std;


double calcVPwobus(double tc)
// Calculate the saturation vapor pressure given the temperature(celsius)
// Polynomial from Herman Wobus
{
    double eso = 6.1078;
    double c0 = 0.99999683;
    double c1 = -0.90826951E-02;
    double c2 = 0.78736169E-04;
    double c3 = -0.61117958E-06;
    double c4 = 0.43884187E-08;
    double c5 = -0.29883885E-10;
    double c6 = 0.21874425E-12;
    double c7 = -0.17892321E-14;
    double c8 = 0.11112018E-16;
    double c9 = -0.30994571E-19;

    double pol=c0+tc*
               (c1+tc*
                (c2+tc*
                 (c3+tc*
                  (c4+tc*
                   (c5+tc*
                    (c6+tc*
                     (c7+tc*
                      (c8+tc*
                       (c9)
                       )
                      )
                     )
                    )
                   )
                  )
                 )
                );

    return eso/qPow(pol, 8);
}

double calcDensity(double abspressmb, double e, double tc)
//  Calculate the air density in kg/m3
{
    double Rv=461.4964;
    double Rd=287.0531;

    double tk=tc+273.15;
    double pv=e*100.0;
    double pd= (abspressmb-e)*100.0;

    return (pv/(Rv*tk)) + (pd/(Rd*tk));
}

double calcAltitude(double d)
// Calculate the ISA altitude (meters) for a given density (kg/m3)
{
    double g=9.80665;
    double Po=101325.0;
    double To=288.15;
    double L=6.5;
    double R=8.314320;
    double M=28.9644;

    double D=d*1000.0;

    double p2=( (L*R)/(g*M-L*R) )*qLn( (R*To*D)/(M*Po) );

    double H=-(To/L)*( qExp(p2)-1.0 );

    double h=H*1000.0;

    return h;
}

double calcZ(double h)
// Calculate the Z geometric altitude (meters), given the H geopotential altitide (meters)
{
    double r=6369E3;

    return (r*h)/(r-h);
}

double calcH(double z)
// Calculate the H geopotential altitude (meters), given the Z geometric altitide (meters)
{
    double r=6369E3;

    return (r*z)/(r+z);
}

double calcAs2Press(double As, double h)
// Calculate the actual pressure (mb)from the altimeter setting (mb) and geopotential altitude (m)
{
    double k1=.190263;
    double k2=8.417286E-5;

    double p=qPow( (qPow(As,k1)-(k2*h)),(1.0/k1) );

    return p;
}

double calcDynoCorrection(double temp, double abspress, double vapress)
// Calculate dyno correction given temp(celsius), absolute pressure(inchesHg)  and vapor pressure(inchesHg)
{
    double p1=29.235/(abspress-vapress);
    double p2=qPow( ((temp+273.0)/298.0), 0.5);
    double p3=(1.18*(p1*p2) - 0.18);
    return p3;
}

double calcVirtualTemp(double tc, double abspressmb, double emb){
// Calculate virtual temperature given temp(celsius), absolute pressure(mb)  and vapor pressure(mb)

    double vtc = ((tc+273.15) / (1- (0.377995*emb/abspressmb))) - 273.15;

    return (vtc * 9 / 5) + 32;
}


Observations::Observations() :
    DbTableBase("observations",
                OBSERVATION_FIELDS)
{
}


Observation::Observation(double t, double h, double p) :
    DbRecordBase("observations",
                 OBSERVATION_FIELDS)
{
    setValue("temperature", formatNum(t, 1));
    setValue("humidity", formatNum(h, 1));
    setValue("pressure", formatNum(p, 2));

    calcDA();
}

Observation::Observation() :
    Observation(0, 0, 0)
{
}

void Observation::calcDA()
{
    double t = value("temperature").toDouble();
    double h = value("humidity").toDouble();
    double p = value("pressure").toDouble();

    double tc = (5.0/9.0) * (t - 32);
    double es = calcVPwobus(tc);
    double emb = es * h / 100.0;
    double actpressmb = p * IN_TO_MB;
    double airDensity = calcDensity(actpressmb, emb, tc);
    double dCF = calcDynoCorrection(tc,
                                    actpressmb * MB_TO_IN,
                                    emb * MB_TO_IN);
    double densaltm = calcAltitude(airDensity);
    double densaltzm = calcZ(densaltm);
    double da = densaltzm * M_TO_FT;

    setValue("vaporPressure", formatNum(emb * MB_TO_IN, 2));
    setValue("relAirDensity", formatNum(100.0 * (airDensity / 1.225), 1));
    setValue("dynoCorrectionFactor", formatNum(dCF, 3));
    setValue("relativeHP", formatNum(100 / dCF, 1));
    setValue("virtualTemp", formatNum(calcVirtualTemp(tc,
                                                      actpressmb,
                                                      emb),
                                      1));
    setValue("densityAltitude", qRound(da));
}


ObservationsModel::ObservationsModel(QObject *parent) :
    ModelBase("observations",
              OBSERVATION_FIELDS,
              parent)
{
    setSort(fieldIndex("dateTime"), Qt::DescendingOrder);

    select();
}

Observation ObservationsModel::lastObservation()
{
    Observation observation;
    observation.populate(record(0));

    return observation;
}

Observation ObservationsModel::observationForTime(QDateTime dateTime)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM observations "
                  "WHERE dateTime = :dateTime");
    query.bindValue(":dateTime", dateTime);

    query.exec();

    Observation observation;

    if(query.next()){
        observation.populate(query.record());

    }
    // this needs a proper error handler
//    }else{
//        qDebug("Weather not found in Observation Model");
//    }

    query.clear();

    return observation;
}

unique_ptr<vector<unique_ptr<Observation>>> ObservationsModel::observationsForToday()
{
    auto observationsVector = make_unique<vector<unique_ptr<Observation>>>();

    QDate date = QDate::currentDate();

    for(int row = rowCount() - 1; row >= 0 ; row--){
        if(row % 100 == 0){
            qDebug() << "row " << row;
        }
        if(record(row).value("dateTime").toDate() == date){
            auto observation = make_unique<Observation>();

            observation->populate(record(row));

            observationsVector->push_back(move(observation));
        }
    }

    return observationsVector;
}

unique_ptr<vector<unique_ptr<Observation>>> ObservationsModel::observationsForDays(const int days)
{
    auto observationsVector = make_unique<vector<unique_ptr<Observation>>>();

    QDateTime startDateTime;
    startDateTime.setDate(QDate::currentDate().addDays(-days));

    QSqlQuery query;
    query.prepare("SELECT * FROM observations "
                  "WHERE dateTime >= :startDateTime");
    query.bindValue(":startDateTime", startDateTime);

    query.exec();

    while(query.next()){
        auto observation = make_unique<Observation>();

        observation->populate(query.record());

        observationsVector->push_back(move(observation));
    }

    query.clear();

    return observationsVector;
}
