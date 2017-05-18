#include "ddcamgifwidget.h"
#include "ui_ddcamgifwidget.h"
#include "frameless_helper.h"
#include <QDesktopWidget>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef Q_OS_WIN32
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#endif

#define  RECORD_WORD  QStringLiteral("录制")
#define  RECORD_STOP  QStringLiteral("停止")
#define  TIMER_INV  100

DDCamGifWidget::DDCamGifWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DDCamGifWidget)
{
    ui->setupUi(this);
    mAllPixMap.clear();
    ui->recordBtn->setText(RECORD_WORD);
    initFrameless();
    setWidgetStyleSheet();
    setAttribute(Qt::WA_TranslucentBackground);
    setButtonStyle(ui->restoreBtn,":/image/sys_button_restore.png",4);
    setButtonStyle(ui->closeBtn,":/image/sys_button_close.png",4);
    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::WindowStaysOnTopHint;
    flags |= Qt::FramelessWindowHint;
    //    setWindowFlags(flags);
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

}
void DDCamGifWidget::setWidgetStyleSheet(){
    QFile file(":/css/camgif.css");
    if(file.open(QIODevice::ReadOnly)){
        setStyleSheet(file.readAll());
    }
    file.close();
}

void DDCamGifWidget::initFrameless()
{
    FramelessHelper *pHelper = new FramelessHelper(this);
    pHelper->activateOn(this);  //激活当前窗体
    pHelper->setTitleHeight(this->height()*0.1);  //设置窗体的标题栏高度
    pHelper->setWidgetMovable(true);  //设置窗体可移动
    pHelper->setWidgetResizable(true);  //设置窗体可缩放
//    winAPIonTop();
    //    pHelper->setRubberBandOnMove(true);  //设置橡皮筋效果-可移动
    //    pHelper->setRubberBandOnResize(true);  //设置橡皮筋效果-可缩放
}

void DDCamGifWidget::initGifObj(const QString& fileName)
{
    QGifImage mGifObj;
    QVector<QRgb> ctable;
    ctable << qRgb(255, 255, 255)
              //           << qRgb(0, 0, 0)
              //           << qRgb(255, 0, 0)
              //           << qRgb(0, 255, 0)
              //           << qRgb(0, 0, 255)
              //           << qRgb(255, 255, 0)
           << qRgb(10, 205, 205)
           << qRgb(255, 0, 255);
    if(mIsStore){
        mGifObj.setGlobalColorTable(ctable, Qt::black);
    }
    mGifObj.setDefaultTransparentColor(Qt::black);
    mGifObj.setDefaultDelay(100);
    mGifObj.clearFrameList();

    //    QString fileName=QDateTime::currentDateTime().toString("yyyyMMdd-hhmmsszzz");
    //    fileName.append(".gif");
    //    fileName.prepend("tmp/");
    foreach (QImage img, mAllPixMap) {
        if(&img){
            mGifObj.addFrame(img);
        }
    }
    mGifObj.save(fileName);
    mAllPixMap.clear();
}

void DDCamGifWidget::addImage()
{
    //grabWidget 来获得中间屏幕的图片， 并赋给pixmap
    QPoint point = ui->MidLabel->mapToGlobal(QPoint(0,0));
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
    QPixmap pixmap  = QPixmap::grabWindow(QApplication::desktop()->winId(),point.x(),point.y(),ui->MidLabel->width(),ui->MidLabel->height());
#else
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmap  = screen->grabWindow(QApplication::desktop()->winId(),point.x(),point.y(),ui->MidLabel->width(),ui->MidLabel->height());
#endif
    if(mIsStore){
        QString fileName=QDateTime::currentDateTime().toString("yyyyMMdd-hhmmsszzz");
        fileName.append(".png");
        fileName.prepend("tmp/");
        pixmap.save(fileName);
    }
    QImage img = pixmap.toImage();
    //    qDebug()<<Q_FUNC_INFO<<&pixmap<<" img "<<&img;
    mAllPixMap.append(img);
}

DDCamGifWidget::~DDCamGifWidget()
{
    delete ui;
}
void DDCamGifWidget::setButtonStyle(QPushButton *button, QString imgsrc, int CutSec)
{
    int PicWidth = QPixmap(imgsrc).width()/CutSec;
    button->setStyleSheet(QString("QPushButton{border-width: 40px; border-image: url(%1)  0 0 0 %2 repeat  repeat;border-width: 0px; border-radius: 0px;}")
                          .append("QPushButton::hover{border-image: url(%1) 0 0 0 %3  repeat  repeat;}")
                          .append("QPushButton::pressed{border-image: url(%1) 0  0 0 %4 repeat  repeat;}")
                          .append("QPushButton::checked{border-image: url(%1) 0  0 0 %4 repeat  repeat;}")
                          .arg(imgsrc).arg(0).arg(PicWidth*1).arg(PicWidth*2));
}
void DDCamGifWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void DDCamGifWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton && event->pos().y() <= 30 )
    {
        if (!this->isFullScreen() &&  this->isMaximized())
        {
            showMaximized();
        }else{
            showNormal();
        }
    }
}

void DDCamGifWidget::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == mTimerId){
        addImage();
    }
}

void DDCamGifWidget::on_restoreBtn_clicked()
{
    if (!this->isFullScreen() &&  !this->isMaximized())
    {
        showMaximized();
    }else{
        showNormal();
    }
}

void DDCamGifWidget::on_closeBtn_clicked()
{
    qApp->quit();
}

void DDCamGifWidget::on_recordBtn_clicked()
{
    if(ui->recordBtn->text() == RECORD_WORD){
        ui->recordBtn->setText(RECORD_STOP);
        mAllPixMap.clear();
        //定时器启动
        if(mTimerId == -1);
        mTimerId = startTimer(TIMER_INV);
    }else{
        ui->recordBtn->setText(RECORD_WORD);
        killTimer(mTimerId);
        mTimerId = -1;
        //定时器停止
    }
}

void DDCamGifWidget::on_saveToGif_clicked()
{
    ui->recordBtn->setText(RECORD_WORD);
    if(mTimerId != -1)
        killTimer(mTimerId);
    mTimerId = -1;
    if(mAllPixMap.size() == 0)return;
    QString fileName = QFileDialog::getSaveFileName(this, QStringLiteral("另存为"),
                                                    ".",
                                                    tr("Images (*.gif)"));
    mFilePath = fileName;
    if(fileName.isEmpty())return;
    initGifObj(fileName);
}

void DDCamGifWidget::on_checkBox_toggled(bool checked)
{
    mIsStore = checked;
}

void DDCamGifWidget::on_gifPath_clicked()
{
    if(mFilePath.isEmpty())return;
    QDesktopServices::openUrl(QUrl(mFilePath));
}
void DDCamGifWidget::winAPIonTop()
{
#ifdef Q_OS_WIN32
        HWND hwnd = (HWND)this->winId();
        DWORD dwstyle = GetWindowLong(hwnd, GWL_EXSTYLE);
        if (dwstyle & WS_EX_TOPMOST)
        {
            dwstyle &= ~WS_EX_TOPMOST;
            SetWindowLong(hwnd, GWL_EXSTYLE, dwstyle);
            SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOSIZE | SWP_SHOWWINDOW);
        }
        else
        {
            dwstyle |= WS_EX_TOPMOST;
            SetWindowLong(hwnd, GWL_EXSTYLE, dwstyle);
            SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOSIZE | SWP_SHOWWINDOW);
        }
#endif
}
