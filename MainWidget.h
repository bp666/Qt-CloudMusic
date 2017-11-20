#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QVBoxLayout>
#include <QSystemTrayIcon>
#include <QTableWidgetItem>
#include <QMediaPlaylist>

#include "FramelessAndAutoSize.h"
#include "TitleBar.h"
#include "MiddleWidget.h"
#include "BottomWidget.h"
#include "TrayIconMenu.h"
#include "miniWidget.h"
#include "SongListFrame.h"
#include "ThreadFromObject.h"

class MainWidget : public FramelessAndAutoSize
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void mousePressEvent(QMouseEvent *);

signals:
    void sig_searchName(QString);

public slots:
    void slot_showMainWidget();
    void slot_showMiniWidget();
    //最大化与向下还原
    void slot_showMaximized();
    void slot_onActivated(QSystemTrayIcon::ActivationReason);
    void slot_showSongListWidget();
    void slot_changeSongListPos(int, int);

    //双击本地音乐，实现播放和添加到播放列表
    void slot_PlayMusic(QTableWidgetItem*);
    //双击网络音乐，实现播放
    void slot_PlayOnlineMusic(QTableWidgetItem*);

    void slot_PlayPause();

    //设置播放顺序
    void slot_setPlayMode();

    //设置歌曲播放位置
    void slot_setPosition(int);
    //更新歌曲播放位置
    void slot_updatePosition(qint64);
    //更新播放位置滑动条范围
    void slot_updateDuration(qint64);
    //更新歌曲信息
    void slot_updateSongInfo(QMediaContent);

    //进入搜索窗口
    void slot_SearchWidget();
    //搜索完成，设置item
    void slot_SetNetSongItem(QVector<QStringList>);

    //静音
    void slot_silence();

    void slot_playNext();
    void slot_playLast();

private:
    TitleBar *m_TitleBar;
    MiddleWidget *m_MiddleWidget;
    BottomWidget *m_BottomWidget;
    int playModeCount;
    SongListFrame *m_SongListFrame;
    int m_SongListFrameX, m_SongListFrameY;

    QVBoxLayout *mainLayout;

    QSystemTrayIcon *m_SystemTray;
    TrayIconMenu *m_TrayMenu;
    //初始化系统托盘
    void initSystemTray();

    miniWidget *m_miniWidget;

    //是否最大化
    bool isMaximun;
    //当前音量
    int curVolume=0;

    QString curPlaySong, curPlaySingal;

    QMediaPlayer *player;

    //保存当前搜索到的的音源
    QMediaPlaylist *searchCurMediaList;

    ThreadFromObject *m_threadObject;
};

#endif // MAINWIDGET_H
