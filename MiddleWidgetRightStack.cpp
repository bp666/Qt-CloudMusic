#include "MiddleWidgetRightStack.h"

static QVector<QStringList> SongsInfo;

MiddleWidgetRightStack::MiddleWidgetRightStack(QWidget *parent) : QStackedWidget(parent)
{
    setStyleSheet("QStackedWidget{background:rgb(250,250,250)}");

    //initStack();
    initFindMusicStack0();
    initLocalMusicStack4();
    initSongSearchStack();

    addWidget(stackChildWidget0);
    addWidget(new QLabel("window 1"));
    addWidget(new QLabel("window 2"));
    addWidget(new QLabel("window 3"));
    addWidget(stackChildWidget4);
    addWidget(new QLabel("window 5"));
    addWidget(new QLabel("window 6"));
    addWidget(new QLabel("window 7"));
    addWidget(SearchWidget8);
}

MiddleWidgetRightStack::~MiddleWidgetRightStack()
{
    thread->~ThreadOfRight();
}

void MiddleWidgetRightStack::initStack()
{
}

void MiddleWidgetRightStack::initFindMusicStack0()
{
    stackChildWidget0 = new BaseStackChildWidget;

    findMusicStack = new QStackedWidget;

    recommendBtn = new QPushButton("个性推荐");
    recommendBtn->setFixedSize(60,40);
    //设置可选中
    recommendBtn->setCheckable(true);
    recommendBtn->setChecked(true);
    //用css设置下边框颜色字会弹起，先用图片代替        border-style: solid; border-bottom-width:2px; border-bottom-color:#66b7ff;
    recommendBtn->setStyleSheet("QPushButton{background:transparent;color:rgb(68,68,68);font-size:15px}\
                                 QPushButton:hover{color:rgb(102,183,255);}\
                                 QPushButton:checked{border-image:url(:/images/RightStack/0/btn_mask.png);color:rgb(102,183,255)}");

    songListBtn = new QPushButton("歌单");
    songListBtn->setFixedSize(60,40);
    songListBtn->setCheckable(true);
    songListBtn->setStyleSheet("QPushButton{background:transparent;color:rgb(68,68,68);font-size:15px}\
                                QPushButton:hover{color:rgb(102,183,255);}\
                                QPushButton:checked{border-image:url(:/images/RightStack/0/btn_mask.png);color:rgb(102,183,255)}");

    radioBtn = new QPushButton("主播电台");
    radioBtn->setFixedSize(60,40);
    radioBtn->setCheckable(true);
    radioBtn->setStyleSheet("QPushButton{background:transparent;color:rgb(68,68,68);font-size:15px}\
                             QPushButton:hover{color:rgb(102,183,255);}\
                             QPushButton:checked{border-image:url(:/images/RightStack/0/btn_mask.png);color:rgb(102,183,255)}");

    rankBtn = new QPushButton("排行榜");
    rankBtn->setFixedSize(60,40);
    rankBtn->setCheckable(true);
    rankBtn->setStyleSheet("QPushButton{background:transparent;color:rgb(68,68,68);font-size:15px}\
                            QPushButton:hover{color:rgb(102,183,255);}\
                            QPushButton:checked{border-image:url(:/images/RightStack/0/btn_mask.png);color:rgb(102,183,255)}");

    singleBtn = new QPushButton("歌手");
    singleBtn->setFixedSize(60,40);
    singleBtn->setCheckable(true);
    singleBtn->setStyleSheet("QPushButton{background:transparent;color:rgb(68,68,68);font-size:15px}\
                              QPushButton:hover{color:rgb(102,183,255);}\
                              QPushButton:checked{border-image:url(:/images/RightStack/0/btn_mask.png);color:rgb(102,183,255)}");

    newMusicBtn = new QPushButton("最新音乐");
    newMusicBtn->setFixedSize(60,40);
    newMusicBtn->setCheckable(true);
    newMusicBtn->setStyleSheet("QPushButton{background:transparent;color:rgb(68,68,68);font-size:15px}\
                                QPushButton:hover{color:rgb(102,183,255);}\
                                QPushButton:checked{border-image:url(:/images/RightStack/0/btn_mask.png);color:rgb(102,183,255)}");

    //把按钮保存在按钮容器中
    m_btn0<<recommendBtn<<songListBtn<<radioBtn<<rankBtn<<singleBtn<<newMusicBtn;

    mutexBtnGroup0 = new QButtonGroup(stackChildWidget0);
    //设置按钮互斥
    mutexBtnGroup0->setExclusive(true);

    for(int i=0;i<m_btn0.count();i++)
    {
        m_btn0.at(i)->setObjectName(QString::number(i));
        mutexBtnGroup0->addButton(m_btn0.at(i));
        connect(m_btn0.at(i),SIGNAL(clicked()),this,SLOT(slot_widget1BtnClick()));
    }

    h_btnBarLayout = new QHBoxLayout;

    h_btnBarLayout->addStretch(165);
    h_btnBarLayout->addWidget(recommendBtn,0,Qt::AlignHCenter);
    h_btnBarLayout->addWidget(songListBtn,0,Qt::AlignHCenter);
    h_btnBarLayout->addWidget(radioBtn,0,Qt::AlignHCenter);
    h_btnBarLayout->addWidget(rankBtn,0,Qt::AlignHCenter);
    h_btnBarLayout->addWidget(singleBtn,0,Qt::AlignHCenter);
    h_btnBarLayout->addWidget(newMusicBtn,0,Qt::AlignHCenter);
    h_btnBarLayout->addStretch(165);
    h_btnBarLayout->setSpacing(20);
    h_btnBarLayout->setMargin(0);

//发现音乐个性推荐
    m_FMOneFrame = new QFrame;

    m_vFMOneLo = new QVBoxLayout(m_FMOneFrame);

    m_animationFrame = new AnimationWidget(m_FMOneFrame);

    m_vFMOneLo->addWidget(m_animationFrame,Qt::AlignHCenter);
    m_vFMOneLo->addStretch();

    findMusicStack->addWidget(m_FMOneFrame);
    findMusicStack->addWidget(new QLabel("window2"));
    findMusicStack->addWidget(new QLabel("window3"));
    findMusicStack->addWidget(new QLabel("window4"));
    findMusicStack->addWidget(new QLabel("window5"));
    findMusicStack->addWidget(new QLabel("window6"));

    v_btnBarLayout = new QVBoxLayout(stackChildWidget0);
    v_btnBarLayout->addLayout(h_btnBarLayout);
    v_btnBarLayout->addWidget(findMusicStack);
    v_btnBarLayout->setMargin(0);
}

