#define RRAPI_LIB_MAIN
#include "../../include/PayAPI.h"
#include "../libhttp/Http.h"
#include "Config.h"
#include "Method.h"
#include "Utility.h"
#include <json/json.h>
#include <QString>

PayAPI::PayAPI(Request *request)
{
    m_request = request;
}

Result PayAPI::isCompleted(const string &sessionKey, ORDERID orderId, bool &result)
{
//    char orderIdBuf[30];
//    sprintf_s(orderIdBuf, 30, "%u", orderId);
    string orderIdBuf;
    orderIdBuf = QString::number(orderId).toStdString();

    RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::PAY_IS_COMPLETED);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
    params.addParam("order_id",     orderIdBuf);
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

        result = root["result"].asBool();

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}

Result PayAPI::regOrder(const string &sessionKey, ORDERID orderId, int amount, const string &description, PayType type, string &token)
{
//    char orderIdBuf[30];
//    sprintf_s(orderIdBuf, 30, "%u", orderId);
    string orderIdBuf;
    orderIdBuf = QString::number(orderId).toStdString();

//    char amountBuf[5];
//    sprintf_s(amountBuf, 5, "%u", amount);
    string amountBuf;
    amountBuf = QString::number(amount).toStdString();

    RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::PAY_REG_ORDER);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
    params.addParam("order_id",     orderIdBuf);
    params.addParam("amount",       amountBuf);
    params.addParam("desc",         description);
    params.addParam("type",         WebOrder == type ? "0" : "1");
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

        token = root["token"].asString();

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}

Result PayAPI::isCompleted4Test(const string &sessionKey, ORDERID orderId, bool &result)
{
//    char orderIdBuf[30];
//    sprintf_s(orderIdBuf, 30, "%u", orderId);
    string orderIdBuf;
    orderIdBuf = QString::number(orderId).toStdString();

    RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::PAY_IS_COMPLETED_4_TEST);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
    params.addParam("order_id",     orderIdBuf);
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

        result = root["result"].asBool();

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}

Result PayAPI::regOrder4Test(const string &sessionKey, ORDERID orderId, int amount, const string &description, PayType type, string &token)
{
//    char orderIdBuf[30];
//    sprintf_s(orderIdBuf, 30, "%u", orderId);
    string orderIdBuf;
    orderIdBuf = QString::number(orderId).toStdString();

//    char amountBuf[5];
//    sprintf_s(amountBuf, 5, "%u", amount);
    string amountBuf;
    amountBuf = QString::number(amount).toStdString();

    RequestParam params;
	params.addParam("api_key",		Config::m_apiKey);
    params.addParam("method",		Method::PAY_REG_ORDER_4_TEST);
	params.addParam("call_id",		Utility::getCallId());
	params.addParam("v",			Config::m_apiVersion);
    params.addParam("order_id",     orderIdBuf);
    params.addParam("amount",       amountBuf);
    params.addParam("desc",         description);
    params.addParam("type",         WebOrder == type ? "0" : "1");
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

        token = root["token"].asString();

        return RESULT_OK;
	}
	else
		return RESULT_JSON_INVALID;
}
