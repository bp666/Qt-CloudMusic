#ifndef SELECTDIRFRAME_H
#define SELECTDIRFRAME_H


#include "FramelessAndAutoSize.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QGroupBox>
#include <QListWidget>
#include <QListWidgetItem>

class SelectDirFrame : public FramelessAndAutoSize
{
    Q_OBJECT
public:
    explicit SelectDirFrame(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *);

    //文件目录列表
    QStringList DirList;

    //获取qcheckbox选择状态
    void getCheckedState();

    QPushButton *m_ackBtn;//确认按钮

private slots:
    void slot_addDir();

private:
    QFrame *m_f1,*m_f2,*m_f3;
    QLabel *seleLocalDir,*description;
    QPushButton *m_closeBtn, *m_addDirBtn;
    QHBoxLayout *f1HLayout, *f3HLayout;
    QVBoxLayout *f2VLayout, *mainLayout;
    QListWidget *checkList;
};

#endif // SELECTDIRFRAME_H
