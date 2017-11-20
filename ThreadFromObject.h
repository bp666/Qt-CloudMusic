#ifndef THREADFROMOBJECT_H
#define THREADFROMOBJECT_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QRegExp>
#include <QEventLoop>

class ThreadFromObject : public QObject
{
    Q_OBJECT
public:
    explicit ThreadFromObject(QObject *parent = 0);
    ~ThreadFromObject();

signals:
    void sig_searchResult(QVector<QStringList>);

public slots:
    void slot_searchNetSong(QString searchName);

private:
    QVector<QStringList> SongInfos;
    QThread m_thread;
};

#endif // THREADFROMOBJECT_H
