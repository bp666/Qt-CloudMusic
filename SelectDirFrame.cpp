#include "SelectDirFrame.h"
#include <QFileDialog>
#include <QScrollBar>

SelectDirFrame::SelectDirFrame(QWidget *parent) : FramelessAndAutoSize(parent)
{
    setStyleSheet("QFrame{border-color:rgb(225,225,225);border-width: 1;border-style: solid}");

    setAttribute(Qt::WA_ShowModal,true);

    setFixedSize(300,350);

    m_f1 = new QFrame;
    m_f1->setFixedHeight(50);
    m_f1->setStyleSheet("QFrame{background:#ffffff}");
    m_f1->setCursor(Qt::SizeAllCursor);
    f1HLayout = new QHBoxLayout(m_f1);
    seleLocalDir = new QLabel("选择本地音乐文件夹");
    seleLocalDir->setStyleSheet("QLabel{font:bold 15px;color:#666666;border:none}");
    seleLocalDir->setFixedSize(145,20);

    m_closeBtn = new QPushButton;
    m_closeBtn->setFixedSize(10,9);
    m_closeBtn->setCursor(Qt::PointingHandCursor);
    m_closeBtn->setStyleSheet("QPushButton{border-image:url(:/images/RightStack/4/close.png)}");

    f1HLayout->setMargin(0);
    f1HLayout->setSpacing(0);
    f1HLayout->addSpacing(20);
    f1HLayout->addWidget(seleLocalDir);
    f1HLayout->addSpacing(100);
    f1HLayout->addWidget(m_closeBtn);

    m_f2 = new QFrame;
    m_f2->setFixedHeight(240);
    m_f2->setStyleSheet("QFrame{background:#ffffff}");
    f2VLayout = new QVBoxLayout(m_f2);
    description = new QLabel("将自动扫描您勾选的目录，文件增删实时同步。");
    description->setFixedSize(250,25);
    description->setStyleSheet("QLabel{border:none}");

    checkList = new QListWidget;
    checkList->setFixedSize(280,180);
    checkList->setFocusPolicy(Qt::NoFocus); //去除选中虚线框
    checkList->setStyleSheet("QListWidget{border:none}"
                             "QListWidget::Item:hover{background:#ffffff}"
                             "QListWidget::item:selected{background:#ffffff}"
                             "QListWidget::item:selected:!active{background:#ffffff}");
    checkList->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent;width:10;height:150;}"
                                                  "QScrollBar::handle{background:#e1e1e2; border:2px solid transparent; border-radius:5px;}"
                                                  "QScrollBar::handle:hover{background:#cfcfd1}"
                                                  "QScrollBar::sub-line{background:transparent}"
                                                  "QScrollBar::add-line{background:transparent}");

    f2VLayout->setSpacing(0);
    f2VLayout->addWidget(description);
    f2VLayout->addWidget(checkList);

    m_f3 = new QFrame;
    m_f3->setFixedHeight(60);
    m_f3->setStyleSheet("QFrame{background:#f5f5f7}");
    f3HLayout = new QHBoxLayout(m_f3);
    m_ackBtn = new QPushButton("确认");
    m_ackBtn->setFixedSize(80,30);
    m_ackBtn->setStyleSheet("QPushButton{background:#0c73c2;color:#ffffff;border-radius:3}");
    m_addDirBtn = new QPushButton("添加文件夹");
    m_addDirBtn->setFixedSize(80,30);
    m_addDirBtn->setStyleSheet("QPushButton{background:#ffffff;border-radius:3}");
    f3HLayout->addWidget(m_ackBtn);
    f3HLayout->addWidget(m_addDirBtn);
    f3HLayout->setMargin(0);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_f1);
    mainLayout->addWidget(m_f2);
    mainLayout->addWidget(m_f3);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    connect(m_closeBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(m_addDirBtn,SIGNAL(clicked(bool)),this,SLOT(slot_addDir()));
}

void SelectDirFrame::mousePressEvent(QMouseEvent *event)
{
    //在标题栏才能改变窗口
    if(QRect(0,0,300,50).contains(event->pos()))
    {
        FramelessAndAutoSize::mousePressEvent(event);
    }
}

void SelectDirFrame::slot_addDir()
{
    QString DirName = QFileDialog::getExistingDirectory(this, tr("打开本地歌曲文件夹"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks);

    if(DirName.isEmpty() || DirList.contains(DirName))
        return;

    QListWidgetItem * item = new QListWidgetItem;
    QCheckBox *checkBox = new QCheckBox;
    checkBox->setText(DirName);
    checkBox->setToolTip(DirName);
    checkList->addItem(item);
    checkList->setItemWidget(item,checkBox);
    checkBox->setChecked(true);
}

void SelectDirFrame::getCheckedState()
{
    int count = checkList->count ();
    for(int i=0; i<count; i++)
    {
         QListWidgetItem *item = checkList->item(i);
         QWidget *widget = checkList->itemWidget(item);
         QCheckBox *box = (QCheckBox*)widget ;
         if(box->isChecked())
             DirList.append(box->text());
    }

}
