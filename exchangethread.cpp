#include "exchangethread.h"
#include <QMetaType>

ExchangeThread::ExchangeThread(const QString &sk, QObject *parent) :
    QObject(parent)
{
    statusContent = "";
    isExchanging = false;
    isLoading = false;
    reply = 0;
    sessionKey = sk.toStdString();
    //    sessionKey = "6.c757661bf410e6d36599907b0380a22a.2592000.1335405600-448992126";
    //    sessionKey = "6.a99bb66a4b2e95ffa43d1506c8e7e200.2592000.1337446800-450631571";

    api = new RenRenAPI;

    initThread(sessionKey);
}

void ExchangeThread::initThread(string sk)
{
    bool isAppuser = false;
    api->m_usersAPI->isAppUser(sk, isAppuser);
    qDebug() << isAppuser;
    if (!isAppuser)
        return;

    UID uid;
    api->m_usersAPI->getLoggedInUser(sk, uid);

    char t[256];

    sprintf(t, "%lu", uid);
    str_uid = t;

    m_infoType = 0;
}

QString ExchangeThread::qfs(string cs)
{
    return QString::fromStdString(cs);
}

//获取用户基本信息
void ExchangeThread::getUserInfo()
{
    QVector<string> uids;
    uids.push_back(str_uid);
    QVector<UserInfo> userInfoList;
    m_result = api->m_usersAPI->getUserInfo(sessionKey, uids, userInfoList);
    if (m_result != RESULT_OK)
        return;
    //    qDebug() << qfs(userInfoList.at(0).m_mainURL);
    downImage(qfs(userInfoList.at(0).m_mainURL));
    emit s_userInfoList(userInfoList);
    //    downImage("http://head.xiaonei.com/photos/0/0/men_main.gif");  //http://head.xiaonei.com/photos/0/0/men_main.gif
}

//获取用户状态
void ExchangeThread::getStatus()
{
    QVector<StatusInfo> list;
    UID m_uid = qfs(str_uid).toULong();
    m_result = api->m_statusAPI->gets(sessionKey, m_uid, 1, 10, list);
    if (m_result != RESULT_OK)
        return;
    emit s_getStatus(list);
    //    qDebug() << list.size();
    //    for (int i = 0; i < list.size(); i++)
    //    {
    //        qDebug() << "*****************************";
    //        qDebug() << qfs(list.at(i).m_message);
    //        qDebug() << list.at(i).m_commentCount;;
    //        qDebug() << qfs(list.at(i).m_time);
    ////        qDebug() << list.at(i).m_place;
    //        qDebug() << qfs(list.at(i).m_srcName);
    //        qDebug() << qfs(list.at(i).m_srcURL);
    //        qDebug() << list.at(i).m_statusId;
    //        qDebug() << list.at(i).m_uid;
    //        qDebug() << "*****************************";
    //        if (list.at(i).m_commentCount > 0)
    //        {
    //            QVector<CommentInfo> commentList;
    //            api->m_statusAPI->getComment(sessionKey, list.at(i).m_statusId, list.at(i).m_uid, 1, 10, api->m_statusAPI->Ascent, commentList);
    //            if (m_result != RESULT_OK)
    //                return;
    //            for (int i = 0; i < commentList.size(); i++)
    //            {
    //                qDebug() << "#############################";
    ////                qDebug() << qfs(commentList.at(i).m_commentId);
    //                qDebug() << qfs(commentList.at(i).m_name);
    //                qDebug() << qfs(commentList.at(i).m_text);
    //                qDebug() << qfs(commentList.at(i).m_time);
    //                qDebug() << qfs(commentList.at(i).m_tinyURL);
    //                qDebug() << commentList.at(i).m_uid;
    //                qDebug() << "#############################";
    //            }
    //        }
    //    }
}

void ExchangeThread::setStatus()
{
    string cstr = statusContent.toStdString();
    UID m_uid = qfs(str_uid).toULong();
    bool result = false;
    STATUSID forwardId = 0;
    PlaceInfo placeInfo;
    placeInfo.m_gpsLatitude = 0;
    placeInfo.m_gpsLongitude = 0;
    placeInfo.m_placeId = 0;
    placeInfo.m_placeLatitude = 0;
    placeInfo.m_placeLocation = "";
    placeInfo.m_placeLongitude = 0;
    placeInfo.m_placeName = "";
    placeInfo.m_privacy = PlaceInfo::Private;
    api->m_statusAPI->set(sessionKey, cstr, forwardId, m_uid, placeInfo, result);
    qDebug() << result;
    if (result)
    {
        emit s_updateStatusOK();
    }
}

void ExchangeThread::downImage(const QString &url)
{
    qDebug() << "start download";
    manager = new QNetworkAccessManager;
//    QNetworkAccessManager *manager = new QNetworkAccessManager;
    reply = manager->get(QNetworkRequest(url));

    connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));

    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),
            this,SLOT(updateDataReadProgress(qint64,qint64)));

    //下载完成后
    isLoading = true;
}

void ExchangeThread::exchangeData(int type)
{
    switch (type)
    {
    case 1:
        qDebug() << "tab1";
        getUserInfo();
        break;
    case 2:
        qDebug() << "tab2";
        getStatus();
        break;
    case 3:
        qDebug() << "tab3";
        break;
    case 1000:
        qDebug() << "publish";
        setStatus();
        break;
    default:
        break;
    }
}

void ExchangeThread::setStatusContent(const QString &content)
{
    statusContent = content;
}

void ExchangeThread::httpFinished()
{
    httpBuff.clear();
    httpBuff = reply->readAll();
    qDebug() << "httpBuff = " << httpBuff;
    if (!httpBuff.isEmpty())
        emit httpData(httpBuff);
    reply->deleteLater();
    reply = NULL;
    qDebug() << "httpFinished";
}

void ExchangeThread::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    emit updateUIProgress(bytesRead, totalBytes);
}

void ExchangeThread::infoType(int type)
{
    qDebug()<<"from thread slot:" << QThread::currentThreadId();
    qDebug() << "stop thread";
    if(reply != NULL)
    {
        reply->abort();
    }
    exchangeData(type);
}
