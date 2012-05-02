#ifndef FRIENDSAPI_H
#define FRIENDSAPI_H

#include "Global.h"
#include "Result.h"
#include "Permission.h"
#include <string>
#include <QVector>

using namespace std;

class Request;
class UserInfo;

class  AreFriendsInfo
{
public:
    UID m_uid1;
    UID m_uid2;
    bool m_areFriends;
};

class  FriendsAPI
{
public:
    FriendsAPI(Request *request);

    Result areFriends(const string &sessionKey, const QVector<UID> &group1, const QVector<UID> &group2, QVector<AreFriendsInfo> &list);
    Result get(const string &sessionKey, int page, int count, QVector<UID> &list);
    Result getFriends(const string &sessionKey, int page, int count, QVector<UserInfo> &list);
    Result getAppFriends(const string &sessionKey, QVector<UserInfo> &list);

private:
    Request *m_request;
};

#endif  //FRIENDSAPI_H
