#ifndef RENRENTEST_H
#define RENRENTEST_H

#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QWebFrame>
#include <string>
#include <iostream>
#include "include/RRAPI"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include "exchangethread.h"
#include <QThread>
#include "object.h"
#include "statuswidget.h"
#include "downloadfun.h"
#include <QHash>
#include <QTimer>

namespace Ui {
class renrentest;
}

class renrentest : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit renrentest(const QString &m_sessionkey, QWidget *parent = 0);
    ~renrentest();
    QString qfs(string cs);
    void threadExit();
    QString userConstellation(const QString &birthday);
    void setTabbarEnable(int c, bool b);

    void limitClick(int msec);
    bool isAllowRefresh(int type);

public slots:
    void getUserInfo(QVector<UserInfo> userInfoList);
    void getStatus(QVector<StatusInfo> list);
    void setPixmap(QByteArray tmpData);
    void setStatusHead(STATUSID id, QByteArray tmpData);
    void updateUIProgress(qint64 bytesRead, qint64 totalBytes);
    void changeTabState();
    void updateStatus();

    void chageRefresh0();
    void chageRefresh1();
    void chageRefresh2();

signals:
    void changeType(int);

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_publishButton_clicked();

    void on_statusContent_textChanged();



protected:
    void resizeEvent(QResizeEvent *ev);

private:
    Ui::renrentest *ui;
    DownLoadFun *downThread;
    ExchangeThread *exThread;
    QThread downloadthread;
    QThread thread;
    Object download;
    Object obj;
    QProgressBar *progressBar;
    statusWidget *stWidget;
    QHash<STATUSID, statusWidget*> stwHash;
    int tabCurrentIndex;
    QString tiny_head;
    QByteArray headPixBuff;
    bool isallowrefresh0;
    bool isallowrefresh1;
    bool isallowrefresh2;

    QTimer *timer0;
    QTimer *timer1;
    QTimer *timer2;
};

#endif // RENRENTEST_H
