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

//    connect(readTimer,SIGNAL(timeout()),this,SLOT(LCDMPU()));
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

    GPS gps;
    gps.GPS_get_value(temp);
}

void Widget::LCDGPS()
{
    GPS gps;
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
    if((temp2[0]==0x55)&&(temp2[1]==0x53))
     {
        //温度提取
        MPU[0]=temp2[8];
        MPU[1]=temp2[9];
        if (MPU[0]>=0)
        {
             TL=MPU[0];
        }
        else
        {
            TL=256+MPU[0];
        }
        TH=MPU[1];
        TEM=(double) ( ( (short)TH<<8  )+TL )/100;
     }
     if((temp2[22]==0x55)&&(temp2[23]==0x53))
     {
        //x角度提取
        MPU[2]=temp2[24];
        MPU[3]=temp2[25];
        if (MPU[3]>=0)
        {
             RollH=MPU[3];
             if(MPU[2]>=0)
             {
                 RollL=MPU[2];
             }
             else
             {
                 RollL=256+MPU[2];
             }
        }
        else
        {
              RollH=MPU[3]+1;
              if(MPU[2]>=0)
              {
                  RollL=MPU[2]-256;
              }
              else
              {
                  RollL=MPU[2];
              }
        }
        Roll=(double)(RollH*256+RollL)/32768*180;
        if(Roll>180)  Roll=Roll-360;
        Roll=(double)((int)(Roll*100))/100;//保留两位小数

        //y角度提取
        MPU[4]=temp2[26];
        MPU[5]=temp2[27];
        if (MPU[5]>=0)
        {
             PitchH=MPU[5];
             if(MPU[4]>=0)
             {
                 PitchL=MPU[4];
             }
             else
             {
                 PitchL=256+MPU[4];
             }
        }
        else
        {
              PitchH=MPU[5]+1;
              if(MPU[4]>=0)
              {
                  PitchL=MPU[4]-256;
              }
              else
              {
                  PitchL=MPU[4];
              }
        }
        Pitch=(double)(PitchH*256+PitchL)/32768*180;
        if(Pitch>180)  Pitch=Pitch-360;
        Pitch=(double)((int)(Pitch*100))/100;//保留两位小数
        y=-(int)Pitch;

        //z角度提取
        MPU[6]=temp2[28];
        MPU[7]=temp2[29];
        if (MPU[7]>=0)
        {
             YawH=MPU[7];
             if(MPU[6]>=0)
             {
                 YawL=MPU[6];
             }
             else
             {
                 YawL=256+MPU[6];
             }
        }
        else
        {
              YawH=MPU[7]+1;
              if(MPU[6]>=0)
              {
                  YawL=MPU[6]-256;
              }
              else
              {
                  YawL=MPU[6];
              }
        }
        Yaw=(double)(YawH*256+YawL)/32768*180-90;
        if(Yaw>180)  Yaw=Yaw-360;
        Yaw=(double)((int)(Yaw*100))/100;//保留两位小数
        z=-(int)Yaw;
     }

     //气压提取
     if((temp2[11]==0x55)&&(temp2[12]==0x56))
     {
         MPU[8]=temp2[13];
         MPU[9]=temp2[14];
         MPU[10]=temp2[15];
         MPU[11]=temp2[16];
         p3=MPU[11];
         if (MPU[10]>=0)
         {
              p2=MPU[10];
         }
         else
         {
             p2=256+MPU[10];
         }
         if (MPU[9]>=0)
         {
              p1=MPU[9];
         }
         else
         {
             p1=256+MPU[9];
         }
         if (MPU[8]>=0)
         {
              p0=MPU[8];
         }
         else
         {
             p0=256+MPU[8];
         }
         Pa=256*256*256*p3+256*256*p2+256*p1+p0;
     }

     //高度提取
     if((temp2[11]==0x55)&&(temp2[12]==0x56))
     {
         MPU[12]=temp2[17];
         MPU[13]=temp2[18];
         MPU[14]=temp2[19];
         MPU[15]=temp2[20];
         if(MPU[15]>=0)
         {
                 h3=MPU[15];
                 if (MPU[14]>=0)
                 {
                      h2=MPU[14];
                 }
                 else
                 {
                     h2=256+MPU[14];
                 }
                 if (MPU[13]>=0)
                 {
                      h1=MPU[13];
                 }
                 else
                 {
                     h1=256+MPU[13];
                 }
                 if (MPU[12]>=0)
                 {
                      h0=MPU[12];
                 }
                 else
                 {
                     h0=256+MPU[12];
                 }
         }
         else
         {
                 h3=MPU[15]+1;
                 if (MPU[14]>=0)
                 {
                      h2=MPU[14]-256;
                 }
                 else
                 {
                     h2=MPU[14];
                 }
                 if (MPU[13]>=0)
                 {
                      h1=MPU[13]-256;
                 }
                 else
                 {
                     h1=MPU[13];
                 }
                 if (MPU[12]>=0)
                 {
                      h0=MPU[12]-256;
                 }
                 else
                 {
                     h0=MPU[12];
                 }
         }
         High=256*256*256*h3+256*256*h2+256*h1+h0;
     }
     //显示温度
     ui->TEM->display(    TEM   );
     //显示x角度
     ui->Roll->display(    Roll   );
     //显示y角度
     ui->Pitch->display(    Pitch   );
     ui->verticalSlider->setValue(y);
     //显示z角度
     ui->Yaw->display(    Yaw   );
     ui->dial->setValue(z);
     //显示气压
     ui->Pa->display(    Pa   );
     //显示高度
 //    ui->High->display(    High   );
}

void Widget::LCDMPU()
{

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



