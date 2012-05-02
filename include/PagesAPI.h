#ifndef PAGESAPI_H
#define PAGESAPI_H

#include "Global.h"
#include "Result.h"
#include "Permission.h"
#include <string>

using namespace std;

class Request;

class  PagesAPI
{
public:
    PagesAPI(Request *request);

    Result isFan(const string &sessionKey, UID uid, PAGEID pageId, bool &result);

private:
    Request *m_request;
};

#endif  //PAGESAPI_H
