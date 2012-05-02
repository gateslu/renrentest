#define RRAPI_LIB_MAIN
#include "../../include/FriendsAPI.h"
#include "../../include/UsersAPI.h"
#include "../libhttp/Http.h"
#include "Config.h"
#include "Method.h"
#include "Utility.h"
#include <json/json.h>
#include <QString>

FriendsAPI::FriendsAPI(Request *request)
{
    m_request = request;
}

Result FriendsAPI::areFriends(const string &sessionKey, const QVector<UID> &group1, const QVector<UID> &group2, QVector<AreFriendsInfo> &list)
{
    if(!group1.size() || !group2.size() || group1.size() != group2.size())
        return RESULT_PARAMETER_INVALID;

    string group1Param, group2Param;
    for(/*size_t*/int i = 0; i < group1.size(); i++)
    {
        string buf;
//        char buf[20];
//        sprintf_s(buf, 20, "%u,", group1[i]);
        buf = QString::number(group1[i]).toStdString();
        group1Param += buf;

//        sprintf_s(buf, 20, "%u,", group2[i]);
        buf = QString::number(group2[i]).toStdString();
        group2Param += buf;
    }
    QString q_group1Param = QString::fromStdString(group1Param);
    q_group1Param = q_group1Param.left(q_group1Param.size()-1);
    group1Param = q_group1Param.toStdString();

    QString q_group2Param = QString::fromStdString(group2Param);
    q_group2Param = q_group2Param.left(q_group2Param.size()-1);
    group2Param = q_group2Param.toStdString();

	RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::FRIENDS_ARE_FRIENDS);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
	params.addParam("session_key",	sessionKey);
    params.addParam("uids1",        group1Param);
    params.addParam("uids2",        group2Param);
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
            Json::Value singleAreFriendsInfo = root[i];
            AreFriendsInfo info;
            info.m_uid1 = singleAreFriendsInfo["uid1"].asUInt();
            info.m_uid2 = singleAreFriendsInfo["uid2"].asUInt();
            info.m_areFriends = singleAreFriendsInfo["are_friends"].asBool();
            list.push_back(info);
        }

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}

Result FriendsAPI::get(const string &sessionKey, int page, int count, QVector<UID> &list)
{
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
    params.addParam("method",		Method::FRIENDS_GET);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
	params.addParam("session_key",	sessionKey);
	params.addParam("format",		Config::m_resultFormat);
    params.addParam("page",         pageBuf);
    params.addParam("count",        countBuf);
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
            list.push_back(root[i].asUInt());

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}

Result FriendsAPI::getFriends(const string &sessionKey, int page, int count, QVector<UserInfo> &list)
{
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
    params.addParam("method",		Method::FRIENDS_GET_FRIENDS);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
	params.addParam("session_key",	sessionKey);
	params.addParam("format",		Config::m_resultFormat);
    params.addParam("page",         pageBuf);
    params.addParam("count",        countBuf);
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
            Json::Value singleUserInfo = root[i];
            UserInfo userInfo;
            userInfo.m_uid = singleUserInfo["id"].asUInt();
            userInfo.m_name = singleUserInfo["name"].asString();
            userInfo.m_headURL = singleUserInfo["headurl"].asString();
            userInfo.m_headURLWithLogo = singleUserInfo["headurl_with_logo"].asString();
            userInfo.m_tinyURLWithLogo = singleUserInfo["tinyurl_with_logo"].asString();
            list.push_back(userInfo);
        }

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}

Result FriendsAPI::getAppFriends(const string &sessionKey, QVector<UserInfo> &list)
{
	RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::FRIENDS_GET_APP_FRIENDS);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
	params.addParam("session_key",	sessionKey);
	params.addParam("format",		Config::m_resultFormat);
    params.addParam("fields",		Config::m_appFriendsFields);
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
            Json::Value singleUserInfo = root[i];
            UserInfo userInfo;
            userInfo.m_uid = singleUserInfo["uid"].asUInt();
            userInfo.m_name = singleUserInfo["name"].asString();
            userInfo.m_headURL = singleUserInfo["headurl"].asString();
            userInfo.m_tinyURL = singleUserInfo["tinyurl"].asString();
            list.push_back(userInfo);
        }

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}
