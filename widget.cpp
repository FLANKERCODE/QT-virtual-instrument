#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QLCDNumber>
#include <QPainter>
#include<math.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    myCom = new Posix_QextSerialPort("/dev/ttyUSB0",QextSerialBase::Polling);
    myCom ->open(QIODevice::ReadWrite);
    //以读写方式打开串口
    myCom->setBaudRate(BAUD9600);
    //波特率设置，我们设置为9600
    myCom->setDataBits(DATA_8);
   //数据位设置，我们设置为8位数据位
    myCom->setParity(PAR_NONE);
    //奇偶校验设置，我们设置为无校验
    myCom->setStopBits(STOP_1);
    //停止位设置，我们设置为1位停止位
    myCom->setFlowControl(FLOW_OFF);
    myCom->setTimeout(100);

    myCom2= new Posix_QextSerialPort("/dev/ttyUSB1",QextSerialBase::Polling);
    myCom2 ->open(QIODevice::ReadWrite);
    //以读写方式打开串口
    myCom2->setBaudRate(BAUD9600);
    //波特率设置，我们设置为9600
    myCom2->setDataBits(DATA_8);
   //数据位设置，我们设置为8位数据位
    myCom2->setParity(PAR_NONE);
    //奇偶校验设置，我们设置为无校验
    myCom2->setStopBits(STOP_1);
    //停止位设置，我们设置为1位停止位
    myCom2->setFlowControl(FLOW_OFF);
    myCom2->setTimeout(20);

    readTimer = new QTimer(this);
    readTimer->start(50);

    readTimer2 = new QTimer(this);
    readTimer2->start(20);

    connect(readTimer,SIGNAL(timeout()),this,SLOT(readMyCom()));
    connect(readTimer,SIGNAL(timeout()),this,SLOT(LCDGPS()));

    connect(readTimer2,SIGNAL(timeout()),this,SLOT(readMyCom2()));

    connect(readTimer2,SIGNAL(timeout()),this,SLOT(LCDMPU()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Widget::readMyCom()
{
    static int i =0;
  /*      static int j =0;
    static int j_2=0;
    static int j_3=0;
    static int comma =0;
    static int point =0; */

    qDebug()<<i++;
    QByteArray temp = myCom->readAll();
    //读取串口缓冲区的所有数据给临时变量temp
//    ui->textBrowser->insertPlainText(temp);
    //将串口的数据显示在窗口的文本浏览器中
    gps.GPS_get_value(temp);
}

void Widget::LCDGPS()
{

    ui->lat_1->display(gps.lat_1);
    ui->lat_2->display(gps.lat_2);
    ui->lng_1->display(gps.lng_1);
    ui->lng_2->display(gps.lng_2);
    ui->groudrat->display(gps.groudrat);
    ui->altitude->display(gps.altitude);
    ui->geoidalheight->display(gps.geoidalheight);
    ui->hour->display(gps.h);
    ui->min->display(gps.m);
    ui->sec->display(gps.s);
    ui->day->display(gps.day);
    ui->month->display(gps.month);
    ui->year->display(gps.year);

    //ui->map->setPixmap(QPixmap(":/new/prefix1/123.jpg"));
}

void Widget::readMyCom2()
{
    static int i =0;
    static int z =0;
    static int y =0;
    qDebug()<<i++;
    QByteArray temp2 = myCom2->readAll();
    //读取串口缓冲区的所有数据给临时变量temp
   // ui->textBrowser_2->insertPlainText(temp2.toHex());
    //将串口的数据显示在窗口的文本浏览器中
    mpu.MPU_get_value(temp2);
}

void Widget::LCDMPU()
{
    //显示温度
    ui->TEM->display(    mpu.TEM   );
    //显示x角度
    ui->Roll->display(    mpu.Roll   );
    //显示y角度
    static int  y=-(int)mpu.Pitch;
    ui->Pitch->display(    mpu.Pitch   );
    ui->verticalSlider->setValue(y);
    //显示z角度
    static int  z=-(int)mpu.Yaw;
    ui->Yaw->display(    mpu.Yaw   );
    ui->dial->setValue(z);
    //显示气压
    ui->Pa->display(    mpu.Pa   );
    //显示高度
//    ui->High->display(    High   );
}


void Widget::on_N_textChanged()
{
    ui->N->moveCursor(QTextCursor::End);
}
void Widget::on_E_textChanged()
{
    ui->E->moveCursor(QTextCursor::End);
}
void Widget::on_textBrowser_textChanged()
{
 //   ui->textBrowser->moveCursor(QTextCursor::End);
}
void Widget::on_textBrowser_2_textChanged()
{
 //   ui->textBrowser_2->moveCursor(QTextCursor::End);
}



void Widget::paintEvent(QPaintEvent *)
{
    static QByteArray pitch;
    GPS gps;
    static const QPoint air_1[3] = {
        QPoint(7, 0),
        QPoint(-7, 0),
        QPoint(0, -20)
    };
    static const QPoint air_2[3] = {
        QPoint(-85, 0),
        QPoint(0, -7),
        QPoint(85, 0)
    };
    static const QPoint air_3[3] = {
        QPoint(3, -98),
        QPoint(-3, -98),
        QPoint(0, -108)
    };
    static const QPoint hand[4] = {
        QPoint(0, 5),
        QPoint(-2, 0),
        QPoint(0, -60),
        QPoint(2, 0)
    };
    QColor purple(127, 0, 127);
    QColor blue(0, 127, 127, 191);
    QColor blank(100,100,100);
    QColor yellow(255,215,0);
    QColor lightgrey(220,220,220);
    QColor red(255,0,0);
    QColor green(34,139,34);
    QColor Reallblank(00,0,0);


    int side = qMin(width(), height());
    //QTime time = QTime::currentTime();
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);


   QPixmap pixmap(":/new/prefix1/map1.jpg");
   painter.drawPixmap(pixmap.rect(),pixmap);

    //经纬线
    painter.setPen(yellow);
    painter.setBrush(Qt::NoBrush);
    painter.drawLine(20,75-gps.lat_1*65/90,300,75-gps.lat_1*65/90 );
    painter.drawLine(160+gps.lng_1*140/180,10,160+gps.lng_1*140/180,140);


    painter.translate(545,130);
    painter.scale(0.9,0.9);
 //  painter.scale(side /464, side / 464);

 //   painter.translate(width()/2, height()/2);
 //   painter.scale(side /250, side / 250);

    //背景色
    painter.setPen(Qt::NoPen);
    painter.setBrush(lightgrey);
    painter.drawEllipse(-116,-116,232,232);

    //飞机机体1
    painter.setPen(Qt::NoPen);
    painter.setBrush(purple);
    painter.save();
    painter.rotate(Roll);
    painter.drawConvexPolygon(air_1, 3);
    painter.restore();

    //大刻度
    painter.setPen(purple);
    for (int i = 0; i < 12; ++i)
    {
        painter.drawLine(108, 0, 116, 0);
        painter.rotate(30.0);
    }

    //指针
    painter.setPen(Qt::NoPen);
    painter.setBrush(blue);
    painter.save();
    painter.rotate(Roll);
    painter.drawConvexPolygon(air_3, 3);
    painter.restore();

    //飞机机体2
    painter.setPen(Qt::NoPen);
    painter.setBrush(blue);
    painter.save();
    painter.rotate(Roll);
    painter.drawConvexPolygon(air_2, 3);
    painter.restore();

    //俯仰刻度线
    painter.save();
    painter.setPen(blank);
    painter.rotate(Roll);
  /*  for(int j=-4;j<5;j++)
    {
        painter.drawLine(-50,-(Pitch+10*j),50,-(Pitch+10*j));
        pitch[0]=fabs(j)+48;
        pitch[1]=48;
        QFont font;
        font.setPixelSize(8);
        painter.setFont(font);
        painter.drawText(60,-(Pitch+10*j)+5,pitch);
    }     */
  /*  for(int j=-45;j<50;j++)
    {
         if ((j % 5) == 0)
        painter.drawLine(-30,-(Pitch+j),30,-(Pitch+j));
    } */
    painter.setPen(green);
    painter.drawLine(-50,-80,50,-80);
    painter.drawLine(-50,-80,-50,-70);
    painter.drawLine(50,-80,50,-70);
    painter.drawLine(-50,80,-50,70);
    painter.drawLine(50,80,50,70);
    painter.drawLine(-50,80,50,80);
    painter.setPen(blank);

    if(fabs(Pitch)<=10)
    {
        for(int j=-3;j<4;j++)
        {
            if(j==0)
            {
                painter.setPen(red);
                painter.drawLine(-60,-(Pitch*2+20*j),55,-(Pitch*2+20*j));
                pitch[0]=48;
                pitch[1]=32;
                QFont font;
                font.setPixelSize(15);
                painter.setFont(font);
                painter.drawText(65,-(Pitch*2+20*j)+5,pitch);
            }
            else
            {
                painter.setPen(blank);
                painter.drawLine(-50,-(Pitch*2+20*j),45,-(Pitch*2+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(Pitch*2+20*j)+5,pitch);
            }
        }
        for(int j=-65;j<70;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(Pitch*2+j),25,-(Pitch*2+j));
           }
    }

    if((Pitch>10)&&(Pitch<=20))
    {
        for(int j=-4;j<3;j++)
        {
            if(j==0)
            {
                painter.setPen(red);
                painter.drawLine(-60,-(Pitch*2+20*j),55,-(Pitch*2+20*j));
                pitch[0]=48;
                pitch[1]=32;
                QFont font;
                font.setPixelSize(15);
                painter.setFont(font);
                painter.drawText(65,-(Pitch*2+20*j)+5,pitch);
            }
            else
            {
                painter.setPen(blank);
                painter.drawLine(-50,-(Pitch*2+20*j),45,-(Pitch*2+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(Pitch*2+20*j)+5,pitch);
            }
        }
        for(int j=-85;j<50;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(Pitch*2+j),25,-(Pitch*2+j));
           }
    }

    if((Pitch>20)&&(Pitch<=30))
    {
        for(int j=-5;j<2;j++)
        {
            if(j==0)
            {
                painter.setPen(red);
                painter.drawLine(-60,-(Pitch*2+20*j),55,-(Pitch*2+20*j));
                pitch[0]=48;
                pitch[1]=32;
                QFont font;
                font.setPixelSize(15);
                painter.setFont(font);
                painter.drawText(65,-(Pitch*2+20*j)+5,pitch);
            }
            else
            {
                painter.setPen(blank);
                painter.drawLine(-50,-(Pitch*2+20*j),45,-(Pitch*2+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(Pitch*2+20*j)+5,pitch);
            }
        }
        for(int j=-105;j<30;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(Pitch*2+j),25,-(Pitch*2+j));
           }
    }

    if((Pitch>30)&&(Pitch<=40))
    {
        for(int j=-6;j<1;j++)
        {
            if(j==0)
            {
                painter.save();
                painter.setPen(red);
                painter.drawLine(-60,-(Pitch*2+20*j),55,-(Pitch*2+20*j));
                pitch[0]=48;
                pitch[1]=32;
                QFont font;
                font.setPixelSize(15);
                painter.setFont(font);
                painter.drawText(65,-(Pitch*2+20*j)+5,pitch);
                painter.restore();
            }
            else
            {
                painter.setPen(blank);
                painter.drawLine(-50,-(Pitch*2+20*j),45,-(Pitch*2+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(Pitch*2+20*j)+5,pitch);
            }
        }
        for(int j=-125;j<10;j++)
        {
                if ((j % 10) == 0)

               painter.drawLine(-30,-(Pitch*2+j),25,-(Pitch*2+j));
           }
    }

    if((Pitch>40)&&(Pitch<=50))
    {
        for(int j=-7;j<0;j++)
        {
                painter.setPen(blank);
                painter.drawLine(-50,-(Pitch*2+20*j),45,-(Pitch*2+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(Pitch*2+20*j)+5,pitch);
        }
        for(int j=-145;j<-10;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(Pitch*2+j),25,-(Pitch*2+j));
           }
    }

    if((Pitch>50)&&(Pitch<=60))
    {
        for(int j=-8;j<-1;j++)
        {
                painter.setPen(blank);
                painter.drawLine(-50,-(Pitch*2+20*j),45,-(Pitch*2+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(Pitch*2+20*j)+5,pitch);
        }
        for(int j=-165;j<-30;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(Pitch*2+j),25,-(Pitch*2+j));
           }
    }

    if((Pitch>60)&&(Pitch<=70))
    {
        for(int j=-9;j<-2;j++)
        {
                painter.setPen(blank);
                painter.drawLine(-50,-(Pitch*2+20*j),45,-(Pitch*2+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(Pitch*2+20*j)+5,pitch);
        }
        for(int j=-185;j<-50;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(Pitch*2+j),25,-(Pitch*2+j));
           }
    }

    if((Pitch>70)&&(Pitch<=80))
    {
        for(int j=-9;j<-3;j++)
        {
                painter.setPen(blank);
                painter.drawLine(-50,-(Pitch*2+20*j),45,-(Pitch*2+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(Pitch*2+20*j)+5,pitch);
        }
        for(int j=-185;j<-70;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(Pitch*2+j),25,-(Pitch*2+j));
           }
    }

    if((Pitch>80)&&(Pitch<=90))
    {
        for(int j=-9;j<-4;j++)
        {
                painter.setPen(blank);
                painter.drawLine(-50,-(Pitch*2+20*j),45,-(Pitch*2+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(Pitch*2+20*j)+5,pitch);
        }
        for(int j=-185;j<-90;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(Pitch*2+j),25,-(Pitch*2+j));
           }
    }

    if ( (Pitch>=-20)&&(Pitch<-10) )
    {
        draw_Pitch=Pitch*2;
        for(int j=-2;j<5;j++)
        {
            if(j==0)
            {
                painter.setPen(red);
                painter.drawLine(-60,-(draw_Pitch+20*j),55,-(draw_Pitch+20*j));
                pitch[0]=48;
                pitch[1]=32;
                QFont font;
                font.setPixelSize(15);
                painter.setFont(font);
                painter.drawText(65,-(draw_Pitch+20*j)+5,pitch);
            }
            else
            {
                painter.setPen(blank);
                painter.drawLine(-50,-(draw_Pitch+20*j),45,-(draw_Pitch+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(draw_Pitch+20*j)+5,pitch);
            }
        }
        for(int j=-45;j<90;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(draw_Pitch+j),25,-(draw_Pitch+j));
           }
    }

    if ( (Pitch>=-30)&&(Pitch<-20) )
    {
        draw_Pitch=Pitch*2;
        for(int j=-1;j<6;j++)
        {
            if(j==0)
            {
                painter.setPen(red);
                painter.drawLine(-60,-(draw_Pitch+20*j),55,-(draw_Pitch+20*j));
                pitch[0]=48;
                pitch[1]=32;
                QFont font;
                font.setPixelSize(15);
                painter.setFont(font);
                painter.drawText(65,-(draw_Pitch+20*j)+5,pitch);
            }
            else
            {
                painter.setPen(blank);
                painter.drawLine(-50,-(draw_Pitch+20*j),45,-(draw_Pitch+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(draw_Pitch+20*j)+5,pitch);
            }
        }
        for(int j=-25;j<110;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(draw_Pitch+j),25,-(draw_Pitch+j));
           }
    }

    if ( (Pitch>=-40)&&(Pitch<-30) )
    {
        draw_Pitch=Pitch*2;
        for(int j=0;j<7;j++)
        {
            if(j==0)
            {
                painter.setPen(red);
                painter.drawLine(-60,-(draw_Pitch+20*j),55,-(draw_Pitch+20*j));
                pitch[0]=48;
                pitch[1]=32;
                QFont font;
                font.setPixelSize(15);
                painter.setFont(font);
                painter.drawText(65,-(draw_Pitch+20*j)+5,pitch);
            }
            else
            {
                painter.setPen(blank);
                painter.drawLine(-50,-(draw_Pitch+20*j),45,-(draw_Pitch+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(draw_Pitch+20*j)+5,pitch);
            }
        }
        for(int j=-5;j<120;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(draw_Pitch+j),25,-(draw_Pitch+j));
           }
    }

    if ( (Pitch>=-50)&&(Pitch<-40) )
    {
        draw_Pitch=Pitch*2;
        for(int j=1;j<8;j++)
        {
                painter.setPen(blank);
                painter.drawLine(-50,-(draw_Pitch+20*j),45,-(draw_Pitch+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(draw_Pitch+20*j)+5,pitch);

        }
        for(int j=15;j<140;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(draw_Pitch+j),25,-(draw_Pitch+j));
           }
    }

    if ( (Pitch>=-60)&&(Pitch<-50) )
    {
        draw_Pitch=Pitch*2;
        for(int j=2;j<9;j++)
        {
                painter.setPen(blank);
                painter.drawLine(-50,-(draw_Pitch+20*j),45,-(draw_Pitch+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(draw_Pitch+20*j)+5,pitch);

        }
        for(int j=35;j<160;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(draw_Pitch+j),25,-(draw_Pitch+j));
           }
    }

    if ( (Pitch>=-70)&&(Pitch<-60) )
    {
        draw_Pitch=Pitch*2;
        for(int j=3;j<10;j++)
        {
                painter.setPen(blank);
                painter.drawLine(-50,-(draw_Pitch+20*j),45,-(draw_Pitch+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(draw_Pitch+20*j)+5,pitch);

        }
        for(int j=55;j<180;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(draw_Pitch+j),25,-(draw_Pitch+j));
           }
    }

    if ( (Pitch>=-80)&&(Pitch<-70) )
    {
        draw_Pitch=Pitch*2;
        for(int j=4;j<10;j++)
        {
                painter.setPen(blank);
                painter.drawLine(-50,-(draw_Pitch+20*j),45,-(draw_Pitch+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(draw_Pitch+20*j)+5,pitch);

        }
        for(int j=75;j<180;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(draw_Pitch+j),25,-(draw_Pitch+j));
           }
    }

    if ( (Pitch>=-90)&&(Pitch<-80) )
    {
        draw_Pitch=Pitch*2;
        for(int j=5;j<10;j++)
        {
                painter.setPen(blank);
                painter.drawLine(-50,-(draw_Pitch+20*j),45,-(draw_Pitch+20*j));
                pitch[0]=fabs(j)+48;
                pitch[1]=48;
                QFont font;
                font.setPixelSize(12);
                painter.setFont(font);
                painter.drawText(55,-(draw_Pitch+20*j)+5,pitch);

        }
        for(int j=95;j<180;j++)
        {
                if ((j % 10) == 0)
               painter.drawLine(-30,-(draw_Pitch+j),25,-(draw_Pitch+j));
           }
    }

    painter.restore();


    //小刻度
    painter.setPen(blue);
    for (int j = 0; j < 60; ++j)
    {
        if ((j % 5) != 0)
            painter.drawLine(112, 0, 116, 0);
        painter.rotate(6.0);
    }

    //仪表外缘
    painter.setPen(blank);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(-116,-116,232,232);
    painter.setPen(yellow);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(-118,-118,236,236);
    painter.setPen(blue);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(-120,-120,240,240);

    painter.save();
    painter.setPen(Reallblank);
    painter.rotate(0);
    painter.drawText(-5,-125,"0");
    painter.rotate(30);
    painter.drawText(-5,-125,"30");
    painter.rotate(30);
    painter.drawText(-5,-125,"60");
    painter.rotate(30);
    painter.drawText(-5,-125,"90");
    painter.rotate(30);
    painter.drawText(-5,-125,"120");
    painter.rotate(30);
    painter.drawText(-5,-125,"150");
    painter.rotate(30);
    painter.drawText(-5,-125,"180");
    painter.rotate(30);
    painter.drawText(-5,-125,"150");
    painter.rotate(30);
    painter.drawText(-5,-125,"120");
    painter.rotate(30);
    painter.drawText(-5,-125,"90");
    painter.rotate(30);
    painter.drawText(-5,-125,"60");
    painter.rotate(30);
    painter.drawText(-5,-125,"30");
    painter.restore();



//sudubiao
    painter.translate(-100,210);
    painter.scale(0.9,0.9);

    painter.setPen(Qt::NoPen);
    painter.setBrush(lightgrey);
    painter.drawEllipse(-70,-70,140,140);

    painter.setPen(blank);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(-70,-70,140,140);
    painter.setPen(yellow);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(-72,-72,144,144);
    painter.setPen(blue);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(-74,-74,148,148);

    painter.save();
    painter.setPen(Reallblank);
    for (int j = 0; j < 6; ++j)
    {
        if (j!= 3)
        painter.drawLine(0, -70, 0, -63);
        painter.rotate(60.0);
    }
    painter.restore();

    painter.save();
    painter.setPen(green);
    painter.rotate(240.0);
    for (int j = 0; j < 9; ++j)
    {
        painter.rotate(12.0);
        if (j!= 4)
        painter.drawLine(0, -70, 0, -65);
    }
    painter.restore();

    painter.save();
    painter.setPen(purple);
    for (int j = 0; j < 5; ++j)
    {
        painter.rotate(12.0);
        if (j!= 4)
        painter.drawLine(0, -70, 0, -65);
    }
    painter.restore();

    painter.save();
    painter.setPen(red);
    painter.rotate(60.0);
    for (int j = 0; j < 5; ++j)
    {
        painter.rotate(12.0);
        if (j!= 4)
        painter.drawLine(0, -70, 0, -65);
    }
    painter.restore();

    painter.save();
    painter.setPen(Reallblank);
    QFont font;
    font.setPixelSize(10);
    painter.setFont(font);
    painter.rotate(240);
    painter.drawText(-5,-79,"0");
    painter.rotate(60);
    painter.drawText(-5,-79,"250");
    painter.rotate(60);
    painter.drawText(-5,-79,"500");
    painter.rotate(60);
    painter.drawText(-5,-79,"750");
    painter.rotate(60);
    painter.drawText(-5,-79,"1000");
    painter.restore();

    painter.save();
    painter.rotate(240);
    painter.setPen(blue);
    painter.setBrush(purple);
    painter.rotate(gps.groudrat);
    painter.drawConvexPolygon(hand,4);
    painter.restore();




}



