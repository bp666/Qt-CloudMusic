#include "MiddleWidgetLeftList.h"

MiddleWidgetLeftList::MiddleWidgetLeftList(QWidget *parent) : QFrame(parent)
{
    setFixedWidth(200);

    setStyleSheet("QFrame{background:rgb(246,246,248);border-color:rgb(225,225,225);border-width: 1px;border-style: solid;}");

    initTopWidget();
    initBtnLinkStack();

    //m_vMainLayout = new QVBoxLayout(this);

}

void MiddleWidgetLeftList::initTopWidget()
{
    recommendLabel = new QLabel(this);
    recommendLabel->setText("推荐");
    recommendLabel->setGeometry(0,0,200,31);
    //QFrame设置了边框，QLabel也会自动设置
    recommendLabel->setStyleSheet("QLabel{color:rgb(92,92,92);border-width: 0 1 0 1;}");

    findMusicBtn = new QPushButton(this);
    findMusicBtn->setGeometry(0,30,200,30);
    //设置可选中
    findMusicBtn->setCheckable(true);
    //设置已选中
    findMusicBtn->setChecked(true);
    findMusicBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/LeftList/findMusic.png)}\
                                 QPushButton::hover{color:rgb(0,0,0)}\
                                 QPushButton::checked{background:rgb(230,231,234)}");

    privateFMBtn = new QPushButton(this);
    privateFMBtn->setGeometry(0,60,200,30);
    privateFMBtn->setCheckable(true);
    privateFMBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/LeftList/fm.png)}\
                                 QPushButton::hover{color:rgb(0,0,0)}\
                                 QPushButton::checked{background:rgb(230,231,234)}");

    mvBtn = new QPushButton(this);
    mvBtn->setGeometry(0,90,200,30);
    mvBtn->setCheckable(true);
    mvBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/LeftList/mv.png)}\
                          QPushButton::hover{color:rgb(0,0,0)}\
                          QPushButton::checked{background:rgb(230,231,234);}");

    friendBtn = new QPushButton(this);
    friendBtn->setGeometry(0,120,200,30);
    friendBtn->setCheckable(true);
    friendBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/LeftList/friend.png)}\
                              QPushButton::hover{color:rgb(0,0,0)}\
                              QPushButton::checked{background:rgb(230,231,234);}");


    myMusicLabel = new QLabel(this);
    myMusicLabel->setText("我的音乐");
    myMusicLabel->setGeometry(0,180,200,30);
    myMusicLabel->setStyleSheet("QLabel{color:rgb(92,92,92);border-width: 0 1 0 1;}");

    localMusicBtn = new QPushButton(this);
    localMusicBtn->setGeometry(0,210,200,30);
    localMusicBtn->setCheckable(true);
    localMusicBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/LeftList/local.png)}\
                                  QPushButton::hover{color:rgb(0,0,0)}\
                                  QPushButton::checked{background:rgb(230,231,234)}");

    downManageBtn = new QPushButton(this);
    downManageBtn->setGeometry(0,240,200,30);
    downManageBtn->setCheckable(true);
    downManageBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/LeftList/download.png)}\
                                  QPushButton::hover{color:rgb(0,0,0)}\
                                  QPushButton::checked{background:rgb(230,231,234)}");

    myMusicBoxBtn = new QPushButton(this);
    myMusicBoxBtn->setGeometry(0,270,200,30);
    myMusicBoxBtn->setCheckable(true);
    myMusicBoxBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/LeftList/yun.png)}\
                                  QPushButton::hover{color:rgb(0,0,0)}\
                                  QPushButton::checked{background:rgb(230,231,234)}");

    mySingerBtn = new QPushButton(this);
    mySingerBtn->setGeometry(0,300,200,30);
    mySingerBtn->setCheckable(true);
    mySingerBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/LeftList/single.png)}\
                                QPushButton::hover{color:rgb(0,0,0)}\
                                QPushButton::checked{background:rgb(230,231,234)}");


    mutexBtnGroup = new QButtonGroup(this);
    //设置按钮互斥
    mutexBtnGroup->setExclusive(true);
    mutexBtnGroup->addButton(findMusicBtn);
    mutexBtnGroup->addButton(privateFMBtn);
    mutexBtnGroup->addButton(mvBtn);
    mutexBtnGroup->addButton(friendBtn);
    mutexBtnGroup->addButton(localMusicBtn);
    mutexBtnGroup->addButton(downManageBtn);
    mutexBtnGroup->addButton(myMusicBoxBtn);
    mutexBtnGroup->addButton(mySingerBtn);
}

//方法一：QSignalMapper
//多个button实现不同的参数
void MiddleWidgetLeftList::initBtnLinkStack()
{
    signalMapper = new QSignalMapper(this);
    connect(findMusicBtn,SIGNAL(clicked()),signalMapper,SLOT(map()));
    signalMapper->setMapping(findMusicBtn,0);

    connect(privateFMBtn,SIGNAL(clicked()),signalMapper,SLOT(map()));
    signalMapper->setMapping(privateFMBtn,1);

    connect(mvBtn,SIGNAL(clicked()),signalMapper,SLOT(map()));
    signalMapper->setMapping(mvBtn,2);

    connect(friendBtn,SIGNAL(clicked()),signalMapper,SLOT(map()));
    signalMapper->setMapping(friendBtn,3);

    connect(localMusicBtn,SIGNAL(clicked()),signalMapper,SLOT(map()));
    signalMapper->setMapping(localMusicBtn,4);

    connect(downManageBtn,SIGNAL(clicked()),signalMapper,SLOT(map()));
    signalMapper->setMapping(downManageBtn,5);

    connect(myMusicBoxBtn,SIGNAL(clicked()),signalMapper,SLOT(map()));
    signalMapper->setMapping(myMusicBoxBtn,6);

    connect(mySingerBtn,SIGNAL(clicked()),signalMapper,SLOT(map()));
    signalMapper->setMapping(mySingerBtn,7);
}
