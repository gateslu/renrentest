#include "downloadfun.h"

DownLoadFun::DownLoadFun(QObject *parent) :
    QObject(parent)
{
    reply = 0;
    m_id = 0;
}

void DownLoadFun::httpFinished()
{
    httpBuff.clear();
    httpBuff = reply->readAll();
    if (!httpBuff.isEmpty())
        emit httpData(m_id, httpBuff);
    reply->deleteLater();
    reply = NULL;
}

void DownLoadFun::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    emit updateUIProgress(bytesRead, totalBytes);
}

void DownLoadFun::down(STATUSID id, QString url)
{
    if(reply != NULL)
    {
        reply->abort();
    }

    m_id = id;

    QNetworkAccessManager *manager = new QNetworkAccessManager;
    reply = manager->get(QNetworkRequest(url));

    connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));

    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),
            this,SLOT(updateDataReadProgress(qint64,qint64)));
}
