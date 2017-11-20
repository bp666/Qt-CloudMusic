#include "MainWidget.h"
#include <QtMath>
#include <QDebug>
#include <QListWidgetItem>
#include <QTime>

#include "PlayListItemStyle.h"

MainWidget::MainWidget(QWidget *parent)
    : FramelessAndAutoSize(parent)
{
    setMinimumSize(1000,680);

   // setAttribute(Qt::WA_TranslucentBackground);

    //设置任务栏图标
    setWindowIcon(QIcon(":/images/logoIcon.png"));

    //注册这个类型，就可以在信号槽用了
    qRegisterMetaType<QVector<QStringList>>("QVector<QStringList>");

    isMaximun = false;

    playModeCount =0;

    player = new QMediaPlayer;

    //初始化多线程
    m_threadObject = new ThreadFromObject;
    connect(this,SIGNAL(sig_searchName(QString)),m_threadObject,SLOT(slot_searchNetSong(QString)));
    connect(m_threadObject,SIGNAL(sig_searchResult(QVector<QStringList>)),this,SLOT(slot_SetNetSongItem(QVector<QStringList>)));

    mainLayout = new QVBoxLayout(this);

    m_TitleBar = new TitleBar;
    connect(m_TitleBar->miniBtn,SIGNAL(clicked(bool)),this,SLOT(slot_showMiniWidget()));
    connect(m_TitleBar->minimumBtn,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(m_TitleBar->maximumBtn,SIGNAL(clicked(bool)),this,SLOT(slot_showMaximized()));
    connect(m_TitleBar->closeBtn, SIGNAL(clicked(bool)),this,SLOT(hide()));
    //搜索框回车点击搜索按钮
    connect(m_TitleBar->searchEdit,SIGNAL(returnPressed()),m_TitleBar->searchBtn,SLOT(click()));
    //点击搜索按钮实现搜索
    connect(m_TitleBar->searchBtn,SIGNAL(clicked(bool)),this,SLOT(slot_SearchWidget()));

    m_MiddleWidget = new MiddleWidget;
    connect(m_MiddleWidget->m_Stack->m_Stack4TableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(slot_PlayMusic(QTableWidgetItem*)));
    m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Sequential);

    m_BottomWidget = new BottomWidget;
    connect(m_BottomWidget->listBtn, SIGNAL(clicked(bool)),this,SLOT(slot_showSongListWidget()));
    connect(m_BottomWidget->playBtn,SIGNAL(clicked(bool)),this,SLOT(slot_PlayPause()));
    connect(m_BottomWidget->playModeBtn,SIGNAL(clicked(bool)),this,SLOT(slot_setPlayMode()));
    connect(m_BottomWidget->playTimeSlider,SIGNAL(valueChanged(int)),this,SLOT(slot_setPosition(int)));
    connect(m_BottomWidget->volumeSlider,SIGNAL(valueChanged(int)),player,SLOT(setVolume(int)));
    connect(m_BottomWidget->volumeBtn,SIGNAL(clicked(bool)),this,SLOT(slot_silence()));
    connect(m_BottomWidget->nextBtn,SIGNAL(clicked(bool)),this,SLOT(slot_playNext()));
    connect(m_BottomWidget->lastBtn,SIGNAL(clicked(bool)),this,SLOT(slot_playLast()));

    m_SongListFrame = new SongListFrame(this);
    m_SongListFrameX = this->width()-m_SongListFrame->width();
    m_SongListFrameY = this->height()-m_SongListFrame->height()-m_BottomWidget->height();
    m_SongListFrame->hide();
    connect(this, SIGNAL(sig_PosChange(int,int)),this,SLOT(slot_changeSongListPos(int,int)));

    mainLayout->addWidget(m_TitleBar);
    mainLayout->addWidget(m_MiddleWidget);
    mainLayout->addWidget(m_BottomWidget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    m_miniWidget = new miniWidget;
    connect(m_miniWidget->m_recoveryWinBtn,SIGNAL(clicked(bool)),this,SLOT(slot_showMainWidget()));
    connect(m_miniWidget->m_lastBtn,SIGNAL(clicked(bool)),this,SLOT(slot_playLast()));
    connect(m_miniWidget->m_playStateBtn,SIGNAL(clicked(bool)),this,SLOT(slot_PlayPause()));
    connect(m_miniWidget->m_nextBtn,SIGNAL(clicked(bool)),this,SLOT(slot_playNext()));

    //歌曲改变
    //connect(player, SIGNAL()),
    //发送歌曲播放时间跳跃位置
    connect(player, SIGNAL(positionChanged(qint64)),this,SLOT(slot_updatePosition(qint64)));
    //发送歌曲时长
    connect(player, SIGNAL(durationChanged(qint64)),this,SLOT(slot_updateDuration(qint64)));
    //发送音量改变
    connect(player, SIGNAL(volumeChanged(int)),m_BottomWidget->volumeSlider,SLOT(setValue(int)));
    //发送歌曲改变信息
    connect(player, SIGNAL(currentMediaChanged(QMediaContent)),this,SLOT(slot_updateSongInfo(QMediaContent)));

    player->setVolume(50);
    searchCurMediaList = new QMediaPlaylist;

//初始化系统托盘
    initSystemTray();
}

MainWidget::~MainWidget()
{
    m_threadObject->~ThreadFromObject();
    m_miniWidget->~QFrame();
    player->~QMediaPlayer();
    searchCurMediaList->~QMediaPlaylist();
}

//移动窗口
void MainWidget::mousePressEvent(QMouseEvent *event)
{
    //在标题栏和右下角才能改变窗口
    if(QRect(0,0,m_TitleBar->width(),m_TitleBar->height()).contains(event->pos()) ||\
       QRect(width()-13,height()-13,15,15).contains(event->pos()))
    {
        FramelessAndAutoSize::mousePressEvent(event);
    }
}

//关闭mini模式恢复正常窗口
void MainWidget::slot_showMainWidget()
{
    m_miniWidget->hide();
    this->show();
}

//最小化
void MainWidget::slot_showMiniWidget()
{
    this->hide();
    m_miniWidget->show();
}

//最大化与恢复、隐藏右下方播放列表
void MainWidget::slot_showMaximized()
{
    if(isMaximun)
    {
        if(m_SongListFrame->isVisible())
            m_SongListFrame->hide();

        isMaximun = false;
        showNormal();
    }
    else
    {
        if(m_SongListFrame->isVisible())
            m_SongListFrame->hide();

        isMaximun = true;
        showMaximized();
    }
}

//系统托盘
void MainWidget::initSystemTray()
{
    m_SystemTray = new QSystemTrayIcon(this);
    m_TrayMenu = new TrayIconMenu(this);
    //m_TrayMenu->setStyleSheet("QMenu::item{padding:5;margin:5;}");

    //设置系统托盘的上下文菜单
    m_SystemTray->setContextMenu(m_TrayMenu);
    m_SystemTray->setToolTip(" 未知 - 未知 ");
    m_SystemTray->setIcon(QIcon(":/images/TrayIcon/logoTrayIcon.png"));

    // 显示系统托盘
    m_SystemTray->show();

    connect(m_SystemTray ,SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slot_onActivated(QSystemTrayIcon::ActivationReason)));

    connect(m_TrayMenu->pauseAction,SIGNAL(triggered(bool)),this,SLOT(slot_PlayPause()));
    connect(m_TrayMenu->lastAction,SIGNAL(triggered(bool)),this,SLOT(slot_playLast()));
    connect(m_TrayMenu->nextAction,SIGNAL(triggered(bool)),this,SLOT(slot_playNext()));
    connect(m_TrayMenu->playModeAction,SIGNAL(triggered(bool)),this,SLOT(slot_setPlayMode()));
    connect(m_TrayMenu->miniAction,SIGNAL(triggered(bool)),this,SLOT(slot_showMiniWidget()));
    connect(m_TrayMenu->quitAction,SIGNAL(triggered(bool)),this,SLOT(close()));
}

