#define RRAPI_LIB_MAIN
#include "../../include/StatusAPI.h"
#include "../libhttp/Http.h"
#include "Config.h"
#include "Method.h"
#include "Utility.h"
#include <json/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <QString>

StatusAPI::StatusAPI(Request *request)
{
    m_request = request;
}

Result StatusAPI::gets(const string &sessionKey, UID uid, int page, int count, QVector<StatusInfo> &list)
{
    //    char uidBuf[10];
    //    sprintf_s(uidBuf, 10, "%u", uid);
    string uidBuf;
    uidBuf = QString::number(uid).toStdString();

    //    char pageBuf[10];
    //    sprintf_s(pageBuf, 10, "%d", page);
    string pageBuf;
    pageBuf = QString::number(page).toStdString();

    //    char countBuf[10];
    //    sprintf_s(countBuf, 10, "%d", count);
    string countBuf;
    countBuf = QString::number(count).toStdString();

    RequestParam params;
    params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::STATUS_GETS);
    params.addParam("call_id",		Utility::getCallId());
    params.addParam("v",			Config::m_apiVersion);
    params.addParam("session_key",	sessionKey);
    params.addParam("uid",          uidBuf);
    params.addParam("page",         pageBuf);
    params.addParam("count",        countBuf);
    params.addParam("format",		Config::m_resultFormat);
    params.addParam("sig",			Utility::stringToUTF8(Utility::getSignature(params)));

    Response response;
    m_request->syncRequest(Config::m_RESTServerURL, Request::Post, params, &response);

    Json::Value root;
    Json::Reader reader;
    if(reader.parse(response.getRawData(), root, false))
    {
        if(!root.isArray() && !root["error_code"].isNull())
            return root["error_code"].asUInt();

        for(unsigned int i = 0; i < root.size(); i++)
        {
            Json::Value singleStatusInfo = root[i];
            StatusInfo info;
            info.m_commentCount = singleStatusInfo["comment_count"].asUInt();
            info.m_message = Utility::UTF8ToString(singleStatusInfo["message"].asString());
            info.m_uid = singleStatusInfo["uid"].asUInt();
            info.m_time = Utility::UTF8ToString(singleStatusInfo["time"].asString());
            info.m_srcURL = Utility::UTF8ToString(singleStatusInfo["source_url"].asString());
            info.m_statusId = singleStatusInfo["status_id"].asUInt();
            info.m_srcName = Utility::UTF8ToString(singleStatusInfo["source_name"].asString());
            info.m_place.m_location = Utility::UTF8ToString(singleStatusInfo["place"]["location"].asString());
            info.m_place.m_name = Utility::UTF8ToString(singleStatusInfo["place"]["name"].asString());
            info.m_place.m_lbsId = singleStatusInfo["place"]["lbs_id"].asUInt();
            info.m_place.m_longitude = singleStatusInfo["place"]["longitude"].asDouble();
            info.m_place.m_latitude = singleStatusInfo["place"]["latitude"].asDouble();
            info.m_place.m_url = Utility::UTF8ToString(singleStatusInfo["place"]["url"].asString());
            list.push_back(info);
        }

        return RESULT_OK;
    }
    else
        return RESULT_JSON_INVALID;
}

Result StatusAPI::set(const string &sessionKey, const string &status, STATUSID forwardId, UID forwardOwnerId, PlaceInfo placeInfo, bool &result)
{
    //    char forwardIdBuf[20];
    //    sprintf_s(forwardIdBuf, 20, "%u", forwardId);
    string forwardIdBuf;
    forwardIdBuf = QString::number(forwardId).toStdString();

    //    char forwardOwnerIdBuf[20];
    //    sprintf_s(forwardOwnerIdBuf, 20, "%u", forwardOwnerId);
    string forwardOwnerIdBuf;
    forwardOwnerIdBuf = QString::number(forwardOwnerId).toStdString();

    /*
        char placeInfoBuf[1024];
        sprintf(placeInfoBuf,
                "{ \
                \"place_id\":%u, \
                \"place_longitude\":%f, \
                \"place_latitude\":%f, \
                \"gps_longitude\":%f, \
                \"gps_latitude\":%f, \
                \"place_name\":%s, \
                \"place_location\":%s, \
                \"privacy\":%d \
                \"}",
                placeInfo.m_placeId,
                placeInfo.m_placeLongitude,
                placeInfo.m_placeLatitude,
                placeInfo.m_gpsLongitude,
                placeInfo.m_gpsLatitude,
                placeInfo.m_placeName,
                placeInfo.m_placeLocation,
                (int)placeInfo.m_privacy);*/

    string placeInfoBuf;
    QString m_placeInfoBuf;
    m_placeInfoBuf = QString(
                "{ "
                "\"place_id\":%1, "
                "\"place_longitude\":%2, "
                "\"place_latitude\":%3, "
                "\"gps_longitude\":%4, "
                "\"gps_latitude\":%5, "
                "\"place_name\":%6, "
                "\"place_location\":%7, "
                "\"privacy\":%8 "
                "}")
            .arg(QString::number(placeInfo.m_placeId))
            .arg(QString::number(placeInfo.m_placeLongitude))
            .arg(QString::number(placeInfo.m_placeLatitude))
            .arg(QString::number(placeInfo.m_gpsLongitude))
            .arg(QString::number(placeInfo.m_gpsLatitude))
            .arg(QString::fromStdString(placeInfo.m_placeName))
            .arg(QString::fromStdString(placeInfo.m_placeLocation))
            .arg(QString::number((int)placeInfo.m_privacy));

    placeInfoBuf = m_placeInfoBuf.toStdString();

    RequestParam params;
    params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::STATUS_SET);
    params.addParam("call_id",		Utility::getCallId());
    params.addParam("v",			Config::m_apiVersion);
    params.addParam("session_key",	sessionKey);
    params.addParam("status",       Utility::stringToUTF8(status));
    params.addParam("format",		Config::m_resultFormat);
    params.addParam("forward_id",   forwardIdBuf);
    params.addParam("forward_owner",forwardOwnerIdBuf);
    params.addParam("place_data",   placeInfoBuf);
    params.addParam("sig",			Utility::stringToUTF8(Utility::getSignature(params)));

    Response response;
    m_request->syncRequest(Config::m_RESTServerURL, Request::Post, params, &response);

    Json::Value root;
    Json::Reader reader;
    if(reader.parse(response.getRawData(), root, false))
    {
        if(!root["error_code"].isNull())
            return root["error_code"].asUInt();

        result = root["result"].asBool();

        return RESULT_OK;
    }
    else
        return RESULT_JSON_INVALID;
}

