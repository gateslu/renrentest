#ifndef UTILITY_H
#define UTILITY_H

#include "include/Global.h"
#include "../libhttp/Http.h"
#include <QVector>
#include <string>

using namespace std;

class Utility
{
public:
    static string formatTime(int year, int month, int day, int hour, int minute, int second);
    static string getSignature(const RequestParam &params);
	static string getCallId();
	static string stringToUTF8(const string &str);
	static string UTF8ToString(const string & str);

private:
    Utility() {}
};

#endif	//UTILITY_H