//mini模式
void MainWidget::slot_onActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
        {
        // 单击托盘显示窗口
        case QSystemTrayIcon::Trigger:
        {
            showNormal();
            raise();
            activateWindow();
            break;
        }
        // 双击
        case QSystemTrayIcon::DoubleClick:
        {
            // ...
            break;
        }
            default:
                break;
    }
}

//显示/隐藏播放列表
void MainWidget::slot_showSongListWidget()
{
    if(m_SongListFrame->isVisible())
        m_SongListFrame->hide();
    else
    {
        //m_SongListFrame->setGeometry(m_SongListFrameX, m_SongListFrameY,580,470);
        m_SongListFrame->setGeometry(width()-m_SongListFrame->width(),height()-m_SongListFrame->height()-m_BottomWidget->height(),580,470);
        m_SongListFrame->show();
        m_SongListFrame->raise();
    }
}

//播放列表始终在右下方
void MainWidget::slot_changeSongListPos(int newWidth, int newHeight)
{
    m_SongListFrameX = newWidth-m_SongListFrame->width();
    m_SongListFrameY = newHeight-m_SongListFrame->height()-m_BottomWidget->height();
    if(m_SongListFrameX<=420)
        m_SongListFrameX=420;

    if(m_SongListFrameY<=160)
        m_SongListFrameY=160;

    m_SongListFrame->move(m_SongListFrameX, m_SongListFrameY);
}

