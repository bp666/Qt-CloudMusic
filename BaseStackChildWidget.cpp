#include "BaseStackChildWidget.h"
#include <QPainter>

BaseStackChildWidget::BaseStackChildWidget(QWidget *parent) : QWidget(parent)
{

}

void BaseStackChildWidget::paintEvent(QPaintEvent *)
{
    //在第一个stack子窗口画线
    QPainter p(this);
    p.setPen(QColor(225,225,225));
    p.drawLine(30,40,width()-30,40);
}
