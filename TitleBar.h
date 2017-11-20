#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

class TitleBar : public QFrame
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0);

    QLabel *titleIconLabel, *nullLabel;
    QPushButton *leftBtn, *rightBtn, *searchBtn, *userIconBtn, *loginBtn, *skinBtn, *mailBtn, *setBtn, *miniBtn, *minimumBtn, *maximumBtn, *closeBtn;
    QLineEdit *searchEdit;

private:
    //初始化标题栏
    void initTitle();

    QHBoxLayout *titleLayout, *searchLayout, *Layout1, *Layout2;
};

#endif // TITLEBAR_H
