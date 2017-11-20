#ifndef MIDDLEWIDGETRIGHTSTACK_H
#define MIDDLEWIDGETRIGHTSTACK_H

#include <QStackedWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QScrollBar>
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMovie>
#include <QThread>
#include <QFile>
#include <QCryptographicHash>

//TagLib
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/toolkit/tpropertymap.h>

#include "BaseStackChildWidget.h"
#include "DataBase.h"
#include "AnimationWidget.h"

class ThreadOfRight : public QThread
{
    Q_OBJECT
public:
    ThreadOfRight() {}
    ~ThreadOfRight() {
        if(this->isRunning())
        {
            this->terminate();
            this->wait();
        }
    }

    void run();
};

class MiddleWidgetRightStack : public QStackedWidget
{
    Q_OBJECT
public:
    explicit MiddleWidgetRightStack(QWidget *parent = 0);
    ~MiddleWidgetRightStack();

public slots:
    void slot_widget1BtnClick();
    void slot_widget4BtnClick();
    void slot_widget4MatchSong();
    void slot_setWidget4TableItem();

private:
    void initStack();

    void initFindMusicStack0();

//    void initFMStack1();
//    void initMVStack2();
//    void initFriendStack3();

    void initLocalMusicStack4();
    void setTableItem(int& rownum, QString title, QString singal, QString cd, QString time, QString size);

//    void initDownloadStack5();
//    void inityunStack6();
//    void initsingleStack7();

    //初始化搜索窗口
    void initSongSearchStack();

public:
//initFindMusicStack0()
    BaseStackChildWidget *stackChildWidget0;
    QStackedWidget *findMusicStack;
    QButtonGroup *mutexBtnGroup0;
    QVector<QPushButton*> m_btn0;
    QPushButton *recommendBtn, *songListBtn, *radioBtn, *rankBtn, *singleBtn, *newMusicBtn;
    QHBoxLayout *h_btnBarLayout;
    QVBoxLayout *v_btnBarLayout;

//发现音乐个性推荐
    QFrame *m_FMOneFrame;
    QVBoxLayout *m_vFMOneLo;
    AnimationWidget *m_animationFrame;

//initLocalMusicStack4()
    QFrame *stackChildWidget4, *titleFrame, *stackFrame4, *stackTitleFrame;
    QButtonGroup *mutexBtnGroup4;
    QVector<QPushButton*> m_btn4;
    QHBoxLayout *hTitleLayout, *hStackTitleLayout;
    QVBoxLayout *vMainLayout4, *hStack4Layout;
    QStackedWidget *localMusicStack;
    QLabel *m_localLabel, *m_CountLabel;
    QPushButton *m_selectBtn, *m_listBtn, *m_singalBtn, *m_cdBtn, *m_dirBtn;
    QPushButton *m_playAllBtn, *m_addBtn, *m_matchMusicBtn;
    QLineEdit *m_searchEdit;
    QLabel *m_searchLabel;
    QTableWidget *m_Stack4TableWidget;
    int rowcount;

    QStringList SongDirPath;
    QDir matchDir;
    QStringList matchMp3Files;
    QString mp3Name;
    QFileInfo fileInfo;
    QByteArray bytes;
    QString titleStr;
    QString artistStr;
    QString albumStr;
    QString timeStr;
    QString mp3Size;
    QString MD5Str;
    QStringList MD5List;

//媒体列表
    QMediaPlaylist *localPlayList;
//数据库
    DataBase db;
//多线程匹配数据库歌曲信息
    ThreadOfRight *thread;

//initSongSearchStack()
    QWidget *SearchWidget8;
    QFrame *pageFrame, *pageBtnFrame;
    QPushButton *m_leftBtn, *m_rightBtn;
    QLabel *m_SearchLabel, *m_progressLabel;
    QMovie *m_progressMovie;
    QHBoxLayout *m_hProgressLayout, *m_hPageLayout;
    QTableWidget *m_SearchWidget;
    QVBoxLayout *m_vSearchLayout;
};

#endif // MIDDLEWIDGETRIGHTSTACK_H