void MainWidget::slot_PlayMusic(QTableWidgetItem* tableItem)
{
    for(int i=0;i<m_MiddleWidget->m_Stack->m_Stack4TableWidget->rowCount();i++)
    {
        QListWidgetItem *item = new QListWidgetItem;
        m_SongListFrame->m_PlayingList->addItem(item);
        PlayListItemStyle *itemStyle = new PlayListItemStyle(m_MiddleWidget->m_Stack->m_Stack4TableWidget->item(i,1)->text(),
                                                             m_MiddleWidget->m_Stack->m_Stack4TableWidget->item(i,2)->text(),
                                                             m_MiddleWidget->m_Stack->m_Stack4TableWidget->item(i,4)->text());
        m_SongListFrame->m_PlayingList->setItemWidget(item,itemStyle);
        item->setSizeHint(QSize(itemStyle->rect().width(),itemStyle->rect().height()));
    }
    m_SongListFrame->getCountLabel()->setText(QString("总%1首").arg(m_MiddleWidget->m_Stack->m_Stack4TableWidget->rowCount()));

    //修改当前播放歌名
    curPlaySong = m_MiddleWidget->m_Stack->m_Stack4TableWidget->item(tableItem->row(),1)->text();
    curPlaySingal = m_MiddleWidget->m_Stack->m_Stack4TableWidget->item(tableItem->row(),2)->text();

    //歌曲信息栏修改当前播放歌名
    m_MiddleWidget->m_PlaySongInfoWidget->setSongText(curPlaySong,curPlaySingal);

    //mini窗口修改当前播放歌名
    m_miniWidget->m_songNameLab->setText(curPlaySong);
    m_miniWidget->m_singleLab->setText(curPlaySingal);

    //系统托盘修改当前播放歌名
    m_TrayMenu->curPlaySongAction->setText(curPlaySong+" - "+curPlaySingal);
    m_SystemTray->setToolTip(curPlaySong+" - "+curPlaySingal);

    //系统托盘修改播放暂停状态
    m_TrayMenu->pauseAction->setText("暂停");
    m_TrayMenu->pauseAction->setIcon(QIcon(":/images/TrayIcon/pause.png"));

    //mini窗口修改播放暂停状态
    m_miniWidget->m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/pause.png)}");

    player->setPlaylist(m_MiddleWidget->m_Stack->localPlayList);
    m_MiddleWidget->m_Stack->localPlayList->setCurrentIndex(tableItem->row());
    player->play();
    m_BottomWidget->playBtn->setToolTip(" 暂停 ( Ctrl + P ) ");
    m_BottomWidget->playBtn->setStyleSheet("QPushButton{background:rgb(102,183,255);border-image:url(:/images/BottomPlay/pause.png);border-radius:17px}");
    m_BottomWidget->endTimeLabel->setText(m_MiddleWidget->m_Stack->m_Stack4TableWidget->item(tableItem->row(),4)->text());
}

