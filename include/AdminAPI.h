#ifndef ADMINAPI_H
#define ADMINAPI_H

#include "Global.h"
#include "Result.h"
#include "Permission.h"
#include <string>
using namespace std;

class Request;

class  Allocation
{
public:
    unsigned long m_notificationsPerDay;
    unsigned long m_requestsPerDay;
};

class  AdminAPI
{
public:
    AdminAPI(Request *request);

    Result getAllocation(const string &sessionKey, Allocation &allocation);

private:
    Request *m_request;
};

#endif  //ADMINAPI_H
