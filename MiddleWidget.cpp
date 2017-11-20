#include "MiddleWidget.h"

MiddleWidget::MiddleWidget(QWidget *parent) : QWidget(parent)
{
    m_hmainLayout = new QHBoxLayout(this);
    m_vListLayout = new QVBoxLayout;

    m_List = new MiddleWidgetLeftList;

    m_PlaySongInfoWidget = new PlaySongInfoWidget;

    m_vListLayout->addWidget(m_List);
    m_vListLayout->addWidget(m_PlaySongInfoWidget);
    m_vListLayout->setSpacing(0);

    m_Stack = new MiddleWidgetRightStack;

    m_hmainLayout->addLayout(m_vListLayout);
    m_hmainLayout->addWidget(m_Stack);
    m_hmainLayout->setMargin(0);
    m_hmainLayout->setSpacing(0);


    connect(m_List->signalMapper,SIGNAL(mapped(int)),m_Stack,SLOT(setCurrentIndex(int)));

    m_SelectDirFrame = new SelectDirFrame;

    connect(m_Stack->m_selectBtn,SIGNAL(clicked(bool)),this,SLOT(slot_showSelectDirFrame()));
    connect(m_SelectDirFrame->m_ackBtn,SIGNAL(clicked(bool)),this,SLOT(slot_ackDir()));


}

void MiddleWidget::slot_showSelectDirFrame()
{
    m_SelectDirFrame->show();
}

void MiddleWidget::slot_ackDir()
{
    //清空媒体列表

    m_Stack->localPlayList->clear();
    //清空数据库
    m_Stack->db.emptyTable();

    //清空上一次的歌曲列表项
    if(m_Stack->m_Stack4TableWidget->rowCount()!=0)
    {
        m_Stack->m_Stack4TableWidget->clearContents();
        m_Stack->m_Stack4TableWidget->setRowCount(0);
    }

    m_SelectDirFrame->getCheckedState();
    m_SelectDirFrame->close();
    m_Stack->SongDirPath = m_SelectDirFrame->DirList;
    m_Stack->slot_widget4MatchSong();
}
