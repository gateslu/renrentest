#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include "Global.h"
#include "Result.h"
#include "Permission.h"
#include <string>
#include <QVector>

using namespace std;

class Request;

class  NotificationsAPI
{
public:
    NotificationsAPI(Request *request);

    Result send(const string &sessionKey, const QVector<UID> &toList, const string &content, bool &result);
    Result sendEmail(const string &sessionKey, int templateId, const QVector<UID> &toList, const string &contentInJSON, UID from, QVector<UID> &successList);

private:
    Request *m_request;
};

#endif  //NOTIFICATIONS_H
