#ifndef TRAYICONMENU_H
#define TRAYICONMENU_H

#include <QMenu>

class TrayIconMenu : public QMenu
{
    Q_OBJECT
public:
    explicit TrayIconMenu(QWidget *parent = 0);

signals:


private:
    void initAction();

public:
    QAction *curPlaySongAction,\
            *pauseAction,\
            *lastAction,\
            *nextAction,\
            *playModeAction,\
            *miniAction,\
            *openLyricAction,\
            *lockLyricAction,\
            *setAction,\
            *quitAction;
};

#endif // TRAYICONMENU_H
