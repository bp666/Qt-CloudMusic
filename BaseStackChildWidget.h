#ifndef BASESTACKCHILDWIDGET_H
#define BASESTACKCHILDWIDGET_H

#include <QWidget>
#include <QPainter>

class BaseStackChildWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseStackChildWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // BASESTACKCHILDWIDGET_H
