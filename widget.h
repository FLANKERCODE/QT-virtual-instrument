#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDialog>
#include <QPaintEvent>

#include "posix_qextserialport.h"
#include "lcd.h"
#include "gps.h"

//class QLCDNumber;
namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *event);

private:
    Ui::Widget *ui;
    Posix_QextSerialPort *myCom;
    Posix_QextSerialPort *myCom2;

    QTimer *readTimer;
    QTimer *readTimer2;
    QTimer *timer;

    QByteArray MPU;
    double TEM;
    double TL;
    double TH;

    double Roll;
    double RollL;
    double RollH;

    double Pitch;
    double PitchL;
    double PitchH;

    double draw_Pitch;


    double Yaw;
    double YawL;
    double YawH;

    double Pa;
    double p0;
    double p1;
    double p2;
    double p3;

    double High;
    double h0;
    double h1;
    double h2;
    double h3;

 //   QLCDNumber *lcdNumber;


private slots:

    void readMyCom(); //读取串口
    void readMyCom2(); //读取串口
    void LCDGPS();
    void LCDMPU();
 //   void on_textBrowser_destroyed();
  //  void on_lcdNumber_destroyed();
 //   void on_lcdNumber_objectNameChanged(const QString &objectName);

    void on_N_textChanged();
    void on_textBrowser_textChanged();
    void on_textBrowser_2_textChanged();
    void on_E_textChanged();

};

#endif // WIDGET_H
