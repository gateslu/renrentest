#define RRAPI_LIB_MAIN
#include "../../include/NotificationsAPI.h"
#include "../libhttp/Http.h"
#include "Config.h"
#include "Method.h"
#include "Utility.h"
#include <json/json.h>
#include <QString>

NotificationsAPI::NotificationsAPI(Request *request)
{
    m_request = request;
}

Result NotificationsAPI::send(const string &sessionKey, const QVector<UID> &toList, const string &content, bool &result)
{
    if(toList.size() >= 20)
    {
        result = false;
        return RESULT_NOTIFICATIONS_TOO_MANY;
    }

    string toListString;
    for(/*size_t*/int i = 0; i < toList.size(); i++)
    {
//        char buf[20];
//        sprintf_s(buf, 20, "%u,", toList[i]);
        string buf;
        buf = QString::number(toList[i]).toStdString();
        toListString.append(buf);
    }
    QString q_toListString = QString::fromStdString(toListString);
    q_toListString = q_toListString.left(q_toListString.size()-1);
    toListString = q_toListString.toStdString();

	RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::ADMIN_GET_ALLOCATION);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
	params.addParam("format",		Config::m_resultFormat);
    params.addParam("session_key",  sessionKey);
    params.addParam("to_ids",       toListString);
    params.addParam("notification", content);
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

Result NotificationsAPI::sendEmail(const string &sessionKey, int templateId, const QVector<UID> &recipients, const string &contentInJSON, UID fromUID, QVector<UID> &successList)
{
    if(recipients.size() > 100)
        return RESULT_NOTIFICATIONS_TOO_MANY;

    string recipientsString;
    for(/*size_t*/int i = 0; i < recipients.size(); i++)
    {
//        char buf[20];
//        sprintf_s(buf, 20, "%u,", recipients[i]);
        string buf;
        buf = QString::number(recipients[i]).toStdString();
        recipientsString.append(buf);
    }
    QString q_recipientsString = QString::fromStdString(recipientsString);
    q_recipientsString = q_recipientsString.left(q_recipientsString.size()-1);
    recipientsString = q_recipientsString.toStdString();

//    char templateIdString[20];
//    sprintf_s(templateIdString, 20, "%d", templateId);
    string templateIdString;
    templateIdString = QString::number(templateId).toStdString();

//    char fromUIDString[20];
//    sprintf_s(fromUIDString, 20, "%u", fromUID);
    string fromUIDString;
    fromUIDString = QString::number(fromUID).toStdString();

	RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::ADMIN_GET_ALLOCATION);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
	params.addParam("format",		Config::m_resultFormat);
    params.addParam("session_key",  sessionKey);
    params.addParam("template_id",  templateIdString);
    params.addParam("recipients",   recipientsString);
    params.addParam("template_data",contentInJSON);
    params.addParam("uid",          fromUIDString);
	params.addParam("sig",			Utility::stringToUTF8(Utility::getSignature(params)));

	Response response;
	m_request->syncRequest(Config::m_RESTServerURL, Request::Post, params, &response);

	Json::Value root;
	Json::Reader reader;
    if(reader.parse(response.getRawData(), root, false))
	{
        if(!root["error_code"].isNull())
            return root["error_code"].asUInt();

        string uids = root["uids"].asString();
        string::size_type offset = 0;
        while(uids.find(',', offset) != uids.npos)
        {
            UID uid = atol(uids.substr(offset, uids.find(',', offset)).c_str());
            successList.push_back(uid);
        }
        UID uid = atol(uids.substr(offset).c_str());
        successList.push_back(uid);

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}
