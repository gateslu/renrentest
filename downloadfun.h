#ifndef DOWNLOADFUN_H
#define DOWNLOADFUN_H

#include <QObject>
#include <QtCore>
#include <QApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "include/RRAPI"

#define ser 4

class DownLoadFun : public QObject
{
    Q_OBJECT
public:
    explicit DownLoadFun(QObject *parent = 0);
    
signals:
    void httpData(STATUSID, QByteArray);
    void updateUIProgress(qint64 bytesRead,qint64 totalBytes);

public slots:
    void httpFinished();
    void updateDataReadProgress(qint64 bytesRead,qint64 totalBytes);
    void down(STATUSID id, QString url);
    
private:
    QNetworkReply *reply;
    QByteArray httpBuff;
    STATUSID m_id;
};

#endif // DOWNLOADFUN_H
