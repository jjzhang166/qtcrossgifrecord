#ifndef FRAMELESS_HELPER_H
#define FRAMELESS_HELPER_H

#include <QObject>
#include <QDebug>

class QWidget;
class FramelessHelperPrivate;

class FramelessHelper : public QObject
{
    Q_OBJECT

public:
    FramelessHelper(QObject *parent = 0);
    ~FramelessHelper();
    void activateOn(QWidget *topLevelWidget);
    void removeFrom(QWidget *topLevelWidget);
    void setWidgetMovable(bool movable);
    void setWidgetResizable(bool resizable);
    void setRubberBandOnMove(bool movable);
    void setRubberBandOnResize(bool resizable);
    void setBorderWidth(uint width);
    void setTitleHeight(uint height);
    bool widgetResizable();
    bool widgetMovable();
    bool rubberBandOnMove();
    bool rubberBandOnResisze();
    uint borderWidth();
    uint titleHeight();

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);

private:
    FramelessHelperPrivate *d;
};

#endif //FRAMELESS_HELPER_H
