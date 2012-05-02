#ifndef PAYAPI_H
#define PAYAPI_H

#include "Global.h"
#include "Result.h"
#include "Permission.h"
#include <string>

using namespace std;

class Request;

class  PayAPI
{
public:
    enum PayType {WebOrder = 0, WapOrder = 1};
public:
    PayAPI(Request *request);

    Result isCompleted(const string &sessionKey, ORDERID orderId, bool &result);
    Result regOrder(const string &sessionKey, ORDERID orderId, int amount, const string &description, PayType type, string &token);

    Result isCompleted4Test(const string &sessionKey, ORDERID orderId, bool &result);
    Result regOrder4Test(const string &sessionKey, ORDERID orderId, int amount, const string &description, PayType type, string &token);

private:
    Request *m_request;
};

#endif  //PAYAPI_H