//方法二：sender()获取发送信号的对象指针
//多个button实现不同的参数
void MiddleWidgetRightStack::slot_widget1BtnClick()
{
    int index=sender()->objectName().toInt();
    findMusicStack->setCurrentIndex(index);
}


void MiddleWidgetRightStack::initLocalMusicStack4()
{
    stackChildWidget4 = new QFrame;
    localPlayList = new QMediaPlaylist;
    //localPlayList->setPlaybackMode(QMediaPlaylist::Sequential);

    titleFrame = new QFrame;
    titleFrame->setFixedHeight(56);
    titleFrame->setStyleSheet("QFrame{border-color:rgb(225,225,225);border-width: 0 0 1 0;border-style: solid}");

    hTitleLayout = new QHBoxLayout(titleFrame);

    m_localLabel = new QLabel("本地音乐");
    m_localLabel->setStyleSheet("QLabel{border:none;font:20px}");
    m_localLabel->setFixedWidth(100);

    m_CountLabel = new QLabel("0首音乐,");
    m_CountLabel->resize(m_CountLabel->width(),m_CountLabel->height());
    m_CountLabel->setStyleSheet("QLabel{border:none}");

    m_selectBtn = new QPushButton("选择目录");
    m_selectBtn->setFixedWidth(50);
    m_selectBtn->setCursor(Qt::PointingHandCursor);
    m_selectBtn->setStyleSheet("QPushButton{background:transparent;color:#0c73c2}");

    m_listBtn = new QPushButton;
    m_listBtn->setFixedSize(26,22);
    m_listBtn->setCursor(Qt::PointingHandCursor);
    m_listBtn->setCheckable(true);
    m_listBtn->setChecked(true);
    m_listBtn->setToolTip("列表");
    m_listBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/list.png)}\
                              QPushButton:checked{border-image:url(:/images/RightStack/4/list_checked.png)}");

    m_singalBtn = new QPushButton;
    m_singalBtn->setFixedSize(26,22);
    m_singalBtn->setCursor(Qt::PointingHandCursor);
    m_singalBtn->setCheckable(true);
    m_singalBtn->setToolTip("歌手");
    m_singalBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/singal.png)}\
                                QPushButton:checked{border-image:url(:/images/RightStack/4/singal_checked.png)}");

    m_cdBtn = new QPushButton;
    m_cdBtn->setFixedSize(26,22);
    m_cdBtn->setCursor(Qt::PointingHandCursor);
    m_cdBtn->setCheckable(true);
    m_cdBtn->setToolTip("专辑");
    m_cdBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/cd.png)}\
                            QPushButton:checked{border-image:url(:/images/RightStack/4/cd_checked.png)}");

    m_dirBtn = new QPushButton;
    m_dirBtn->setFixedSize(26,22);
    m_dirBtn->setCursor(Qt::PointingHandCursor);
    m_dirBtn->setCheckable(true);
    m_dirBtn->setToolTip("文件夹");
    m_dirBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/dir.png)}\
                             QPushButton:checked{border-image:url(:/images/RightStack/4/dir_checked.png)}");

     //把按钮保存在按钮容器中
     m_btn4<<m_listBtn<<m_singalBtn<<m_cdBtn<<m_dirBtn;

     mutexBtnGroup4 = new QButtonGroup(stackChildWidget4);
     //设置按钮互斥
     mutexBtnGroup4->setExclusive(true);

     for(int i=0;i<m_btn4.count();i++)
     {
         m_btn4.at(i)->setObjectName(QString::number(i));
         mutexBtnGroup4->addButton(m_btn4.at(i));
         connect(m_btn4.at(i),SIGNAL(clicked()),this,SLOT(slot_widget4BtnClick()));
     }


    hTitleLayout->addWidget(m_localLabel);
    hTitleLayout->addWidget(m_CountLabel);
    hTitleLayout->addWidget(m_selectBtn);
    hTitleLayout->addStretch();
    hTitleLayout->addWidget(m_listBtn);
    hTitleLayout->addWidget(m_singalBtn);
    hTitleLayout->addWidget(m_cdBtn);
    hTitleLayout->addWidget(m_dirBtn);
    hTitleLayout->setSpacing(0);

    stackFrame4 = new QFrame;

    stackTitleFrame = new QFrame;
    stackTitleFrame->setFixedHeight(58);

    hStackTitleLayout = new QHBoxLayout(stackTitleFrame);

    m_playAllBtn = new QPushButton;
    m_playAllBtn->setCursor(Qt::PointingHandCursor);
    m_playAllBtn->setFixedSize(91,26);
    m_playAllBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/PlayAll.png)}");

    m_addBtn = new QPushButton;
    m_addBtn->setCursor(Qt::PointingHandCursor);
    m_addBtn->setFixedSize(32,26);
    m_addBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/Add.png)}");

    m_matchMusicBtn = new QPushButton;
    m_matchMusicBtn->setCursor(Qt::PointingHandCursor);
    m_matchMusicBtn->setFixedSize(92,26);
    m_matchMusicBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/Match.png)}");

    m_searchEdit = new QLineEdit;
    m_searchEdit->setFixedSize(172,24);
    m_searchEdit->setPlaceholderText("搜索本地音乐");
    m_searchEdit->setStyleSheet("QLineEdit{border-radius:10px;border-color:rgb(225,225,225);border-width: 1;border-style: solid}");

    m_searchLabel = new QLabel;
    m_searchLabel->setFixedSize(13,14);
    m_searchLabel->setStyleSheet("QLabel{border-image:url(:/images/RightStack/4/search.png)}");

    //设置m_searchEdit的可编辑边缘，
    QMargins margins = m_searchEdit->textMargins();
    m_searchEdit->setTextMargins(margins.left()+10, margins.top(), m_searchLabel->width()+15, margins.bottom());

    //m_searchLabel附在m_searchEdit上，Layout的主窗口是m_searchEdit
    QHBoxLayout *searchLayout = new QHBoxLayout(m_searchEdit);
    searchLayout->addStretch();
    searchLayout->addWidget(m_searchLabel);
    searchLayout->setSpacing(0);
    //设置m_searchLabel在m_searchEdit右边的边缘
    searchLayout->setContentsMargins(0,0,10,0);

    hStackTitleLayout->addWidget(m_playAllBtn);
    hStackTitleLayout->addWidget(m_addBtn);
    hStackTitleLayout->addSpacing(15);
    hStackTitleLayout->addWidget(m_matchMusicBtn);
    hStackTitleLayout->addStretch();
    hStackTitleLayout->addWidget(m_searchEdit);
    hStackTitleLayout->setSpacing(0);

