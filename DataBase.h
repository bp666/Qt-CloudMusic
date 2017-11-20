#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>

class DataBase
{
public:
    explicit DataBase();

    void addSongList(int& id, const QString& title, const QString& singer, const QString& cd, const QString& time, const QString& size, const QString& mediaSrc);

    int loadSongList(int& id, QString& title, QString& singer, QString& cd, QString& time, QString& size, QString& mediaSrc);

    void emptyTable();

    QSqlDatabase db;
    QSqlQuery query;
};

#endif // DATABASE_H
