#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>

class HttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequest(QObject *parent = 0);
    void downImage(const QString& url);
    void setUrl(const QString& url)
    {
        m_url = url;
    }

signals:
    void requestData(QByteArray tmpData);
    
public slots:
    void httpFinished();
    void httpReadyRead();
    
private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    bool isLoading;
    QByteArray httpBuff;
    QString m_url;
};

#endif // HTTPREQUEST_H
