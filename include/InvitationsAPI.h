#ifndef INVITATIONSAPI_H
#define INVITATIONSAPI_H

#include "Global.h"
#include "Result.h"
#include "Permission.h"
#include <string>
#include <QVector>
using namespace std;

class Request;

class  InvitationInfo
{
public:
    enum Type {Outside = 0, Inside = 1};    // Outside:Õ¾ÍâÑûÇë£»Inside:Õ¾ÄÚÑûÇë
    Type m_type;
    UID m_inviterUID;
    string m_inviteTime;
    UID m_inviteeUID;
};

class  InvitationsAPI
{
public:
    InvitationsAPI(Request *request);

    Result createLink(const string &sessionKey, string &link);
    Result getInfoByInviteeUID(const string &sessionKey, UID inviteeUID, QVector<InvitationInfo> &list);
    Result getInfoByTime(const string &sessionKey, const string &startTime, const string &endTime, QVector<InvitationInfo> &list);

private:
    Request *m_request;
};

#endif  //INVITATIONSAPI_H
