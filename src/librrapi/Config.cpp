#include "Config.h"

const string Config::m_version = "1.0.0";
const string Config::m_apiVersion = "1.0";
const string Config::m_apiKey = "004911f885614b67a940c44567023ab9";
const string Config::m_secretKey = "2cd6d3bc6df349a0b3268e64a5d8729e";

const string Config::m_resultFormat = "JSON";
const string Config::m_userInfoFields = "uid,name,sex,star,zidou,vip,birthday,email_hash,tinyurl,headurl,mainurl,hometown_location,work_history,university_history,hs_history";
const string Config::m_appFriendsFields = "name,tinyurl,headurl";

const string Config::m_RESTServerURL = "http://api.renren.com/restserver.do";

Config::Config()
{
}
