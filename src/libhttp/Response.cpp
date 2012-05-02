#include "Http.h"
#include <memory>
#include <assert.h>

Response::Response(void)
{
	m_rawData = 0;
	m_rawDataSize = 0;
}

Response::~Response(void)
{
	delete []m_rawData;
	m_rawData = 0;
	m_rawDataSize = 0;
}

void Response::clearRawData()
{
	delete []m_rawData;
	m_rawData = 0;
	m_rawDataSize = 0;
}

void Response::addRawData(const char *rawData, size_t size)
{
	if(!m_rawData || !m_rawDataSize)
	{
		m_rawData = new char[size];
		assert(m_rawData);

		::memcpy(m_rawData, rawData, size);
		m_rawDataSize = size;
	}
	else
	{
		char *ptr = (char *)realloc(m_rawData, m_rawDataSize + size);
		assert(ptr);
		m_rawData = ptr;
		::memcpy(m_rawData + m_rawDataSize, rawData, size);
		m_rawDataSize += size;
	}
}

void Response::setRawData(const char *rawData, size_t size)
{
	if(!size)
		return ;

	if(m_rawDataSize)
	{
		delete []m_rawData;
		m_rawDataSize = 0;
	}

	m_rawData = new char[size];
	assert(m_rawData);

	::memcpy(m_rawData, rawData, size);
	m_rawDataSize = size;
}
