#include "ddcamgifwidget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DDCamGifWidget w;
    w.show();
    return a.exec();
}
