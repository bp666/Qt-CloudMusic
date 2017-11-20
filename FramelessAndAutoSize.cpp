#include "FramelessAndAutoSize.h"

FramelessAndAutoSize::FramelessAndAutoSize(QWidget *parent) : QWidget(parent)
{
    m_border=18;
    m_state.MousePressed=false;
    m_state.IsPressBorder=false;

    //启用鼠标跟踪,QMainwindow无效
    //不启用要单机鼠标才追踪
    setMouseTracking(true);
    //取消窗口标题栏
    setWindowFlags(Qt::FramelessWindowHint);
    //设置窗口可拉策略，使用后窗口变小了，不要也行
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

//鼠标在窗口右下角可拉伸窗口
void FramelessAndAutoSize::mouseMoveRect(const QPoint &p)
{
    if(!m_state.IsPressBorder)
    {
        if((p.x()>width()-m_border) && (p.y()>height()-m_border))
        {
            setCursor(Qt::SizeFDiagCursor);
            m_curPos=CursorPos::BottomRight;
        }
        else
        {
            //正常鼠标箭头
            setCursor(Qt::ArrowCursor);
        }
    }
    else
    {
        switch (m_curPos) {
        case CursorPos::BottomRight:
        {
            int setW=QCursor::pos().x()-x();
            int setH=QCursor::pos().y()-y();
            setGeometry(m_state.WindowPos.x(),m_state.WindowPos.y(),setW,setH);
            emit sig_PosChange(setW,setH);
            break;
        }
        default:
            break;
        }
    }
}

void FramelessAndAutoSize::mousePressEvent(QMouseEvent *event)
{
    m_state.PressedSize=this->size();
    m_state.IsPressBorder=false;
    setFocus();
    if (event->button() == Qt::LeftButton)
    {
        //保存按下的位置
        m_state.WindowPos = this->pos();
        //鼠标按下可移动，只允许标题栏就可以了
        if(QRect(0,0,width(),height()-m_border*2).contains(event->pos()))
        {
            //保存鼠标全局位置
            m_state.MousePos = event->globalPos();
            m_state.MousePressed = true;
        }
        else
            m_state.IsPressBorder=true;
    }
}

void FramelessAndAutoSize::mouseReleaseEvent(QMouseEvent *event)
{
    m_state.IsPressBorder=false;
    if (event->button() == Qt::LeftButton)
    {
      this->m_state.MousePressed = false;
    }
}

void FramelessAndAutoSize::mouseMoveEvent(QMouseEvent *event)
{
    //将全局屏幕坐标位置转换为窗口坐标
    mouseMoveRect(mapFromGlobal(QCursor::pos()));
    if (m_state.MousePressed)
        {
            this->move(m_state.WindowPos + (event->globalPos() - m_state.MousePos));
        }
}
