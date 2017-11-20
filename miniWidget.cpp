#include "miniWidget.h"

miniWidget::miniWidget(QWidget *parent) : QFrame(parent)
{
    setFixedSize(300,42);

    move(1200,100);

    m_mouseState = false;

    //无任务栏图标，无工具栏，置顶显示
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint);

    setStyleSheet("QFrame{background:rgb(102,183,255)}");

    //不追踪鼠标无法拖动窗口
    setMouseTracking(true);

    init_miniWidget();
}

void miniWidget::mousePressEvent(QMouseEvent *event)
{
    m_WindowPos = this->pos();
    if(QRect(0,0,width(),height()).contains(event->pos()) && event->button() == Qt::LeftButton)
    {
        m_MousePos = event->globalPos();
        m_mouseState = true;
    }
}

void miniWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_mouseState)
    {
        move(m_WindowPos + (event->globalPos() - m_MousePos));
    }
}

void miniWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_mouseState = false;
}

void miniWidget::enterEvent(QEvent *)
{
    m_songNameLab->setVisible(false);
    m_singleLab->setVisible(false);
    m_palyFrame->setVisible(true);
}

void miniWidget::leaveEvent(QEvent *)
{
    m_songNameLab->setVisible(true);
    m_singleLab->setVisible(true);
    m_palyFrame->setVisible(false);
}

void miniWidget::init_miniWidget()
{
    m_vMainLayout = new QVBoxLayout(this);

    m_mainFrame = new QFrame;
    m_mainFrame->setFixedSize(300,42);

    m_hMainLayout = new QHBoxLayout(m_mainFrame);

//图片
    m_photoBtn = new QPushButton;
    m_photoBtn->setFixedSize(42,42);
    m_photoBtn->setCursor(Qt::PointingHandCursor);
    m_photoBtn->setStyleSheet("QPushButton{border-image:url(:/images/mini/photo.png)}");

//歌曲信息
    m_vInfoLayout = new QVBoxLayout;

    m_songNameLab = new QLabel;
    m_songNameLab->setFixedSize(150,15);
    m_songNameLab->setText("未知");
    m_songNameLab->setAlignment(Qt::AlignCenter);
    m_songNameLab->setStyleSheet("QLabel{color:#FFFFFF}");

    m_singleLab = new QLabel;
    m_singleLab->setFixedSize(150,15);
    m_singleLab->setText("未知");
    m_singleLab->setAlignment(Qt::AlignCenter);

    m_vInfoLayout->setMargin(5);
    m_vInfoLayout->setSpacing(5);
    m_vInfoLayout->addWidget(m_songNameLab);
    m_vInfoLayout->addWidget(m_singleLab);

//歌曲控制
    m_palyFrame = new QFrame;
    m_palyFrame->setVisible(false);

    m_hPlayLayout = new QHBoxLayout(m_palyFrame);

    m_lastBtn = new QPushButton;
    m_lastBtn->setFixedSize(26,26);
    m_lastBtn->setCursor(Qt::PointingHandCursor);
    m_lastBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/last.png)}");

    m_playStateBtn = new QPushButton;
    m_playStateBtn->setFixedSize(30,30);
    m_playStateBtn->setCursor(Qt::PointingHandCursor);
    m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/play.png)}");

    m_nextBtn = new QPushButton;
    m_nextBtn->setFixedSize(26,26);
    m_nextBtn->setCursor(Qt::PointingHandCursor);
    m_nextBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/next.png)}");

    m_hPlayLayout->setMargin(0);
    m_hPlayLayout->setSpacing(15);
    m_hPlayLayout->addWidget(m_lastBtn);
    m_hPlayLayout->addWidget(m_playStateBtn);
    m_hPlayLayout->addWidget(m_nextBtn);

//喜欢收藏
    m_loveBtn = new QPushButton;
    m_loveBtn->setFixedSize(15,13);
    m_loveBtn->setCursor(Qt::PointingHandCursor);
    m_loveBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/mini/love.png)}");

//音量
    m_volBtn = new QPushButton;
    m_volBtn->setFixedSize(15,13);
    m_volBtn->setCursor(Qt::PointingHandCursor);
    m_volBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/mini/vol.png)}");

//列表
    m_listBtn = new QPushButton;
    m_listBtn->setFixedSize(13,11);
    m_listBtn->setCursor(Qt::PointingHandCursor);
    m_listBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/mini/list.png)}");

//关闭和还原
    m_vLayout = new QVBoxLayout;

    m_closeBtn = new QPushButton;
    m_closeBtn->setFixedSize(8,7);
    m_closeBtn->setCursor(Qt::PointingHandCursor);
    m_closeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/mini/close.png)}");
    connect(m_closeBtn,SIGNAL(clicked(bool)),this,SLOT(hide()));

    m_recoveryWinBtn = new QPushButton;
    m_recoveryWinBtn->setFixedSize(8,6);
    m_recoveryWinBtn->setCursor(Qt::PointingHandCursor);
    m_recoveryWinBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/mini/winMode.png)}");

    m_vLayout->setSpacing(6);
    m_vLayout->setMargin(6);
    m_vLayout->addWidget(m_closeBtn);
    m_vLayout->addWidget(m_recoveryWinBtn);
    m_vLayout->addStretch();

    m_hMainLayout->setMargin(0);
    m_hMainLayout->addWidget(m_photoBtn);
    m_hMainLayout->addLayout(m_vInfoLayout);
    m_hMainLayout->addStretch();
    m_hMainLayout->addWidget(m_palyFrame);
    m_hMainLayout->addStretch();
    m_hMainLayout->addWidget(m_loveBtn);
    m_hMainLayout->addWidget(m_volBtn);
    m_hMainLayout->addWidget(m_listBtn);
    m_hMainLayout->addLayout(m_vLayout);

//---------------------------------------
//    m_tipLab = new QLabel("1111111111111111");
//    m_tipLab->setAlignment(Qt::AlignHCenter);
//    m_tipLab->setFixedSize(230,20);
//    m_tipLab->setStyleSheet("background:transparent;");

//---------------------------------------

    m_vMainLayout->setMargin(0);
    m_vMainLayout->addWidget(m_mainFrame);
    //m_vMainLayout->addWidget(m_tipLab);
    //m_vMainLayout->addStretch();
}
