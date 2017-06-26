#ifndef DDCAMGIFWIDGET_H
#define DDCAMGIFWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QTimerEvent>
#include <QDateTime>
#include <QScreen>
#include <QFileDialog>
#include <QDesktopServices>

#include <3rdparty/qtgifimage/src/gifimage/qgifimage.h>

namespace Ui {
class DDCamGifWidget;
}

class DDCamGifWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DDCamGifWidget(QWidget *parent = 0);
    ~DDCamGifWidget();

protected:
    void paintEvent(QPaintEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *);

private slots:

    void on_restoreBtn_clicked();

    void on_closeBtn_clicked();

    void on_recordBtn_clicked();

    void on_saveToGif_clicked();

    void on_checkBox_toggled(bool checked);

    void on_gifPath_clicked();

private:
    Ui::DDCamGifWidget *ui;
    void setButtonStyle(QPushButton *button, QString imgsrc, int CutSec);
    void setWidgetStyleSheet();
    void initFrameless();
    int mTimerId{-1};

    QList<QImage> mAllPixMap;

    void initGifObj(const QString &fileName);
    void addImage();
    QString mFilePath;
    bool mIsStore{false};
    void winAPIonTop();
    QImage *cool(int delta, QImage *origin);
};

#endif // DDCAMGIFWIDGET_H