void MainWidget::slot_PlayOnlineMusic(QTableWidgetItem *tableItem)
{
    //修改当前播放歌名
    curPlaySong = m_MiddleWidget->m_Stack->m_SearchWidget->item(tableItem->row(),2)->text();
    curPlaySingal = m_MiddleWidget->m_Stack->m_SearchWidget->item(tableItem->row(),3)->text();

    //歌曲信息栏修改当前播放歌名
    m_MiddleWidget->m_PlaySongInfoWidget->setSongText(curPlaySong,curPlaySingal);

    //mini窗口修改当前播放歌名
    m_miniWidget->m_songNameLab->setText(curPlaySong);
    m_miniWidget->m_singleLab->setText(curPlaySingal);

    //系统托盘修改当前播放歌名
    m_TrayMenu->curPlaySongAction->setText(curPlaySong+" - "+curPlaySingal);
    m_SystemTray->setToolTip(curPlaySong+" - "+curPlaySingal);

    player->setPlaylist(searchCurMediaList);
    searchCurMediaList->setCurrentIndex(tableItem->row());
    player->play();
    m_BottomWidget->playBtn->setToolTip(" 暂停 ( Ctrl + P ) ");
    m_BottomWidget->playBtn->setStyleSheet("QPushButton{background:rgb(102,183,255);border-image:url(:/images/BottomPlay/pause.png);border-radius:17px}");
    m_BottomWidget->endTimeLabel->setText(m_MiddleWidget->m_Stack->m_SearchWidget->item(tableItem->row(),4)->text());
}

void MainWidget::slot_PlayPause()
{
    if(player->state() == QMediaPlayer::PausedState)
    {
        player->play();
        m_BottomWidget->playBtn->setToolTip(" 暂停 ( Ctrl + P ) ");
        m_BottomWidget-> playBtn->setStyleSheet("QPushButton{background:rgb(102,183,255);border-image:url(:/images/BottomPlay/pause.png);border-radius:17px}");

        m_TrayMenu->pauseAction->setText("暂停");
        m_TrayMenu->pauseAction->setIcon(QIcon(":/images/TrayIcon/pause.png"));

        m_miniWidget->m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/pause.png)}");
    }
    else
    {
       player->pause();
       m_BottomWidget->playBtn->setToolTip(" 播放 ( Ctrl + P ) ");
       m_BottomWidget-> playBtn->setStyleSheet("QPushButton{background:rgb(102,183,255);border-image:url(:/images/BottomPlay/play.png);border-radius:17px}");

       m_TrayMenu->pauseAction->setText("播放");
       m_TrayMenu->pauseAction->setIcon(QIcon(":/images/TrayIcon/play.png"));

       m_miniWidget->m_playStateBtn->setStyleSheet("QPushButton{border-image:url(:/images/BottomPlay/play.png)}");
    }
}

//设置播放模式
void MainWidget::slot_setPlayMode()
{
    playModeCount++;
    switch (playModeCount) {
    case 0:
        m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Sequential);
        m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Sequential.png)}");
        m_TrayMenu->playModeAction->setIcon(QIcon(":/images/BottomPlay/Sequential.png"));
        break;
    case 1:
        m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Loop);
        m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Loop.png)}");
        m_TrayMenu->playModeAction->setIcon(QIcon(":/images/BottomPlay/Loop.png"));
        break;
    case 2:
        m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/CurrentItemInLoop.png)}");
        m_TrayMenu->playModeAction->setIcon(QIcon(":/images/BottomPlay/CurrentItemInLoop.png"));
        break;
    case 3:
        m_MiddleWidget->m_Stack->localPlayList->setPlaybackMode(QMediaPlaylist::Random);
        m_BottomWidget->playModeBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/BottomPlay/Random.png)}");
        m_TrayMenu->playModeAction->setIcon(QIcon(":/images/BottomPlay/Random.png"));
        playModeCount=-1;   //如果是0，进来自增就变成1了
        break;
    default:
        break;
    }
}