//歌曲列表
    m_Stack4TableWidget = new QTableWidget;

    m_Stack4TableWidget->setColumnCount(6);//表头个数

    //设置表头内容
    QStringList header;
    header<<""<<" 音乐标题"<<" 歌手"<<" 专辑"<<" 时长"<<" 大小";
    m_Stack4TableWidget->setHorizontalHeaderLabels(header);

    //horizontalHeader()水平句柄
    m_Stack4TableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);//只能用resizeSection设置大小
    m_Stack4TableWidget->horizontalHeader()->resizeSection(0,50);//设置表头的位置
    m_Stack4TableWidget->horizontalHeader()->resizeSection(1,180);
    m_Stack4TableWidget->horizontalHeader()->resizeSection(2,120);
    m_Stack4TableWidget->horizontalHeader()->resizeSection(3,180);
    m_Stack4TableWidget->horizontalHeader()->resizeSection(4,120);
    m_Stack4TableWidget->horizontalHeader()->setFixedHeight(30); //设置表头的高度
    m_Stack4TableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    m_Stack4TableWidget->horizontalHeader()->setHighlightSections(false); //点击表时,表头行不跟着亮
    m_Stack4TableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);//默认文字居左
    m_Stack4TableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#fafafa;color:#666666;border:1px solid #cccccc;}"
                                                           "QHeaderView::section::hover{background:#ecedee}");

    //selection-background-color选中行颜色
    m_Stack4TableWidget->setStyleSheet("QTableWidget{color:#888888;selection-background-color:#e4e4e6}");

    //verticalHeader()垂直句柄
    m_Stack4TableWidget->verticalHeader()->setDefaultSectionSize(30); //设置行高
    m_Stack4TableWidget->verticalHeader()->setVisible(false);//垂直头是否可见，就是每行的num编号
    m_Stack4TableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent;width:10;height:150;}"
                                                            "QScrollBar::handle{background:#e1e1e2; border:2px solid transparent; border-radius:5px;}"
                                                            "QScrollBar::handle:hover{background:#cfcfd1;}"
                                                            "QScrollBar::sub-line{background:transparent;}"
                                                            "QScrollBar::add-line{background:transparent;}");

    m_Stack4TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//选择一行
    m_Stack4TableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//单选
    m_Stack4TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    m_Stack4TableWidget->setFocusPolicy(Qt::NoFocus); //去除选中虚线框
    m_Stack4TableWidget->setShowGrid(false); //设置不显示格子线
    m_Stack4TableWidget->setAlternatingRowColors(true);//设置交替行颜色
    m_Stack4TableWidget->setFrameShape(QFrame::NoFrame); //设置无边框

    hStack4Layout = new QVBoxLayout(stackFrame4);
    hStack4Layout->addWidget(stackTitleFrame);
    hStack4Layout->addWidget(m_Stack4TableWidget);
    hStack4Layout->setMargin(0);
    hStack4Layout->setSpacing(0);

    localMusicStack = new QStackedWidget;

    localMusicStack->addWidget(stackFrame4);
    localMusicStack->addWidget(new QLabel("window2"));
    localMusicStack->addWidget(new QLabel("window3"));
    localMusicStack->addWidget(new QLabel("window4"));

    vMainLayout4 = new QVBoxLayout(stackChildWidget4);
    vMainLayout4->addWidget(titleFrame);
    vMainLayout4->addWidget(localMusicStack);
    vMainLayout4->setMargin(0);
    vMainLayout4->setSpacing(0);

    connect(m_matchMusicBtn,SIGNAL(clicked()),this,SLOT(slot_widget4MatchSong()));

    thread = new ThreadOfRight;
    connect(thread,SIGNAL(finished()),this,SLOT(slot_setWidget4TableItem()));
    thread->start();
}

