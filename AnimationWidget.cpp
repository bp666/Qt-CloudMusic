#include "AnimationWidget.h"

#define center_width 542
#define center_hieght 200
#define margin_width 110
#define margin_height 188

#define ToLeft 0
#define ToRight 1

AnimationWidget::AnimationWidget(QWidget *parent)
    : QFrame(parent)
{
    resize(770,230);
    mainCnt=3;

    for(int i=0;i<3;i++)
    {
        QPixmap temp_label = QPixmap(":/images/"+QString::number(i+1)+".png");
        label_group.push_back(temp_label);
    }

    int width = this->width();
    int height = this->height();

    int pos_x =(width-center_width)/2;
    int pos_y=(height-center_hieght)/2;

    center_rect.setRect(pos_x,pos_y,center_width,center_hieght);

    center_label =new QLabel(this);
    center_label->setPixmap(label_group[0]);

    center_label->setGeometry(pos_x,pos_y,center_width,center_hieght);


    transferBar = new QToolBar(this);
    transferBar->setGeometry(pos_x+center_width/2-40,pos_y+center_hieght+10,90,10);
    transferBar->setStyleSheet("background:transparent");
    transferBar->setIconSize(QSize(17,5));
    for(int actions_num=0;actions_num<2;actions_num++)
    {
        QAction *action=new QAction(QIcon(":/images/line.png"),"",transferBar);
        action->setData(actions_num);
        transferBar->addAction(action);
    }
    connect(transferBar,SIGNAL(actionTriggered(QAction *)),this,SLOT(onTriggerAction(QAction*)));

    /**
       设置右边控件的位置和大小
    */
    right_rect.setRect(pos_x+center_width,pos_y+(center_hieght-margin_height),margin_width,margin_height);
    right_label =new QLabel(this);
    right_label->setPixmap(label_group[1]);
    //right_label->setScaledContents(true);
    right_label->setGeometry(pos_x+center_width,pos_y+(center_hieght-margin_height),margin_width,margin_height);

    /**
       设置左边控件的位置和大小

    */
    pos_x=(pos_x-margin_width);
    pos_y=pos_y+(center_hieght-margin_height);

    left_rect.setRect(pos_x,pos_y,margin_width,margin_height);

    left_label =new QLabel(this);
    left_label->setPixmap(label_group[2]);
    //left_label->setScaledContents(true);
    left_label->setGeometry(pos_x,pos_y,margin_width,margin_height);
    center_label->raise();

}

AnimationWidget::~AnimationWidget()
{

}

void AnimationWidget::onTriggerAction(QAction *action)
{
    int action_num=action->data().toInt();
    if (action_num==ToLeft)
        moveLeft();
    else if(action_num==ToRight)
        moveRight();
}

void AnimationWidget::moveRight()
{
    mainCnt+=1;
    moveAnimation_left=new QPropertyAnimation(left_label,"geometry");
    moveAnimation_left->setDuration(200);
    moveAnimation_left->setStartValue(left_rect);
    moveAnimation_left->setEndValue(right_rect);
    moveAnimation_left->setEasingCurve(QEasingCurve::Linear);
    moveAnimation_left->start();


    moveAnimation=new QPropertyAnimation(center_label,"geometry");
    moveAnimation->setDuration(200);
    moveAnimation->setStartValue(center_rect);
    moveAnimation->setEndValue(left_rect);
    moveAnimation->setEasingCurve(QEasingCurve::Linear);
    moveAnimation->start();


    moveAnimation_right=new QPropertyAnimation(right_label,"geometry");
    moveAnimation_right->setDuration(200);
    moveAnimation_right->setStartValue(right_rect);
    moveAnimation_right->setEndValue(center_rect);
    moveAnimation_right->setEasingCurve(QEasingCurve::Linear);
    moveAnimation_right->start();

    /**
        方向和label移动的方向恰恰相反
    */
    QRect rect(right_rect);
    right_rect=center_rect;
    center_rect=left_rect;
    left_rect=rect;

    if(mainCnt==6)
        mainCnt=3;
    if(mainCnt==4)
    {
        right_label->raise();
    }
    else if(mainCnt==5)
    {
        left_label->raise();
    }
    else if(mainCnt==1)
    {
       center_label->raise();
    }
}

void AnimationWidget::moveLeft()
{
    mainCnt-=1;

    moveAnimation_left=new QPropertyAnimation(left_label,"geometry");
    moveAnimation_left->setDuration(200);
    moveAnimation_left->setStartValue(left_rect);
    moveAnimation_left->setEndValue(center_rect);
    moveAnimation_left->setEasingCurve(QEasingCurve::Linear);
    moveAnimation_left->start();

    moveAnimation=new QPropertyAnimation(center_label,"geometry");
    moveAnimation->setDuration(200);
    moveAnimation->setStartValue(center_rect);
    moveAnimation->setEndValue(right_rect);
    moveAnimation->setEasingCurve(QEasingCurve::Linear);
    moveAnimation->start();

    moveAnimation_right=new QPropertyAnimation(right_label,"geometry");
    moveAnimation_right->setDuration(200);
    moveAnimation_right->setStartValue(right_rect);
    moveAnimation_right->setEndValue(left_rect);
    moveAnimation_right->setEasingCurve(QEasingCurve::Linear);
    moveAnimation_right->start();


    /**
       方向和label移动的方向恰恰相反

      */
    QRect rect(left_rect);
    left_rect=center_rect;
    center_rect=right_rect;
    right_rect=rect;

    if(mainCnt==-1)
        mainCnt=3;

    if(mainCnt==2)
    {
        left_label->raise();
    }
    else if(mainCnt==1)
    {
        right_label->raise();
    }

    else if(mainCnt==0)
    {
        center_label->raise();
    }
}

