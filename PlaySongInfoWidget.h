#ifndef PLAYSONGINFOWIDGET_H
#define PLAYSONGINFOWIDGET_H

#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFontMetrics>

class PlaySongInfoWidget : public QFrame
{
    Q_OBJECT
public:
    explicit PlaySongInfoWidget(QWidget *parent = 0);
    ~PlaySongInfoWidget();

    QPushButton *cdCoverBtn, *songNameBtn, *singleNameBtn, *loveBtn, *shareBtn;

    void setSongText(QString,QString);

private:
    void initWidget();

    QHBoxLayout *h_mainLayout;
    QVBoxLayout *v_initLayout1, *v_initLayout2;

    QFontMetrics *m_fontMetrics;
};

#endif // PLAYSONGINFOWIDGET_H