void MiddleWidgetRightStack::setTableItem(int& rownum, QString title, QString singal, QString cd, QString time, QString size)
{
    m_Stack4TableWidget->insertRow(rownum);
    QString num=QString("%1").arg(rownum+1, 2, 10, QChar('0'));

    QTableWidgetItem *item = new QTableWidgetItem(num);
    QTableWidgetItem *item1 = new QTableWidgetItem(title);
    QTableWidgetItem *item2 = new QTableWidgetItem(singal);
    QTableWidgetItem *item3 = new QTableWidgetItem(cd);
    QTableWidgetItem *item4 = new QTableWidgetItem(time);
    QTableWidgetItem *item5 = new QTableWidgetItem(size);

    m_Stack4TableWidget->setItem(rownum,0,item);
    m_Stack4TableWidget->item(rownum,0)->setTextAlignment(Qt::AlignCenter|Qt::AlignRight);
    m_Stack4TableWidget->setItem(rownum,1,item1);
    m_Stack4TableWidget->item(rownum,1)->setTextColor(QColor(0,0,0));
    m_Stack4TableWidget->setItem(rownum,2,item2);
    m_Stack4TableWidget->setItem(rownum,3,item3);
    m_Stack4TableWidget->setItem(rownum,4,item4);
    m_Stack4TableWidget->setItem(rownum,5,item5);
}