Result StatusAPI::get(const string &sessionKey, STATUSID statusId, UID ownerId, StatusInfo &status)
{
    //    char statusIdBuf[10];
    //    sprintf_s(statusIdBuf, 10, "%u", statusId);
    string statusIdBuf;
    statusIdBuf = QString::number(statusId).toStdString();

    //    char ownerIdBuf[10];
    //    sprintf_s(ownerIdBuf, 10, "%u", ownerId);
    string ownerIdBuf;
    ownerIdBuf = QString::number(ownerId).toStdString();

    RequestParam params;
    params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::STATUS_GET);
    params.addParam("call_id",		Utility::getCallId());
    params.addParam("v",			Config::m_apiVersion);
    params.addParam("session_key",	sessionKey);
    params.addParam("status_id",    statusIdBuf);
    params.addParam("owner_id",     ownerIdBuf);
    params.addParam("format",		Config::m_resultFormat);
    params.addParam("sig",			Utility::stringToUTF8(Utility::getSignature(params)));

    Response response;
    m_request->syncRequest(Config::m_RESTServerURL, Request::Post, params, &response);

    Json::Value root;
    Json::Reader reader;
    if(reader.parse(response.getRawData(), root, false))
    {
        if(!root["error_code"].isNull())
            return root["error_code"].asUInt();

        status.m_commentCount = root["comment_count"].asUInt();
        status.m_message = root["message"].asString();
        status.m_uid = root["uid"].asUInt();
        status.m_time = root["time"].asString();
        status.m_srcURL = root["source_url"].asString();
        status.m_statusId = root["status_id"].asUInt();
        status.m_srcName = root["source_name"].asString();
        status.m_place.m_location = root["place"]["location"].asString();
        status.m_place.m_name = root["place"]["name"].asString();
        status.m_place.m_lbsId = root["place"]["lbs_id"].asUInt();
        status.m_place.m_longitude = root["place"]["longitude"].asDouble();
        status.m_place.m_latitude = root["place"]["latitude"].asDouble();
        status.m_place.m_url = root["place"]["url"].asString();

        return RESULT_OK;
    }
    else
        return RESULT_JSON_INVALID;
}

Result StatusAPI::getComment(const string &sessionKey, STATUSID statusId, UID ownerId, int page, int count, CommentOrder order, QVector<CommentInfo> &list)
{
    //    char statusIdBuf[10];
    //    sprintf_s(statusIdBuf, 10, "%u", statusId);
    string statusIdBuf;
    statusIdBuf = QString::number(statusId).toStdString();

    //    char ownerIdBuf[10];
    //    sprintf_s(ownerIdBuf, 10, "%u", ownerId);
    string ownerIdBuf;
    ownerIdBuf = QString::number(ownerId).toStdString();

    //    char pageBuf[10];
    //    sprintf_s(pageBuf, 10, "%d", page);
    string pageBuf;
    pageBuf = QString::number(page).toStdString();

    //    char countBuf[10];
    //    sprintf_s(countBuf, 10, "%d", count);
    string countBuf;
    countBuf = QString::number(count).toStdString();

    RequestParam params;
    params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::STATUS_GET_COMMENT);
    params.addParam("call_id",		Utility::getCallId());
    params.addParam("v",			Config::m_apiVersion);
    params.addParam("session_key",	sessionKey);
    params.addParam("status_id",    statusIdBuf);
    params.addParam("owner_id",     ownerIdBuf);
    params.addParam("format",		Config::m_resultFormat);
    params.addParam("page",         pageBuf);
    params.addParam("count",        countBuf);
    params.addParam("order",        Ascent == order ? "0" : "1");
    params.addParam("sig",			Utility::stringToUTF8(Utility::getSignature(params)));

    Response response;
    m_request->syncRequest(Config::m_RESTServerURL, Request::Post, params, &response);

    Json::Value root;
    Json::Reader reader;
    if(reader.parse(response.getRawData(), root, false))
    {
        if(!root.isArray() && !root["error_code"].isNull())
            return root["error_code"].asUInt();

        for(unsigned int i = 0; i < root.size(); i++)
        {
            Json::Value singleCommentInfo = root[i];
            CommentInfo info;
            info.m_uid = singleCommentInfo["uid"].asUInt();
            info.m_name = Utility::UTF8ToString(singleCommentInfo["name"].asString());
            info.m_tinyURL = Utility::UTF8ToString(singleCommentInfo["tinyurl"].asString());
//            info.m_commentId = singleCommentInfo["comment_id"].asUInt();
            info.m_time = singleCommentInfo["time"].asString();
            info.m_text = Utility::UTF8ToString(singleCommentInfo["text"].asString());
            list.push_back(info);
        }

        return RESULT_OK;
    }
    else
        return RESULT_JSON_INVALID;
}
