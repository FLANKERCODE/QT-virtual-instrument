#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("unifont",12,25,QFont::Normal);
    a.setFont(font);
    Widget w;
  //  w.showFullScreen();
    w.show();
    return a.exec();
}
