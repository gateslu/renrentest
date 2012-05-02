#ifndef HTTP_H
#define HTTP_H

#include "../../include/Global.h"
#include "../../include/Result.h"
#include <string>
#include <map>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef map<string, string>	Param;

class RequestParam
{
public:
	RequestParam();
	RequestParam(const RequestParam &other);
	RequestParam &operator = (const RequestParam &other);
	~RequestParam();

	RequestParam &addParam(const string &key, const string &value);
	RequestParam &removeParam(const string &key);
	void setValue(const string &key, const string &value);

	string toString(const string &separator = "&") const;

protected:
	Param *m_paramList;
};

class Response
{
public:
	Response(void);
	~Response(void);

	void clearRawData();
	void addRawData(const char *rawData, size_t size);
	void setRawData(const char *rawData, size_t size);
	const char *getRawData() {return m_rawData;}

protected:
	char *m_rawData;
	size_t m_rawDataSize;
};

typedef void CURL;

class Request
{
public:
	enum Method {Post, Get};

public:
	Request();
	~Request();

	// Synchronous request
	Result syncRequest(const string &url, Method method,
					   const RequestParam &params, Response *response);

protected:
	CURL *m_curl;

	static size_t _receive(void *ptr, size_t size, size_t nmemb, void *userdata);
};

#endif	//HTTP_H