void MainWidget::slot_setPosition(int position)
{
    if (qAbs(player->position() - position) > 99)
        player->setPosition(position);
}

void MainWidget::slot_updatePosition(qint64 position)
{
    m_BottomWidget->playTimeSlider->setValue(position);
    QTime duration(0, position / 60000, (position % 60000) / 1000.0);
    m_BottomWidget->startTimeLabel->setText(duration.toString("mm:ss"));
}

void MainWidget::slot_updateDuration(qint64 duration)
{
    m_BottomWidget->playTimeSlider->setRange(0,duration);
    m_BottomWidget->playTimeSlider->setEnabled(duration>0);
    m_BottomWidget->playTimeSlider->setPageStep(duration/10);
}

void MainWidget::slot_updateSongInfo(QMediaContent c)
{
    Q_UNUSED(c);

    int currentIndex = m_MiddleWidget->m_Stack->localPlayList->currentIndex();

    //修改当前播放歌名
    QString curPlaySong = m_MiddleWidget->m_Stack->m_Stack4TableWidget->item(currentIndex,1)->text();
    QString curPlaySingal = m_MiddleWidget->m_Stack->m_Stack4TableWidget->item(currentIndex,2)->text();

    //歌曲信息栏修改当前播放歌名
    m_MiddleWidget->m_PlaySongInfoWidget->setSongText(curPlaySong,curPlaySingal);

    //mini窗口修改当前播放歌名
    m_miniWidget->m_songNameLab->setText(curPlaySong);
    m_miniWidget->m_singleLab->setText(curPlaySingal);

    //系统托盘修改当前播放歌名
    m_TrayMenu->curPlaySongAction->setText(curPlaySong+" - "+curPlaySingal);
    m_SystemTray->setToolTip(curPlaySong+" - "+curPlaySingal);
}

void MainWidget::slot_SearchWidget()
{
    QString searchStr = m_TitleBar->searchEdit->text();
    m_MiddleWidget->m_Stack->setCurrentIndex(8);
    if(searchStr.isEmpty())
        return;
    m_MiddleWidget->m_Stack->m_SearchLabel->setText(QString("    搜索\"%1\"").arg(searchStr));

    if(m_MiddleWidget->m_Stack->m_SearchWidget->isVisible())
        m_MiddleWidget->m_Stack->m_SearchWidget->hide();

    //加载中图片
    if(!m_MiddleWidget->m_Stack->m_progressLabel->isVisible())
    {
        m_MiddleWidget->m_Stack->m_progressLabel->show();
        m_MiddleWidget->m_Stack->m_progressMovie->start();
    }

    //清空上一次的在线歌曲媒体列表
    searchCurMediaList->clear();
    //清空上一次的歌曲列表项
    if(m_MiddleWidget->m_Stack->m_SearchWidget->rowCount()!=0)
    {
        m_MiddleWidget->m_Stack->m_SearchWidget->clearContents();
        m_MiddleWidget->m_Stack->m_SearchWidget->setRowCount(0);
    }
    //发送要搜索的字符
    emit sig_searchName(searchStr);
}

