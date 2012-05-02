#define RRAPI_LIB_MAIN
#include "../../include/PagesAPI.h"
#include "../libhttp/Http.h"
#include "Config.h"
#include "Method.h"
#include "Utility.h"
#include <json/json.h>
#include <QString>

PagesAPI::PagesAPI(Request *request)
{
    m_request = request;
}

Result PagesAPI::isFan(const string &sessionKey, UID uid, PAGEID pageId, bool &result)
{
//    char uidString[20];
//    sprintf_s(uidString, 20, "%u", uid);
    string uidString;
    uidString = QString::number(uid).toStdString();
    
//    char pageIdString[20];
//    sprintf_s(pageIdString, 20, "%u", pageId);
    string pageIdString;
    pageIdString = QString::number(pageId).toStdString();

    RequestParam params;
    params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::ADMIN_GET_ALLOCATION);
    params.addParam("call_id",		Utility::getCallId());
    params.addParam("v",		Config::m_apiVersion);
    params.addParam("format",		Config::m_resultFormat);
    params.addParam("uid",              uidString);
    params.addParam("page_id",          pageIdString);
    params.addParam("sig",		Utility::stringToUTF8(Utility::getSignature(params)));

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
