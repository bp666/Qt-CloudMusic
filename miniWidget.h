#ifndef MINIWIDGET_H
#define MINIWIDGET_H

#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

class miniWidget : public QFrame
{
    Q_OBJECT
public:
    explicit miniWidget(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

public:
    QFrame *m_mainFrame,*m_minorFrame;
    QPushButton *m_photoBtn, *m_loveBtn, *m_volBtn, *m_listBtn,\
                *m_closeBtn, *m_recoveryWinBtn,\
                *m_lastBtn, *m_playStateBtn, *m_nextBtn;

    QLabel *m_songNameLab, *m_singleLab, *m_tipLab;

private:
    void init_miniWidget();
    bool m_mouseState;
    QPoint  m_WindowPos, m_MousePos;

    QHBoxLayout *m_hMainLayout, *m_hPlayLayout;
    QFrame *m_palyFrame;
    QVBoxLayout *m_vMainLayout, *m_vInfoLayout ,*m_vLayout;
};

#endif // MINIWIDGET_H
