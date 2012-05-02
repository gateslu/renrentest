#include "Http.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <assert.h>
#include <iostream>
#include <QByteArray>
#include <QDebug>

Request::Request()
{
	m_curl = ::curl_easy_init();
	assert(m_curl);
}

Request::~Request()
{
	::curl_easy_cleanup(m_curl);
	m_curl = 0;
}

Result Request::syncRequest(const std::string &url, Method method,
							const RequestParam &params, Response *response)
{
	if(!response)
		return RESULT_NULL_POINTER;

	CURLcode res = ::curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	if(url.npos != url.find("https"))
	{
		// https
		::curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
		::curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);
	}

	::curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, Request::_receive);
	::curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, response);
	//curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);
	//curl_easy_setopt(m_curl, CURLOPT_HEADER, 1L);
	::curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);

	if(method == Post)
	{
		char paramStr[1024];
//		::strncpy_s(paramStr, 1024, params.toString().c_str(), params.toString().length());
        qstrncpy(paramStr, params.toString().c_str(), params.toString().length()+1);
//        qDebug() << QString(paramStr);
		::curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, paramStr);
		::curl_easy_setopt(m_curl, CURLOPT_POST, 1L);
	}

	res = ::curl_easy_perform(m_curl);

	return RESULT_OK;
}

size_t Request::_receive(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	Response *pResponse = (Response *)userdata;
	pResponse->addRawData((char *)ptr, nmemb);

	return nmemb * size;
}
