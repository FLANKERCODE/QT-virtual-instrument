#ifndef MPU_H
#define MPU_H
#include <QWidget>

class MPUGET
{
public:
    MPUGET();

    double TEM;
    double Roll;
    double Pitch;
    double draw_Pitch;
    double Yaw;
    double Pa;
    double High;

    void MPU_get_value(QByteArray temp2);

 private:
    QByteArray MPU;
    double TL;
    double TH;
    double RollL;
    double RollH;
    double PitchL;
    double PitchH;
    double YawL;
    double YawH;
    double p0;
    double p1;
    double p2;
    double p3;
    double h0;
    double h1;
    double h2;
    double h3;

};

#endif // MPU_H
