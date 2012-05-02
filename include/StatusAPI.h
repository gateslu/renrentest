#ifndef STATUSAPI_H
#define STATUSAPI_H

#include "Global.h"
#include "Result.h"
#include "Permission.h"
#include <string>
#include <QVector>
#include <string.h>

using namespace std;

class Request;

class  StatusInfo
{
public:
    int m_commentCount;
    string m_message;
    UID m_uid;
    string m_time;
    string m_srcURL;
    STATUSID m_statusId;
    string m_srcName;
    class Place
    {
    public:
        string m_location;
        string m_name;
        LBSID m_lbsId;
        double m_longitude;
        double m_latitude;
        string m_url;
    };
    Place m_place;
};

class  PlaceInfo
{
public:
    enum Privacy {Private = 0, FriendsOnly = 1, Public = 2};
public:
    PLACEID m_placeId;
    double m_placeLongitude;
    double m_placeLatitude;
    double m_gpsLongitude;
    double m_gpsLatitude;
    string m_placeName;
    string m_placeLocation;
    Privacy m_privacy;
};

class  CommentInfo
{
public:
    UID m_uid;
    string m_name;
    string m_tinyURL;
    COMMENTID m_commentId;
    string m_time;
    string m_text;
};

class  StatusAPI
{
public:
    enum CommentOrder {Ascent = 0, Descent = 1};
public:
    StatusAPI(Request *request);

    Result gets(const string &sessionKey, UID uid, int page, int count, QVector<StatusInfo> &list);
    Result set(const string &sessionKey, const string &status, STATUSID forwardId, UID forwardOwnerId, PlaceInfo placeInfo, bool &result);
    Result get(const string &sessionKey, STATUSID statusId, UID ownerId, StatusInfo &status);
    Result getComment(const string &sessionKey, STATUSID statusId, UID ownerId, int page, int count, CommentOrder order, QVector<CommentInfo> &list);

private:
    Request *m_request;
};

#endif  //STATUSAPI_H
