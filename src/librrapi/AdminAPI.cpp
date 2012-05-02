#define RRAPI_LIB_MAIN
#include "../../include/AdminAPI.h"
#include "../libhttp/Http.h"
#include "Config.h"
#include "Method.h"
#include "Utility.h"
#include <json/json.h>

AdminAPI::AdminAPI(Request *request)
{
    m_request = request;
}

Result AdminAPI::getAllocation(const string &sessionKey, Allocation &allocation)
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
        if(!root["error_code"].isNull())
            return root["error_code"].asUInt();

        allocation.m_notificationsPerDay = root["notifications_per_day"].asUInt();
        allocation.m_requestsPerDay = root["requests_per_day"].asUInt();

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}
