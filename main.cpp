#include "ddcamgifwidget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("ddui");
    QApplication::setQuitOnLastWindowClosed(false);
    a.setFont(QFont(QStringLiteral("微软雅黑")));

    QWidget w1;
    w1.setWindowFlags(w1.windowFlags() |Qt::FramelessWindowHint|Qt::SubWindow);
    w1.setFixedSize(1,1);
    w1.move(-10,-10);
    w1.show();
    DDCamGifWidget w;
    w.setFocus();
    w.show();
    return a.exec();
}
