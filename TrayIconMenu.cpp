#include "TrayIconMenu.h"

TrayIconMenu::TrayIconMenu(QWidget *parent) : QMenu(parent)
{
    setFixedWidth(212);
    setStyleSheet("QMenu{background:#fafafc;}"
                  "QMenu::item{height: 28px;padding: 0px 20px 0px 40px;font-size : 12px}"
                  "QMenu::item:hover{background:#ededef}"
                  "QMenu::icon{position: absolute;left: 12px;}"
                  "QMenu::separator{height:1px;background: #ededef;margin:5px 0px 5px 0px;}");

    initAction();
}

void TrayIconMenu::initAction()
{
    // 创建菜单项
    curPlaySongAction = new QAction(QIcon(":/images/TrayIcon/curPlaySong.png"), "未知 - 未知", this);
    pauseAction = new QAction(QIcon(":/images/TrayIcon/play.png"), "开始", this);
    lastAction = new QAction(QIcon(":/images/TrayIcon/last.png"), "上一首", this);
    nextAction = new QAction(QIcon(":/images/TrayIcon/next.png"), "下一首", this);
    playModeAction = new QAction(QIcon(":/images/BottomPlay/Sequential.png"), "顺序播放", this);
    miniAction = new QAction(QIcon(":/images/TrayIcon/mini.png"), "mini模式", this);
    openLyricAction = new QAction(QIcon(":/images/TrayIcon/openLyric.png"), "打开桌面歌词", this);
    lockLyricAction = new QAction(QIcon(":/images/TrayIcon/lockLyric.png"), "锁定桌面歌词", this);
    setAction = new QAction(QIcon(":/images/TrayIcon/set.png"), "设置", this);
    quitAction = new QAction(QIcon(":/images/TrayIcon/quit.png"), "退出", this);

    // 创建菜单项
    addAction(curPlaySongAction);
    addAction(pauseAction);
    addAction(lastAction);
    addAction(nextAction);
    addSeparator();
    addAction(playModeAction);
    addAction(miniAction);
    addAction(openLyricAction);
    addAction(lockLyricAction);
    addSeparator();
    addAction(setAction);
    addSeparator();
    addAction(quitAction);
}
