#include "PlaySongInfoWidget.h"

PlaySongInfoWidget::PlaySongInfoWidget(QWidget *parent) : QFrame(parent)
{
    setFixedHeight(60);
    setFixedWidth(200);

    //border-width:上 右 下 左
    setStyleSheet("QFrame{background:rgb(246,246,248);border-color:rgb(225,225,225);border-width: 0px 1px 0px 1px;border-style: solid;}");

    m_fontMetrics = new QFontMetrics(this->font());

    initWidget();
}

PlaySongInfoWidget::~PlaySongInfoWidget()
{
    m_fontMetrics->~QFontMetrics();
}

void PlaySongInfoWidget::setSongText(QString song, QString single)
{
    songNameBtn->setText(m_fontMetrics->elidedText(song,Qt::ElideRight,songNameBtn->width()));
    songNameBtn->setToolTip(song);
    singleNameBtn->setText(m_fontMetrics->elidedText(single,Qt::ElideRight,singleNameBtn->width()));
    singleNameBtn->setToolTip(single);
}

void PlaySongInfoWidget::initWidget()
{
    h_mainLayout = new QHBoxLayout(this);
    v_initLayout1 = new QVBoxLayout;
    v_initLayout2 = new QVBoxLayout;

    cdCoverBtn = new QPushButton;
    cdCoverBtn->setFixedSize(60,60);
    cdCoverBtn->setCursor(Qt::PointingHandCursor);
    cdCoverBtn->setStyleSheet("QPushButton{border-image:url(:/images/SongInfo/cdCover.png)}");

    songNameBtn = new QPushButton;
    songNameBtn->setFixedSize(100,20);
    songNameBtn->setCursor(Qt::PointingHandCursor);
    songNameBtn->setText("未知");
    songNameBtn->setStyleSheet("QPushButton{background:transparent}");

    singleNameBtn = new QPushButton;
    singleNameBtn->setFixedSize(100,20);
    singleNameBtn->setCursor(Qt::PointingHandCursor);
    singleNameBtn->setText("未知");
    singleNameBtn->setStyleSheet("QPushButton{background:transparent}");

    v_initLayout1->addWidget(songNameBtn);
    v_initLayout1->addWidget(singleNameBtn);
    v_initLayout1->setMargin(0);

    loveBtn = new QPushButton;
    loveBtn->setCursor(Qt::PointingHandCursor);
    loveBtn->setFixedSize(14,12);
    loveBtn->setStyleSheet("QPushButton{border-image:url(:/images/SongInfo/love.png)}");

    shareBtn = new QPushButton;
    shareBtn->setCursor(Qt::PointingHandCursor);
    shareBtn->setFixedSize(13,14);
    shareBtn->setStyleSheet("QPushButton{border-image:url(:/images/SongInfo/share.png)}");

    v_initLayout2->addWidget(loveBtn);
    v_initLayout2->addWidget(shareBtn);
    v_initLayout2->setMargin(5);

    h_mainLayout->addWidget(cdCoverBtn);
    h_mainLayout->addLayout(v_initLayout1);
    h_mainLayout->addLayout(v_initLayout2);
    h_mainLayout->setMargin(0);
}
