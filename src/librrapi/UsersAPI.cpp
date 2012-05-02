#define RRAPI_LIB_MAIN
#include "../../include/UsersAPI.h"
#include "../libhttp/Http.h"
#include "Config.h"
#include "Method.h"
#include "Utility.h"
#include <json/json.h>
#include <QString>

UsersAPI::UsersAPI(Request *request)
{
//    qRegisterMetaType<UserInfo>("UserInfo");
	m_request = request;
}

Result UsersAPI::getLoggedInUser(const string &sessionKey, UID &uid)
{
	RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
	params.addParam("method",		Method::USERS_GET_LOGGED_IN_USER);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
	params.addParam("session_key",	sessionKey);
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

        uid = root["uid"].asUInt();

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}

Result UsersAPI::getUserInfo(const string &sessionKey, const QVector<string> &uids, QVector<UserInfo> &userInfoList)
{
    if(!uids.size())
        return RESULT_PARAMETER_INVALID;

    string uidsParam;
    for(/*size_t*/int i = 0; i < uids.size(); i++)
        uidsParam += uids.at(i) + ",";
    QString q_uidsParam = QString::fromStdString(uidsParam);
    q_uidsParam = q_uidsParam.left(q_uidsParam.size()-1);
    uidsParam = q_uidsParam.toStdString();

    RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
	params.addParam("method",		Method::USERS_GET_INFO);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
	params.addParam("session_key",	sessionKey);
	params.addParam("format",		Config::m_resultFormat);
    params.addParam("uids",         uidsParam);
    params.addParam("fields",       Config::m_userInfoFields);
	params.addParam("sig",			Utility::getSignature(params));

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
            Json::Value singleUser = root[i];
            UserInfo userInfo;
            userInfo.m_uid = singleUser["uid"].asUInt();
            userInfo.m_name = Utility::UTF8ToString(singleUser["name"].asString());
            userInfo.m_sex = singleUser["sex"].asBool();
            userInfo.m_isStar = singleUser["star"].asBool();
            userInfo.m_isZidou = singleUser["zidou"].asBool();
            userInfo.m_isVIP = singleUser["vip"].asBool();
            userInfo.m_birthday = Utility::UTF8ToString(singleUser["birthday"].asString());
            userInfo.m_emailHash = Utility::UTF8ToString(singleUser["email_hash"].asString());
            userInfo.m_tinyURL = Utility::UTF8ToString(singleUser["tinyurl"].asString());
            userInfo.m_headURL = Utility::UTF8ToString(singleUser["headurl"].asString());
            userInfo.m_mainURL = Utility::UTF8ToString(singleUser["mainurl"].asString());
            userInfo.m_hometown.m_country = Utility::UTF8ToString(singleUser["hometown_location"]["country"].asString());
            userInfo.m_hometown.m_province = Utility::UTF8ToString(singleUser["homwtown_location"]["province"].asString());
            userInfo.m_hometown.m_city = Utility::UTF8ToString(singleUser["hometown_location"]["city"].asString());
            for(unsigned int j = 0; j < singleUser["work_history"].size(); j++)
            {
                Json::Value singleWorkInfo = singleUser["work_history"][j];
                UserInfo::WorkInfo workInfo;
                workInfo.m_company = Utility::UTF8ToString(singleWorkInfo["company_name"].asString());
                workInfo.m_description = Utility::UTF8ToString(singleWorkInfo["description"].asString());
                workInfo.m_startDate = Utility::UTF8ToString(singleWorkInfo["start_date"].asString());
                workInfo.m_endDate = Utility::UTF8ToString(singleWorkInfo["end_date"].asString());
                userInfo.m_workHistory.push_back(workInfo);
            }
            for(unsigned int j = 0; j < singleUser["university_history"].size(); j++)
            {
                Json::Value singleUnivInfo = singleUser["university_history"][j];
                UserInfo::UnivInfo univInfo;
                univInfo.m_name = Utility::UTF8ToString(singleUnivInfo["name"].asString());
                univInfo.m_year = singleUnivInfo["year"].asUInt();
                univInfo.m_department = Utility::UTF8ToString(singleUnivInfo["department"].asString());
                userInfo.m_univHistory.push_back(univInfo);
            }
            for(unsigned int j = 0; j < singleUser["hs_history"].size(); j++)
            {
                Json::Value singleHSInfo = singleUser["hs_history"][j];
                UserInfo::HSInfo hsInfo;
                hsInfo.m_name = Utility::UTF8ToString(singleHSInfo["name"].asString());
                hsInfo.m_year = singleHSInfo["grad_year"].asUInt();
                userInfo.m_hsHistory.push_back(hsInfo);
            }

            userInfoList.push_back(userInfo);
        }

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}

Result UsersAPI::hasAppPermission(const string &sessionKey, PERMISSION permission, bool &result)
{
    RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
	params.addParam("method",		Method::USERS_HAS_APP_PERMISSION);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
	params.addParam("session_key",	sessionKey);
	params.addParam("format",		Config::m_resultFormat);
    params.addParam("ext_perm",     permission);
	params.addParam("sig",			Utility::getSignature(params));

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

Result UsersAPI::isAppUser(const string &sessionKey, bool &result)
{
    RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
	params.addParam("method",		Method::USERS_IS_APP_USER);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
	params.addParam("session_key",	sessionKey);
	params.addParam("format",		Config::m_resultFormat);
	params.addParam("sig",			Utility::getSignature(params));

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
