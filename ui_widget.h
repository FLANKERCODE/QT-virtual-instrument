/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Thu May 12 19:46:29 2016
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDial>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLCDNumber *lat_1;
    QLCDNumber *hour;
    QLCDNumber *min;
    QLCDNumber *sec;
    QLCDNumber *TEM;
    QLabel *label;
    QLabel *label_4;
    QLCDNumber *Roll;
    QLabel *label_5;
    QLabel *label_6;
    QLCDNumber *Pitch;
    QLCDNumber *Yaw;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLCDNumber *Pa;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLCDNumber *day;
    QLCDNumber *year;
    QLCDNumber *month;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_2;
    QLabel *label_22;
    QLCDNumber *lat_2;
    QLabel *label_23;
    QLCDNumber *lng_1;
    QLabel *label_3;
    QLCDNumber *lng_2;
    QLabel *label_24;
    QLabel *label_25;
    QLCDNumber *groudrat;
    QLabel *label_26;
    QLabel *label_27;
    QLCDNumber *altitude;
    QLabel *label_28;
    QLCDNumber *geoidalheight;
    QTextBrowser *N;
    QTextBrowser *E;
    QDial *dial;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_35;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *label_38;
    QSlider *verticalSlider;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_39;
    QLabel *label_11;
    QLabel *label_14;
    QLabel *label_40;
    QLabel *label_53;
    QLabel *label_54;
    QLabel *label_55;
    QLabel *label_56;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(725, 412);
        lat_1 = new QLCDNumber(Widget);
        lat_1->setObjectName(QString::fromUtf8("lat_1"));
        lat_1->setGeometry(QRect(117, 210, 41, 31));
        lat_1->setFrameShape(QFrame::Box);
        lat_1->setDigitCount(3);
        lat_1->setSegmentStyle(QLCDNumber::Flat);
        hour = new QLCDNumber(Widget);
        hour->setObjectName(QString::fromUtf8("hour"));
        hour->setGeometry(QRect(130, 180, 31, 21));
        hour->setFrameShape(QFrame::Box);
        hour->setDigitCount(2);
        hour->setSegmentStyle(QLCDNumber::Flat);
        min = new QLCDNumber(Widget);
        min->setObjectName(QString::fromUtf8("min"));
        min->setGeometry(QRect(190, 180, 31, 21));
        min->setFrameShape(QFrame::Box);
        min->setDigitCount(2);
        min->setSegmentStyle(QLCDNumber::Flat);
        sec = new QLCDNumber(Widget);
        sec->setObjectName(QString::fromUtf8("sec"));
        sec->setGeometry(QRect(250, 180, 31, 21));
        sec->setDigitCount(2);
        sec->setSegmentStyle(QLCDNumber::Flat);
        sec->setProperty("value", QVariant(0));
        TEM = new QLCDNumber(Widget);
        TEM->setObjectName(QString::fromUtf8("TEM"));
        TEM->setGeometry(QRect(60, 320, 51, 21));
        TEM->setSegmentStyle(QLCDNumber::Flat);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 310, 31, 41));
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(110, 310, 31, 41));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        label_4->setFont(font1);
        Roll = new QLCDNumber(Widget);
        Roll->setObjectName(QString::fromUtf8("Roll"));
        Roll->setGeometry(QRect(60, 380, 61, 21));
        Roll->setDigitCount(6);
        Roll->setSegmentStyle(QLCDNumber::Flat);
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 370, 41, 41));
        label_5->setFont(font);
        label_6 = new QLabel(Widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(120, 380, 16, 21));
        label_6->setFont(font1);
        Pitch = new QLCDNumber(Widget);
        Pitch->setObjectName(QString::fromUtf8("Pitch"));
        Pitch->setGeometry(QRect(220, 380, 61, 21));
        Pitch->setDigitCount(6);
        Pitch->setSegmentStyle(QLCDNumber::Flat);
        Yaw = new QLCDNumber(Widget);
        Yaw->setObjectName(QString::fromUtf8("Yaw"));
        Yaw->setGeometry(QRect(220, 350, 61, 21));
        Yaw->setDigitCount(6);
        Yaw->setSegmentStyle(QLCDNumber::Flat);
        label_7 = new QLabel(Widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(180, 340, 41, 41));
        label_7->setFont(font);
        label_8 = new QLabel(Widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(180, 370, 41, 41));
        label_8->setFont(font);
        label_9 = new QLabel(Widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(280, 380, 16, 21));
        label_9->setFont(font1);
        label_10 = new QLabel(Widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(280, 350, 16, 21));
        label_10->setFont(font1);
        Pa = new QLCDNumber(Widget);
        Pa->setObjectName(QString::fromUtf8("Pa"));
        Pa->setGeometry(QRect(60, 350, 71, 21));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        Pa->setFont(font2);
        Pa->setDigitCount(7);
        Pa->setSegmentStyle(QLCDNumber::Flat);
        label_12 = new QLabel(Widget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 340, 31, 41));
        label_12->setFont(font);
        label_13 = new QLabel(Widget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(130, 340, 21, 41));
        label_13->setFont(font1);
        label_15 = new QLabel(Widget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(20, 140, 61, 41));
        label_15->setFont(font);
        label_16 = new QLabel(Widget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(170, 170, 21, 41));
        label_16->setFont(font);
        label_17 = new QLabel(Widget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(230, 170, 21, 41));
        label_17->setFont(font);
        label_18 = new QLabel(Widget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(290, 170, 21, 41));
        label_18->setFont(font);
        day = new QLCDNumber(Widget);
        day->setObjectName(QString::fromUtf8("day"));
        day->setGeometry(QRect(250, 150, 31, 21));
        day->setFrameShape(QFrame::Box);
        day->setDigitCount(2);
        day->setSegmentStyle(QLCDNumber::Flat);
        day->setProperty("value", QVariant(0));
        year = new QLCDNumber(Widget);
        year->setObjectName(QString::fromUtf8("year"));
        year->setGeometry(QRect(100, 150, 61, 21));
        year->setFrameShape(QFrame::Box);
        year->setDigitCount(4);
        year->setSegmentStyle(QLCDNumber::Flat);
        month = new QLCDNumber(Widget);
        month->setObjectName(QString::fromUtf8("month"));
        month->setGeometry(QRect(190, 150, 31, 21));
        month->setDigitCount(2);
        month->setSegmentStyle(QLCDNumber::Flat);
        label_19 = new QLabel(Widget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(170, 140, 21, 41));
        label_19->setFont(font);
        label_20 = new QLabel(Widget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(290, 140, 21, 41));
        label_20->setFont(font);
        label_21 = new QLabel(Widget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(230, 140, 21, 41));
        label_21->setFont(font);
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 210, 31, 20));
        label_2->setFont(font);
        label_22 = new QLabel(Widget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(157, 210, 41, 21));
        label_22->setFont(font1);
        lat_2 = new QLCDNumber(Widget);
        lat_2->setObjectName(QString::fromUtf8("lat_2"));
        lat_2->setGeometry(QRect(180, 210, 101, 31));
        lat_2->setDigitCount(8);
        lat_2->setSegmentStyle(QLCDNumber::Flat);
        label_23 = new QLabel(Widget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(157, 250, 41, 21));
        label_23->setFont(font1);
        lng_1 = new QLCDNumber(Widget);
        lng_1->setObjectName(QString::fromUtf8("lng_1"));
        lng_1->setGeometry(QRect(117, 250, 41, 31));
        lng_1->setFrameShape(QFrame::Box);
        lng_1->setDigitCount(3);
        lng_1->setSegmentStyle(QLCDNumber::Flat);
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 250, 31, 17));
        label_3->setFont(font);
        lng_2 = new QLCDNumber(Widget);
        lng_2->setObjectName(QString::fromUtf8("lng_2"));
        lng_2->setGeometry(QRect(180, 250, 101, 31));
        lng_2->setDigitCount(8);
        lng_2->setSegmentStyle(QLCDNumber::Flat);
        label_24 = new QLabel(Widget);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(280, 210, 16, 21));
        label_24->setFont(font1);
        label_25 = new QLabel(Widget);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(280, 250, 16, 21));
        label_25->setFont(font1);
        groudrat = new QLCDNumber(Widget);
        groudrat->setObjectName(QString::fromUtf8("groudrat"));
        groudrat->setGeometry(QRect(220, 320, 61, 21));
        groudrat->setSegmentStyle(QLCDNumber::Flat);
        label_26 = new QLabel(Widget);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(180, 310, 31, 41));
        label_26->setFont(font);
        label_27 = new QLabel(Widget);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(20, 290, 67, 17));
        label_27->setFont(font);
        altitude = new QLCDNumber(Widget);
        altitude->setObjectName(QString::fromUtf8("altitude"));
        altitude->setGeometry(QRect(60, 290, 51, 21));
        altitude->setSegmentStyle(QLCDNumber::Flat);
        label_28 = new QLabel(Widget);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(130, 290, 91, 17));
        label_28->setFont(font);
        geoidalheight = new QLCDNumber(Widget);
        geoidalheight->setObjectName(QString::fromUtf8("geoidalheight"));
        geoidalheight->setGeometry(QRect(220, 290, 61, 21));
        geoidalheight->setFrameShape(QFrame::Box);
        geoidalheight->setFrameShadow(QFrame::Raised);
        geoidalheight->setSegmentStyle(QLCDNumber::Flat);
        N = new QTextBrowser(Widget);
        N->setObjectName(QString::fromUtf8("N"));
        N->setGeometry(QRect(60, 210, 31, 31));
        N->setFrameShape(QFrame::NoFrame);
        E = new QTextBrowser(Widget);
        E->setObjectName(QString::fromUtf8("E"));
        E->setGeometry(QRect(60, 250, 31, 31));
        E->setFrameShape(QFrame::NoFrame);
        dial = new QDial(Widget);
        dial->setObjectName(QString::fromUtf8("dial"));
        dial->setGeometry(QRect(560, 260, 161, 121));
        dial->setMinimum(-180);
        dial->setMaximum(180);
        dial->setSingleStep(1);
        dial->setPageStep(10);
        dial->setWrapping(true);
        dial->setNotchesVisible(true);
        label_29 = new QLabel(Widget);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(635, 240, 31, 17));
        label_29->setFont(font2);
        label_30 = new QLabel(Widget);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(635, 380, 21, 20));
        label_30->setFont(font2);
        label_31 = new QLabel(Widget);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(560, 300, 31, 31));
        label_31->setFont(font2);
        label_32 = new QLabel(Widget);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(710, 300, 31, 31));
        label_32->setFont(font2);
        label_35 = new QLabel(Widget);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(680, 260, 41, 17));
        QFont font3;
        font3.setPointSize(8);
        font3.setBold(false);
        font3.setWeight(50);
        label_35->setFont(font3);
        label_36 = new QLabel(Widget);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(680, 360, 41, 17));
        label_36->setFont(font3);
        label_37 = new QLabel(Widget);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setGeometry(QRect(580, 360, 41, 17));
        label_37->setFont(font3);
        label_38 = new QLabel(Widget);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setGeometry(QRect(580, 260, 41, 17));
        label_38->setFont(font3);
        verticalSlider = new QSlider(Widget);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setGeometry(QRect(340, 20, 29, 211));
        verticalSlider->setMinimum(-90);
        verticalSlider->setMaximum(90);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setInvertedAppearance(false);
        verticalSlider->setInvertedControls(false);
        verticalSlider->setTickPosition(QSlider::TicksBelow);
        verticalSlider->setTickInterval(5);
        label_33 = new QLabel(Widget);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(370, 110, 31, 31));
        label_33->setFont(font);
        label_34 = new QLabel(Widget);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(370, 15, 41, 21));
        label_34->setFont(font);
        label_39 = new QLabel(Widget);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(370, 210, 31, 31));
        label_39->setFont(font);
        label_11 = new QLabel(Widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(110, 280, 21, 41));
        label_11->setFont(font1);
        label_14 = new QLabel(Widget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(280, 280, 21, 41));
        label_14->setFont(font1);
        label_40 = new QLabel(Widget);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setGeometry(QRect(280, 320, 41, 17));
        label_40->setFont(font1);
        label_53 = new QLabel(Widget);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        label_53->setGeometry(QRect(370, 140, 31, 31));
        label_53->setFont(font);
        label_54 = new QLabel(Widget);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        label_54->setGeometry(QRect(370, 170, 31, 41));
        label_54->setFont(font);
        label_55 = new QLabel(Widget);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        label_55->setGeometry(QRect(370, 80, 31, 31));
        label_55->setFont(font);
        label_56 = new QLabel(Widget);
        label_56->setObjectName(QString::fromUtf8("label_56"));
        label_56->setGeometry(QRect(370, 40, 31, 41));
        label_56->setFont(font);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "\346\270\251\345\272\246", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Widget", "\342\204\203", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Widget", "\346\273\232\350\275\254", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Widget", "\302\260", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Widget", "\345\201\217\350\210\252", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Widget", "\344\277\257\344\273\260", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Widget", "\302\260", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Widget", "\302\260", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Widget", "\346\260\224\345\216\213", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("Widget", "Pa", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("Widget", "\345\214\227\344\272\254\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("Widget", "\346\227\266", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("Widget", "\345\210\206", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("Widget", "\347\247\222", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("Widget", "\345\271\264", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("Widget", "\346\227\245", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("Widget", "\346\234\210", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "\347\272\254\345\272\246", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("Widget", "\302\260", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("Widget", "\302\260", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "\347\273\217\345\272\246", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("Widget", "\357\274\202", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("Widget", "\357\274\202", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("Widget", "\345\234\260\351\200\237", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("Widget", "\346\265\267\346\213\224", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("Widget", "\345\244\247\345\234\260\346\260\264\345\207\206\351\235\242\351\253\230\345\272\246", 0, QApplication::UnicodeUTF8));
        N->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Ubuntu'; font-size:14pt;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        E->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Ubuntu'; font-size:14pt;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("Widget", "N", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("Widget", "S", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("Widget", "W", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("Widget", "E", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("Widget", "N/E", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("Widget", "E/S", 0, QApplication::UnicodeUTF8));
        label_37->setText(QApplication::translate("Widget", "S/W", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("Widget", "N/W", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("Widget", "0\302\260", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("Widget", "90\302\260", 0, QApplication::UnicodeUTF8));
        label_39->setText(QApplication::translate("Widget", "90\302\260", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Widget", "m", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("Widget", "m", 0, QApplication::UnicodeUTF8));
        label_40->setText(QApplication::translate("Widget", "km/h", 0, QApplication::UnicodeUTF8));
        label_53->setText(QApplication::translate("Widget", "30\302\260", 0, QApplication::UnicodeUTF8));
        label_54->setText(QApplication::translate("Widget", "60\302\260", 0, QApplication::UnicodeUTF8));
        label_55->setText(QApplication::translate("Widget", "30\302\260", 0, QApplication::UnicodeUTF8));
        label_56->setText(QApplication::translate("Widget", "60\302\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