void MiddleWidgetRightStack::slot_widget4BtnClick()
{
    int index=sender()->objectName().toInt();
    localMusicStack->setCurrentIndex(index);
}

void MiddleWidgetRightStack::slot_widget4MatchSong()
{
    int curCount = 0;
    int countSum = 0;
    for(int i=0;i<SongDirPath.count();i++)
    {
        matchDir.setPath(SongDirPath.at(i));
        matchDir.setNameFilters(QStringList("*.mp3"));//过滤文件
        matchMp3Files = matchDir.entryList();//列出所有符合的文件
        countSum += matchMp3Files.count();
        for(int j=curCount, cur=0; j<countSum; j++, cur++, curCount++)
        {
            mp3Name = SongDirPath.at(i) + '/' + matchMp3Files.at(cur);

            //获取文件的MD5值对比文件是否相同
            QFile file(mp3Name);
            file.open(QIODevice::ReadOnly);
            MD5Str = QCryptographicHash::hash(file.readAll(),QCryptographicHash::Md5).toHex().constData();
            file.close();

            if(MD5List.contains(MD5Str))
                continue;

            //保存文件的MD5值
            MD5List.append(MD5Str);

            //添加歌曲到媒体列表
            localPlayList->addMedia(QMediaContent(QUrl(mp3Name)));

            //mp3大小
            fileInfo.setFile(mp3Name);
            qint64 fileSize= fileInfo.size();
            if(fileSize/1024)
            {
                if(fileSize/1024/1024)
                {
                    if(fileSize/1024/1024/1024)
                    {
                        mp3Size = QString::number(fileSize/1024/1024/1024,10)+"GB";
                    }
                    else
                       mp3Size = QString::number(fileSize/1024/1024,10)+"MB";
                }
                else
                    mp3Size = QString::number(fileSize/1024,10)+"KB";
            }
            else
                mp3Size = QString::number(fileSize,10)+"B";

            //转为本地编码
            bytes = mp3Name.toLocal8Bit();

            TagLib::FileRef f(bytes.data());

            if(f.isNull())
            {
                qDebug()<<matchMp3Files.at(cur)<<",无法读取";
                continue;
            }

            TagLib::PropertyMap tags = f.file()->properties();

            //ALBUM专辑 ARTIST艺术家 TITLE标题
            titleStr = tags["TITLE"].toString().toCString(true);

            if(titleStr.isEmpty())
                titleStr = fileInfo.baseName();

            artistStr = tags["ARTIST"].toString().toCString(true);

            if(artistStr.isEmpty())
                artistStr="未知";

            albumStr = tags["ALBUM"].toString().toCString(true);

            if(albumStr.isEmpty())
                albumStr="未知";

            TagLib::AudioProperties *properties = f.audioProperties();

            int seconds = properties->length() % 60;
            int minutes = (properties->length() - seconds) / 60;

            timeStr = QString::number(minutes)+":"+QString("%1").arg(seconds, 2, 10, QChar('0'));

            rowcount= m_Stack4TableWidget->rowCount();

            //把歌曲信息保存进数据库
            db.addSongList(rowcount,titleStr, artistStr, albumStr, timeStr, mp3Size,mp3Name);

            setTableItem(rowcount,titleStr, artistStr, albumStr, timeStr, mp3Size);
        }
        //更新歌曲总数
        if(rowcount!=0)
            m_CountLabel->setText(QString("%1首音乐,").arg(rowcount+1));
    }
}