void MainWidget::slot_SetNetSongItem(QVector<QStringList> SongInfos)
{
    int itemRow=0;

    for(int i=0; i<SongInfos.count(); i++)
    {
        searchCurMediaList->addMedia(QMediaContent(QUrl(SongInfos[i][3])));

        //搜索窗口里的操作按钮
        QFrame *actionFrame = new QFrame;
        QPushButton *loveBtn = new QPushButton;
        loveBtn->setFixedSize(14,12);
        loveBtn->setCursor(Qt::PointingHandCursor);
        loveBtn->setStyleSheet("QPushButton{border-image:url(:/images/SearchStack/love.png)}"
                               "QPushButton:hover{background:transparent;border-image:url(:/images/SearchStack/love_hover.png)}");
        QPushButton *downBtn = new QPushButton;
        downBtn->setFixedSize(13,12);
        downBtn->setCursor(Qt::PointingHandCursor);
        downBtn->setStyleSheet("QPushButton{border-image:url(:/images/SearchStack/download.png)}"
                               "QPushButton:hover{background:transparent;border-image:url(:/images/SearchStack/download_hover.png)}");
        QHBoxLayout *seekLayout = new QHBoxLayout(actionFrame);
        seekLayout->addWidget(loveBtn);
        seekLayout->addWidget(downBtn);

        itemRow = m_MiddleWidget->m_Stack->m_SearchWidget->rowCount();
        m_MiddleWidget->m_Stack->m_SearchWidget->insertRow(itemRow);
        QString num=QString("%1").arg(itemRow+1, 2, 10, QChar('0'));

        QTableWidgetItem *itemNum = new QTableWidgetItem(num);
        QTableWidgetItem *Singeritem = new QTableWidgetItem(SongInfos[i][0]);
        QTableWidgetItem *SongNameitem = new QTableWidgetItem(SongInfos[i][1]);
        QTableWidgetItem *SongLenitem = new QTableWidgetItem(SongInfos[i][2]);

        m_MiddleWidget->m_Stack->m_SearchWidget->setItem(itemRow,0,itemNum);
        m_MiddleWidget->m_Stack->m_SearchWidget->item(itemRow,0)->setTextAlignment(Qt::AlignCenter|Qt::AlignRight);
        m_MiddleWidget->m_Stack->m_SearchWidget->setCellWidget(itemRow,1,actionFrame);
        m_MiddleWidget->m_Stack->m_SearchWidget->setItem(itemRow,2,SongNameitem);
        m_MiddleWidget->m_Stack->m_SearchWidget->item(itemRow,2)->setTextColor(QColor(0,0,0));
        m_MiddleWidget->m_Stack->m_SearchWidget->setItem(itemRow,3,Singeritem);
        m_MiddleWidget->m_Stack->m_SearchWidget->setItem(itemRow,4,SongLenitem);
    }

    //m_MiddleWidget->m_Stack->m_SearchWidget->setFixedHeight((itemRow+2)*30);
    //qDebug()<<m_MiddleWidget->m_Stack->m_SearchWidget->height();

    if(!m_MiddleWidget->m_Stack->m_SearchWidget->isVisible())
        m_MiddleWidget->m_Stack->m_SearchWidget->show();

    //加载完成取消图片
    if(m_MiddleWidget->m_Stack->m_progressLabel->isVisible())
    {
        m_MiddleWidget->m_Stack->m_progressLabel->hide();
        m_MiddleWidget->m_Stack->m_progressMovie->stop();
    }

    connect(m_MiddleWidget->m_Stack->m_SearchWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(slot_PlayOnlineMusic(QTableWidgetItem*)));
}

void MainWidget::slot_silence()
{
    if(0 == player->volume())
        player->setVolume(curVolume);
    else
    {
        curVolume = player->volume();
        player->setVolume(0);
    }
}

void MainWidget::slot_playNext()
{
    int currentIndex = m_MiddleWidget->m_Stack->localPlayList->currentIndex();
    if(++currentIndex == m_MiddleWidget->m_Stack->localPlayList->mediaCount())
        currentIndex = 0;
    m_MiddleWidget->m_Stack->localPlayList->setCurrentIndex(currentIndex);
    player->play();
}

void MainWidget::slot_playLast()
{
    int currentIndex = m_MiddleWidget->m_Stack->localPlayList->currentIndex();
    if(currentIndex == 0)
        currentIndex = m_MiddleWidget->m_Stack->localPlayList->mediaCount();
    else
        --currentIndex;
    m_MiddleWidget->m_Stack->localPlayList->setCurrentIndex(currentIndex);
    player->play();
}
