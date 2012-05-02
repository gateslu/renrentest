#ifndef USERSAPI_H
#define USERSAPI_H

#include "Global.h"
#include "Result.h"
#include "Permission.h"
#include <string>
#include <QVector>
#include <QMetaType>

using namespace std;

class  UserInfo
{
public:
    class Hometown
    {
    public:
        string m_country;
        string m_province;
        string m_city;
    };
    class WorkInfo
    {
    public:
        string m_company;
        string m_description;
        string m_startDate;
        string m_endDate;
    };
    class UnivInfo
    {
    public:
        string m_name;
        unsigned long m_year;
        string m_department;
    };
    class HSInfo
    {
    public:
        string m_name;
        unsigned long m_year;
    };

    UID m_uid;
    string m_name;
    bool m_sex;     // male: true; female: false;
    bool m_isStar;
    bool m_isZidou;
    bool m_isVIP;
    string m_birthday;
    string m_emailHash;
    string m_tinyURL;
    string m_headURL;
    string m_mainURL;
    string m_headURLWithLogo;
    string m_tinyURLWithLogo;
    Hometown m_hometown;
    QVector<WorkInfo> m_workHistory;
    QVector<UnivInfo> m_univHistory;
    QVector<HSInfo> m_hsHistory;
};

class Request;

class  UsersAPI
{
public:
    UsersAPI(Request *request);

    Result getLoggedInUser(const string &sessionKey, UID &uid);
    Result getUserInfo(const string &sessionKey, const QVector<string> &uids, QVector<UserInfo> &userInfoList);
    Result hasAppPermission(const string &sessionKey, PERMISSION permission, bool &result);
    Result isAppUser(const string &sessionKey, bool &result);

private:
    Request *m_request;
};

//Q_DECLARE_METATYPE(UserInfo)

#endif  //USERSAPI_H
