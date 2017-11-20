#ifndef WIDGET_H
#define WIDGET_H

#include <QFrame>
#include <QVector>
#include <QLabel>
#include <QToolBar>
#include <QPropertyAnimation>

class AnimationWidget : public QFrame
{
    Q_OBJECT

public:
    AnimationWidget(QWidget *parent = 0);
    ~AnimationWidget();

protected slots:
    void onTriggerAction(QAction *);

private:
    void moveLeft();
    void moveRight();
    QRect center_rect;
    QRect left_rect;
    QRect right_rect;

    QLabel *center_label;
    QLabel *left_label;
    QLabel *right_label;

    QPropertyAnimation *moveAnimation;
    QPropertyAnimation *moveAnimation_left;
    QPropertyAnimation *moveAnimation_right;

    int mainCnt;
    //下方的横线控件
    QToolBar *transferBar;
    QVector<QPixmap> label_group;
};

#endif // WIDGET_H
