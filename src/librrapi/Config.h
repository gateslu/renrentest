#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "include/Global.h"
using namespace std;

class Config
{
public:
    static const string m_version;		// Version of this library
    static const string m_apiVersion;	// Version of Renren API
    static const string m_apiKey;		// API key of your application
    static const string m_secretKey;	// Secret key of your application

    static const string m_resultFormat;	// Json or XML
    static const string m_userInfoFields;
    static const string m_appFriendsFields;

    static const string m_RESTServerURL;

private:
    Config();
};


#endif	//CONFIG_H
