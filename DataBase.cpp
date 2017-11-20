#include "DataBase.h"
#include <QVariant>

DataBase::DataBase()
{
    //如果已连接数据库，则继续操作，不然多次连接同一个数据库会有警告
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("SongInfoBase.db");

    db.open();
    db.exec(QString("CREATE TABLE IF NOT EXISTS songinfo(id int primary key, title varchar(255), singer varchar(255), cd varchar(255), time varchar(255), size int, mediaSrc varchar(255))"));
    query = QSqlQuery(db);
}

void DataBase::addSongList(int& id, const QString& title, const QString& singer, const QString& cd, const QString& time, const QString& size, const QString& mediaSrc)
{
    query.prepare(QString("INSERT INTO songinfo(id, title, singer, cd, time, size, mediaSrc) VALUES (:id, :title, :singer, :cd, :time, :size, :mediaSrc)"));
    query.bindValue(":id", id);
    query.bindValue(":title", title);
    query.bindValue(":singer", singer);
    query.bindValue(":cd", cd);
    query.bindValue(":time", time);
    query.bindValue(":size", size);
    query.bindValue(":mediaSrc", mediaSrc);
    query.exec();
}

int DataBase::loadSongList(int& id, QString& title, QString& singer, QString& cd, QString& time, QString& size, QString& mediaSrc)
{
    query.exec(QString("SELECT * FROM songinfo order by id"));
    if(!query.next())
        return 0;
    id = query.value("id").toInt();
    title = query.value("title").toString();
    singer = query.value("singer").toString();
    cd = query.value("cd").toString();
    time = query.value("time").toString();
    size = query.value("size").toString();
    mediaSrc = query.value("mediaSrc").toString();
    return 1;
}

void DataBase::emptyTable()
{
    query.exec(QString("delete from songinfo"));
}

