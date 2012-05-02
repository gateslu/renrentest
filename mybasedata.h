#ifndef MYBASEDATA_H
#define MYBASEDATA_H

#include <QObject>
#include "include/RRAPI"

namespace MyData {

class MyBaseData : public QObject
{
    Q_OBJECT
public:
    explicit MyBaseData(QObject *parent = 0);
    QVector<UserInfo> userInfoList;
signals:

public slots:

};
}

#endif // MYBASEDATA_H
