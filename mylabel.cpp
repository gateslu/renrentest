#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) :
    QLabel(parent)
{
    setStyleSheet("QLabel{color: blue}");
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
        {
            emit refresh();
        }
    QLabel::mousePressEvent(ev);
}
