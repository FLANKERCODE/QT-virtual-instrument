#ifndef GPS_H
#define GPS_H

#include "posix_qextserialport.h"
#include <math.h>

class GPS
{
public:
    GPS();

    double lat_1;
    double lat_2;
    double lng_1;
    double lng_2;
    double groudrat;
    double altitude;
    double geoidalheight;
    double h;
    double m;
    double s;
    double year;
    double month;
    double day;

    void GPS_get_value(QByteArray temp);

private:
     QByteArray GPSdate;
     QByteArray N;
     QByteArray E;
     QByteArray Altitude;
     QByteArray Geoidalheight;
     QByteArray Lat;
     QByteArray Lng;
     QByteArray Groudrat;
     QByteArray time;
};

#endif // GPS_H
