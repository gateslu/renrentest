#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include "include/RRAPI"

class Object : public QObject
{
    Q_OBJECT
public:
    explicit Object(QObject *parent = 0);
    
signals:
    void sig(int i);
    void down(STATUSID id, QString url);
    
public slots:
    void emitsig(int i)
    {
        emit sig(i);
    }
    
    void emitdown(STATUSID id, QString url)
    {
        emit down(id, url);
    }
};

#endif // OBJECT_H
