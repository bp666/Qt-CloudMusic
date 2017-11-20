#include "ThreadFromObject.h"

ThreadFromObject::ThreadFromObject(QObject *parent) : QObject(parent)
{
    this->moveToThread(&m_thread);
    m_thread.start();
}

ThreadFromObject::~ThreadFromObject()
{
    if(m_thread.isRunning())
    {
        m_thread.terminate();
        m_thread.wait();
    }
}

void ThreadFromObject::slot_searchNetSong(QString searchName)
{
    QUrl url;
    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply;

    //1.通过搜索娶歌曲找出各歌曲hash
    QString curUrlStr = QString("http://songsearch.kugou.com/song_search_v2?callback=jQuery191005998896165458123_1500911077658&keyword=%1").arg(searchName);
    url.setUrl(curUrlStr);

    //2.通过hash获取歌曲各信息
    const QString hashURLSTR ="http://www.kugou.com/yy/index.php?r=play/getdata&hash=";

    reply = manager.get(QNetworkRequest(url));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QString codeContent = reply->readAll();

    QRegExp re("\"total.{2}(\\d*)");

    //获取歌曲总数
    re.indexIn(codeContent);
    QString TotalStr = re.cap(1);
    int iTotalSize = TotalStr.toInt();

    //获取每页歌曲数
    re.setPattern("pagesize.{2}(\\d*)");
    re.indexIn(codeContent);
    QString PageSizeStr = re.cap(1);
    int iPageSize = PageSizeStr.toInt();

    //页数
    int iPage = 0;
    if(iTotalSize % iPageSize != 0)
        iPage = iTotalSize / iPageSize + 1;
    else
        iPage = iTotalSize / iPageSize;

    //限制最多为1页,一页20首， 太多加载太慢了
    if(iPage>1)
        iPage = 1;

    SongInfos.clear();

    for(int z=1;z<=iPage;z++)
    {
        QString UrlBufStr = curUrlStr+"&page="+QChar(z);

        reply = manager.get(QNetworkRequest(UrlBufStr));
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        QString codeContentBuf = reply->readAll();

        QStringList HashStrList;
        //获取各歌曲的Hash值
        //不把查找条件去除将无限循环
        while (codeContentBuf.indexOf("\"FileHash\":\"") != -1)
        {
            int idx = codeContentBuf.indexOf("\"FileHash\":\"");
            //去除查找条件 "FileHash":" 长度为12 Hash值长32
            codeContentBuf = codeContentBuf.replace(idx,12,"");
            QString HashStr = codeContentBuf.mid(idx, 32);
            if(!HashStrList.contains(HashStr))
                HashStrList.append(HashStr);
        }

        //合并为完整的搜索Hash网址
        QStringList HashUrlList;
        for(int i=0;i<HashStrList.count();i++)
        {
            HashUrlList.append(hashURLSTR + HashStrList.at(i));
        }

        for(int j=0; j<HashUrlList.count(); j++)
        {
            QUrl hashUrl(HashUrlList.at(j));
            reply = manager.get(QNetworkRequest(hashUrl));
            QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();

            //hash网页的源码为unicode值 需转换
            QString HashContent = reply->readAll();

            //Unicode转汉字
            while (HashContent.indexOf("\\u") != -1)
            {
                int idx = HashContent.indexOf("\\u");
                //获取Unicode \u5468
                QString strHex = HashContent.mid(idx, 6);
                //把\u去掉
                strHex = strHex.replace("\\u", QString());
                //把5468作为16进制转为十进制21608
                int nHex = strHex.toInt(0, 16);
                //QChar(21608)转为utf8
                HashContent.replace(idx, 6, QChar(nHex));
            }

            QStringList songInfo;

            //歌曲信息
            re.setPattern("audio_name.{3}(.*)\",\"have_album");
            re.indexIn(HashContent);

            QString SongInfoStr = re.cap(1);
            QString SingerStr = SongInfoStr.section(" - ",0,0);
//0.歌手
            songInfo.append(SingerStr);
            QString SongNameStr = SongInfoStr.section(" - ",1,1);
//1.歌曲名称
            songInfo.append(SongNameStr);

            //歌曲时长
            re.setPattern("timelength.{2}(\\d*)");
            re.indexIn(HashContent);

            QString SongTimeStr = re.cap(1);
            int seconds = SongTimeStr.toInt() / 1000 % 60;
            int minutes = (SongTimeStr.toInt() / 1000 - seconds) / 60;

            SongTimeStr = QString::number(minutes)+":"+QString("%1").arg(seconds, 2, 10, QChar('0'));
//2.歌曲时长
            songInfo.append(SongTimeStr);

            //音源
            re.setPattern("play_url.{3}(.*.mp3)");
            re.indexIn(HashContent);

            QString SongSrcStr = re.cap(1);
            SongSrcStr.replace("\\","");
//3.音源
            songInfo.append(SongSrcStr);

            SongInfos.append(songInfo);
        }
    }
    emit sig_searchResult(SongInfos);
}

