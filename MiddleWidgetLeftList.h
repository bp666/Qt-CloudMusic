#ifndef MIDDLEWIDGETLEFTLIST_H
#define MIDDLEWIDGETLEFTLIST_H

#include <QFrame>
#include <QToolButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QSignalMapper>

class MiddleWidgetLeftList : public QFrame
{
    Q_OBJECT
public:
    explicit MiddleWidgetLeftList(QWidget *parent = 0);

    QPushButton *findMusicBtn, *privateFMBtn, *mvBtn, *friendBtn;
    QPushButton *localMusicBtn, *downManageBtn, *myMusicBoxBtn, *mySingerBtn;
    QSignalMapper *signalMapper;
private:
    void initTopWidget();
    void initBtnLinkStack();

    QVBoxLayout *m_vMainLayout;

    QLabel *recommendLabel, *myMusicLabel;

    QButtonGroup *mutexBtnGroup;

    QToolButton *createSongListBtn;
};

#endif // MIDDLEWIDGETLEFTLIST_H
