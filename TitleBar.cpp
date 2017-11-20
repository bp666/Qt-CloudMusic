#include "TitleBar.h"
#include <QMenu>

TitleBar::TitleBar(QWidget *parent) : QFrame(parent)
{

    setStyleSheet("QFrame{Background:rgb(102,183,255)}");

    setMouseTracking(true);

    initTitle();

}

void TitleBar::initTitle()
{
    setMinimumSize(1000,50);
    setMaximumSize(1920,50);
    //setSizePolicy(QSizePolicy::Expanding);

    titleLayout = new QHBoxLayout(this);

    titleIconLabel = new QLabel;
    titleIconLabel->setFixedWidth(114);
    titleIconLabel->setCursor(Qt::PointingHandCursor);
    titleIconLabel->setPixmap(QPixmap(":/images/TitleBar/titleIcon.png"));

//////////////////////////////////////////////////////////////////////

    Layout1 = new QHBoxLayout;

    leftBtn = new QPushButton;
    leftBtn->setFixedSize(27,22);
    leftBtn->setToolTip("后退");
    leftBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/TitleBar/leftArrow.png)}");

    rightBtn = new QPushButton;
    rightBtn->setFixedSize(27,22);
    rightBtn->setToolTip("前进");
    rightBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/TitleBar/rightArrow.png)}");

    searchEdit = new QLineEdit;
    searchEdit->setFixedSize(220,20);
    //searchEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    searchEdit->setPlaceholderText("搜索音乐，歌手，歌词，用户");
    searchEdit->setStyleSheet("QLineEdit{border-radius:10px;background:rgb(73,140,213);color:rgb(238,211,211)}");

    searchBtn = new QPushButton(searchEdit);
    searchBtn->setFixedSize(13,12);
    searchBtn->setCursor(Qt::PointingHandCursor);
    searchBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/TitleBar/search.png)}\
                              QPushButton::hover{border-image:url(:/images/TitleBar/search_hover.png)}");

    //设置searchEdit的可编辑边缘，
    QMargins margins = searchEdit->textMargins();
    searchEdit->setTextMargins(margins.left()+10, margins.top(), searchBtn->width()+15, margins.bottom());

    //searchBtn附在searchEdit上，Layout的主窗口是searchEdit
    searchLayout = new QHBoxLayout(searchEdit);
    searchLayout->addStretch();
    searchLayout->addWidget(searchBtn);
    searchLayout->setSpacing(0);
    //设置searchBtn在searchEdit右边的边缘
    searchLayout->setContentsMargins(0,0,10,0);

    Layout1->addWidget(leftBtn);
    Layout1->addWidget(rightBtn);
    Layout1->addSpacing(10);
    Layout1->addWidget(searchEdit);
    Layout1->setSpacing(0);

//////////////////////////////////////////////////////////////////////

    Layout2 = new QHBoxLayout;

    userIconBtn = new QPushButton;
    userIconBtn->setCursor(Qt::PointingHandCursor);
    userIconBtn->setFixedSize(40,32);
    userIconBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/TitleBar/userIcon.png)}");

    loginBtn = new QPushButton;
    loginBtn->setText("未登录");
    //自适应大小
    loginBtn->adjustSize();
    loginBtn->setFixedWidth(loginBtn->width());
    loginBtn->setCursor(Qt::PointingHandCursor);
    loginBtn->setStyleSheet("QPushButton{background:transparent;color:rgb(238,238,238)}\
                             QPushButton::hover{color:rgb(255,255,255)}\
                             QPushButton::menu-indicator{subcontrol-position: right center;}");

    QMenu *loginMenu = new QMenu;
    loginBtn->setMenu(loginMenu);

    skinBtn = new QPushButton;
    skinBtn->setCursor(Qt::PointingHandCursor);
    skinBtn->setFixedSize(16,14);
    skinBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/TitleBar/skin.png)}\
                            QPushButton::hover{border-image:url(:/images/TitleBar/skin_hover.png)}");

    mailBtn = new QPushButton;
    mailBtn->setCursor(Qt::PointingHandCursor);
    mailBtn->setFixedSize(16,12);
    mailBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/TitleBar/mail.png)}\
                            QPushButton::hover{border-image:url(:/images/TitleBar/mail_hover.png)}");

    setBtn = new QPushButton;
    setBtn->setCursor(Qt::PointingHandCursor);
    setBtn->setFixedSize(15,16);
    setBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/TitleBar/set.png)}\
                           QPushButton::hover{border-image:url(:/images/TitleBar/set_hover.png)}");

    nullLabel = new QLabel;
    nullLabel->setPixmap(QPixmap(":/images/TitleBar/line.png"));

    miniBtn = new QPushButton;
    miniBtn->setCursor(Qt::PointingHandCursor);
    miniBtn->setFixedSize(13,11);
    miniBtn->setToolTip("mini模式 ( Ctrl + M ) ");
    miniBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/TitleBar/mini.png)}\
                            QPushButton::hover{border-image:url(:/images/TitleBar/mini_hover.png)}");

    minimumBtn = new QPushButton;
    minimumBtn->setCursor(Qt::PointingHandCursor);
    minimumBtn->setToolTip("最小化");
    minimumBtn->setFixedSize(14,18);
    minimumBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/TitleBar/minimum.png)}\
                               QPushButton::hover{border-image:url(:/images/TitleBar/minimum_hover.png)}");

    maximumBtn = new QPushButton;
    maximumBtn->setCursor(Qt::PointingHandCursor);
    maximumBtn->setFixedSize(14,11);
    maximumBtn->setToolTip("最大化");
    maximumBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/TitleBar/maximum.png)}\
                               QPushButton::hover{border-image:url(:/images/TitleBar/maximum_hover.png)}");

    closeBtn = new QPushButton;
    closeBtn->setCursor(Qt::PointingHandCursor);
    closeBtn->setFixedSize(12,11);
    closeBtn->setToolTip("关闭");
    closeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/TitleBar/close.png)}\
                             QPushButton::hover{border-image:url(:/images/TitleBar/close_hover.png)}");

    Layout2->setSpacing(0);
    Layout2->addWidget(userIconBtn);
    Layout2->addWidget(loginBtn);
    Layout2->addSpacing(20);
    Layout2->addWidget(skinBtn);
    Layout2->addSpacing(20);
    Layout2->addWidget(mailBtn);
    Layout2->addSpacing(20);
    Layout2->addWidget(setBtn);
    Layout2->addSpacing(15);
    Layout2->addWidget(nullLabel);
    Layout2->addSpacing(15);
    Layout2->addWidget(miniBtn);
    Layout2->addSpacing(10);
    Layout2->addWidget(minimumBtn);
    Layout2->addSpacing(10);
    Layout2->addWidget(maximumBtn);
    Layout2->addSpacing(10);
    Layout2->addWidget(closeBtn);

    titleLayout->addWidget(titleIconLabel);
    titleLayout->addSpacing(60);
    titleLayout->addLayout(Layout1);
    titleLayout->addStretch();
    titleLayout->addLayout(Layout2);
}
