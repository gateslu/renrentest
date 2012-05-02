#include <Windows.h>
#include "Utility.h"
#include "Config.h"
#include "MD5.h"
#include <string>
#include <stdio.h>
#include <QtCore>
#include <QString>
#include <QObject>
using namespace std;

string Utility::formatTime(int year, int month, int day, int hour, int minute, int second)
{
    QString time = QString(QObject::tr("%1-%2-%3 %4:%5:%6").arg(year, 4, 10, QChar('0'))
                  .arg(month, 2, 10, QChar('0'))
                  .arg(day, 2, 10, QChar('0'))
                  .arg(hour, 2, 10, QChar('0'))
                  .arg(minute, 2, 10, QChar('0'))
                  .arg(second, 2, 10, QChar('0')));

    return time.toStdString();
}

string Utility::getSignature(const RequestParam &params)
{
    string md5code;
    string sig = params.toString("");

    sig += Config::m_secretKey;
//    qDebug() << QString::fromStdString(sig);
    MD5 md5(sig);
    md5code = md5.toString();
//    qDebug() << QString::fromStdString(md5code);
    return md5.toString();
}

string Utility::getCallId()
{
//    char call_id[20];
//    ::sprintf(call_id, 20, "%u", ::GetTickCount());
//    return string(call_id);

//    QString str = QString("%1").arg(::GetTickCount(), 20, 10, QChar(' '));
    QString str = QString::number(::GetTickCount());
    return str.toStdString();
}

string Utility::UTF8ToString(const string &str)
{
    int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

    wchar_t * pwBuf = new wchar_t[nwLen + 1];
    memset(pwBuf, 0, nwLen * 2 + 2);

    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

    int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

    char * pBuf = new char[nLen + 1];
    memset(pBuf, 0, nLen + 1);

    WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

    std::string retStr = pBuf;

    delete []pBuf;
    delete []pwBuf;

    pBuf = NULL;
    pwBuf = NULL;

    return retStr;
}

string Utility::stringToUTF8(const string &str)
{
    int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

    wchar_t * pwBuf = new wchar_t[nwLen + 1];
    ZeroMemory(pwBuf, nwLen * 2 + 2);

    ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

    int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

    char * pBuf = new char[nLen + 1];
    ZeroMemory(pBuf, nLen + 1);

    ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

    std::string retStr(pBuf);

    delete []pwBuf;
    delete []pBuf;

    pwBuf = NULL;
    pBuf  = NULL;

    return retStr;
}
