#ifndef FRAMELESSANDAUTOSIZE_H
#define FRAMELESSANDAUTOSIZE_H

/////////////////////////////////////////////////
//无框架和自动尺寸
//1.去掉窗口标题栏
//2.鼠标点击窗口拖动与改变窗口尺寸
/////////////////////////////////////////////////

#include <QWidget>
#include <QMouseEvent>

//鼠标位置
enum CursorPos{Default,Right,Left,Bottom,Top,TopRight,TopLeft,BottomRight,BottomLeft};

//鼠标按下窗口的状态
struct pressWindowsState
{
    bool    MousePressed; //按住鼠标移动
    bool   IsPressBorder; //是否在窗口边界
    QPoint  MousePos;     //移动位置
    QPoint  WindowPos;    //窗口位置
    QSize PressedSize;    //鼠标点击窗口的位置
};

class FramelessAndAutoSize : public QWidget
{
    Q_OBJECT
public:
    explicit FramelessAndAutoSize(QWidget *parent = 0);
    ~FramelessAndAutoSize(){}

    //根据鼠标Pos移动窗口
    void mouseMoveRect(const QPoint &p);

signals:
    void sig_PosChange(int,int);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);

    pressWindowsState m_state;
    int m_border;
    CursorPos m_curPos;
};

#endif // FRAMELESSANDAUTOSIZE_H
