#ifndef EXCHANGETHREAD_H
#define EXCHANGETHREAD_H

#include <QtCore>
#include <QApplication>
#include <string>
#include <iostream>
#include "include/RRAPI"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

class ExchangeThread : public QObject
{
    Q_OBJECT
public:
    explicit ExchangeThread(const QString &sk, QObject *parent = 0);
    void initThread(string sk);
    QString qfs(string cs);

    void downImage(const QString& url);
    void exchangeData(int type);
    void setStatusContent(const QString& content);

private:
    void getUserInfo();
    void getStatus();
    void setStatus();

signals:
    void s_userInfoList(QVector<UserInfo>);
    void s_getStatus(QVector<StatusInfo>);
    void s_updateStatusOK();

    void httpData(QByteArray);
    void updateUIProgress(qint64 bytesRead,qint64 totalBytes);
    
public slots:
    void httpFinished();
    void updateDataReadProgress(qint64 bytesRead,qint64 totalBytes);
    void infoType(int type);
    
private:
    RenRenAPI *api;
    Result m_result;
    string sessionKey;
    string str_uid;
    int m_infoType;
    QApplication *app;
    QNetworkReply *reply;
    bool isExchanging;
    bool isLoading;
    QByteArray httpBuff;
    QString statusContent;
    QNetworkAccessManager *manager;
};

#endif // EXCHANGETHREAD_H
