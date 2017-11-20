#include "PlayListItemStyle.h"

PlayListItemStyle::PlayListItemStyle(QString songName, QString singalName, QString songTime, QWidget *parent):QFrame(parent)
{
    setFixedHeight(30);

    m_playStatus = new QLabel(this);
    m_playStatus->setGeometry(13,9,6,10);
    m_playStatus->setToolTip(m_playStatus->text());
    m_playStatus->setStyleSheet("QLabel{background:transparent;border-image:url(:/images/SongList/playLabel.png)}");

    m_songName = new QLabel(songName,this);
    m_songName->adjustSize();
    m_songName->setGeometry(31,9,m_songName->width(),12);
    m_songName->setToolTip(m_songName->text());
    m_songName->setStyleSheet("QLabel{border:none}");

    m_singalBtn = new QPushButton(singalName,this);
    m_singalBtn->adjustSize();
    m_singalBtn->setGeometry(373,9,m_singalBtn->width(),12);
    m_singalBtn->setCursor(Qt::PointingHandCursor);
    m_singalBtn->setToolTip(m_singalBtn->text());
    m_singalBtn->setStyleSheet("QPushButton{background:transparent;color:#888888;border:none}");

    m_sourceBtn = new QPushButton(this);
    m_sourceBtn->setGeometry(482,7,13,13);
    m_sourceBtn->setCursor(Qt::PointingHandCursor);
    m_sourceBtn->setToolTip("来源:");
    m_sourceBtn->setStyleSheet("QPushButton{background:transparent;border-image:url(:/images/SongList/source.png)}");

    m_songTime = new QLabel(songTime,this);
    m_songTime->adjustSize();
    m_songTime->setGeometry(514,9,m_songTime->width(),m_songTime->height());
    m_songTime->setStyleSheet("QLabel{border:none}");
}
