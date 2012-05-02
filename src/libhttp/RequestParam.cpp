#include "Http.h"

RequestParam::RequestParam()
{
	m_paramList = new Param;
}

RequestParam::~RequestParam()
{
	delete m_paramList;
}

RequestParam::RequestParam(const RequestParam &other)
{
	m_paramList = new Param(*other.m_paramList);
}

RequestParam &RequestParam::operator = (const RequestParam &other)
{
	m_paramList = new Param(*other.m_paramList);
	return *this;
}

RequestParam &RequestParam::addParam(const std::string &key, const std::string &value)
{
	(*m_paramList)[key] = value;
	return *this;
}

RequestParam &RequestParam::removeParam(const std::string &key)
{
	m_paramList->erase(m_paramList->find(key));
	return *this;
}

std::string RequestParam::toString(const std::string &separator) const
{
	std::string rslt;
	for(Param::iterator it = m_paramList->begin();
		it != m_paramList->end();
		it++)
	{
		rslt += it->first + "=" + it->second + separator;
	}
	if(rslt.size() && separator.length())
		rslt.erase(rslt.size() - separator.length());

	return rslt;
}

void RequestParam::setValue(const std::string &key, const std::string &value)
{
	(*m_paramList)[key] = value;
}
