#define RRAPI_LIB_MAIN
#include "../../include/InvitationsAPI.h"
#include "../libhttp/Http.h"
#include "Config.h"
#include "Method.h"
#include "Utility.h"
#include <json/json.h>
#include <QString>

InvitationsAPI::InvitationsAPI(Request *request)
{
    m_request = request;
}

Result InvitationsAPI::createLink(const string &sessionKey, string &link)
{
	RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::ADMIN_GET_ALLOCATION);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
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

        link = root[(unsigned int)0].asString();

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}

Result InvitationsAPI::getInfoByInviteeUID(const string &sessionKey, UID inviteeUID, QVector<InvitationInfo> &list)
{
//    char inviteeUIDBuf[20];
//    sprintf_s(inviteeUIDBuf, 20, "%u", inviteeUID);
    string inviteeUIDBuf;
    inviteeUIDBuf = QString::number(inviteeUID).toStdString();

	RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::ADMIN_GET_ALLOCATION);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
	params.addParam("format",		Config::m_resultFormat);
    params.addParam("invitee_id",   inviteeUIDBuf);
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
            InvitationInfo info;
            info.m_type = root[i]["invite_type"].asInt() ? InvitationInfo::Inside : InvitationInfo::Outside;
            info.m_inviterUID = root[i]["inviter_uid"].asUInt();
            info.m_inviteTime = root[i]["invite_time"].asString();
            info.m_inviteeUID = root[i]["invitee_uid"].asUInt();
            list.push_back(info);
        }

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}

Result InvitationsAPI::getInfoByTime(const string &sessionKey, const string &beginTime, const string &endTime, QVector<InvitationInfo> &list)
{
	RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::ADMIN_GET_ALLOCATION);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
	params.addParam("format",		Config::m_resultFormat);
    params.addParam("begin_time",   beginTime);
    params.addParam("end_time",     endTime);
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
            InvitationInfo info;
            info.m_type = root[i]["invite_type"].asInt() ? InvitationInfo::Inside : InvitationInfo::Outside;
            info.m_inviterUID = root[i]["inviter_uid"].asUInt();
            info.m_inviteTime = root[i]["invite_time"].asString();
            info.m_inviteeUID = root[i]["invitee_uid"].asUInt();
            list.push_back(info);
        }

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}