void MiddleWidgetRightStack::slot_setWidget4TableItem()
{
    if(SongsInfo.isEmpty())
        return;

    for(int i=0;i<SongsInfo.count();i++)
    {
        QString count = SongsInfo[i][0];
        rowcount = count.toInt();
        setTableItem(rowcount,SongsInfo[i][1], SongsInfo[i][2], SongsInfo[i][3], SongsInfo[i][4], SongsInfo[i][5]);
        localPlayList->addMedia(QMediaContent(QUrl(SongsInfo[i][6])));
    }
    if(rowcount!=0)
        m_CountLabel->setText(QString("%1首音乐,").arg(rowcount+1));

    //退出线程
    thread->terminate();
    thread->wait();
}

void MiddleWidgetRightStack::initSongSearchStack()
{
    SearchWidget8 = new QWidget;
    m_vSearchLayout = new QVBoxLayout(SearchWidget8);

    m_SearchLabel = new QLabel("    搜索\"\"");//，找到0首单曲
    m_SearchLabel->setFixedHeight(76);
    m_SearchLabel->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    m_SearchLabel->setStyleSheet("QLabel{border-color:#44AAF8;border-width: 0 0 1 0;border-style: solid}");

    m_SearchWidget = new QTableWidget;
    m_SearchWidget->setColumnCount(5);//表头个数

    //设置表头内容
    QStringList header;
    header<<""<<"操作"<<"音乐标题"<<"歌手"<<"时长";
    m_SearchWidget->setHorizontalHeaderLabels(header);

    //horizontalHeader()水平句柄
    m_SearchWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);//只能用resizeSection设置大小
    m_SearchWidget->horizontalHeader()->resizeSection(0,50);//设置表头的位置
    m_SearchWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    m_SearchWidget->horizontalHeader()->resizeSection(1,60);
    m_SearchWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    m_SearchWidget->horizontalHeader()->resizeSection(2,300);
    m_SearchWidget->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    m_SearchWidget->horizontalHeader()->resizeSection(3,200);
    m_SearchWidget->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Fixed);
    m_SearchWidget->horizontalHeader()->resizeSection(4,50);
    m_SearchWidget->horizontalHeader()->setFixedHeight(30); //设置表头的高度
    m_SearchWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    m_SearchWidget->horizontalHeader()->setHighlightSections(false); //点击表时,表头行不跟着亮
    m_SearchWidget->horizontalHeader()->setSectionsClickable(false); //设置表头不可点击
    m_SearchWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);//默认文字居左
    m_SearchWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#fafafa;color:#666666;border:1px solid #cccccc;}"
                                                      "QHeaderView::section::hover{background:#ecedee}");

    //selection-background-color选中行颜色
    m_SearchWidget->setStyleSheet("QTableWidget{color:#888888;selection-background-color:#e4e4e6}");

    //verticalHeader()垂直句柄
    m_SearchWidget->verticalHeader()->setDefaultSectionSize(30); //设置行高
    m_SearchWidget->verticalHeader()->setVisible(false);//垂直头是否可见，就是每行的num编号
    m_SearchWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent;width:10;height:150;}"
                                                       "QScrollBar::handle{background:#e1e1e2; border:2px solid transparent; border-radius:5px;}"
                                                       "QScrollBar::handle:hover{background:#cfcfd1;}"
                                                       "QScrollBar::sub-line{background:transparent;}"
                                                       "QScrollBar::add-line{background:transparent;}");

    m_SearchWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//选择一行
    m_SearchWidget->setSelectionMode(QAbstractItemView::SingleSelection);//单选
    m_SearchWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    m_SearchWidget->setFocusPolicy(Qt::NoFocus); //去除选中虚线框
    m_SearchWidget->setShowGrid(false); //设置不显示格子线
    m_SearchWidget->setAlternatingRowColors(true);//设置交替行颜色
    m_SearchWidget->setFrameShape(QFrame::NoFrame); //设置无边框


    //加载中动画
    m_progressLabel = new QLabel;
    m_progressLabel->setFixedSize(32,32);
    m_progressMovie = new QMovie(":/images/SearchStack/progressbar.gif");
    m_progressLabel->setMovie(m_progressMovie);

    m_hProgressLayout = new QHBoxLayout();
    //m_hProgressLayout->addStretch();
    m_hProgressLayout->addWidget(m_progressLabel);

    //页数按钮
    pageFrame = new QFrame;

    m_leftBtn = new QPushButton;
    m_leftBtn->setFixedSize(24,24);
    m_leftBtn->setStyleSheet("QPushButton{border-image:url(:/images/SearchStack/left.png)}"
                             "QPushButton:hover{background:transparent;border-image:url(:/images/SearchStack/left_hover.png)}");
    m_rightBtn = new QPushButton;
    m_rightBtn->setFixedSize(24,24);
    m_rightBtn->setStyleSheet("QPushButton{border-image:url(:/images/SearchStack/right.png)}"
                              "QPushButton:hover{background:transparent;border-image:url(:/images/SearchStack/right_hover.png)}");

    pageBtnFrame = new QFrame;

    m_hPageLayout = new QHBoxLayout(pageFrame);
    m_hPageLayout->addStretch();
    m_hPageLayout->addWidget(m_leftBtn);
    m_hPageLayout->addSpacing(5);
    m_hPageLayout->addWidget(pageBtnFrame);
    m_hPageLayout->addSpacing(5);
    m_hPageLayout->addWidget(m_rightBtn);
    m_hPageLayout->addStretch();
    m_hPageLayout->setMargin(0);
    m_hPageLayout->setSpacing(0);

    m_vSearchLayout->addWidget(m_SearchLabel);
    m_vSearchLayout->addLayout(m_hProgressLayout);
    m_vSearchLayout->addWidget(m_SearchWidget);
    m_vSearchLayout->addWidget(pageFrame);
    m_vSearchLayout->setMargin(0);
    m_vSearchLayout->setSpacing(0);

    m_SearchWidget->hide();
    pageFrame->hide();
    m_progressLabel->hide();
}


//-------------------------------------QThread----------------------------------------------

void ThreadOfRight::run()
{
    DataBase db;
    db.query.exec(QString("SELECT * FROM songinfo order by id"));
    while(db.query.next())
    {
        QStringList st;
        st.append(db.query.value("id").toString());
        st.append(db.query.value("title").toString());
        st.append(db.query.value("singer").toString());
        st.append(db.query.value("cd").toString());
        st.append(db.query.value("time").toString());
        st.append(db.query.value("size").toString());
        st.append(db.query.value("mediaSrc").toString());
        SongsInfo.append(st);
    }
}
