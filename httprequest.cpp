#include "httprequest.h"

HttpRequest::HttpRequest(QObject *parent) :
    QObject(parent)
{
    m_url = "";
    isLoading = false;
    manager = new QNetworkAccessManager(parent);
}

void HttpRequest::downImage(const QString &url)
{
    if (isLoading)
        return;

    reply = manager->get(QNetworkRequest(QUrl(url)));

    connect(reply,SIGNAL(finished()),this,SLOT(httpFinished()));
    //������ɺ�
    connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead()));
    //�п�������ʱ
    isLoading = true;
}

void HttpRequest::httpFinished()
{
    httpBuff.clear();
    httpBuff = reply->readAll();
    reply = 0;
    emit requestData(httpBuff);
    isLoading = false;
}

void HttpRequest::httpReadyRead()
{
}
