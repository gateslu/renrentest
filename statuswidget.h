#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include "commentwidget.h"
#include <QList>

namespace Ui {
class statusWidget;
}

class statusWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit statusWidget(QWidget *parent = 0);
    ~statusWidget();
    int documentHeight();
    void setComment(const QString &text);
    void setName(const QString &text);
    void setTime(const QString &text);
    void setCount(int c);
    void setCountDisable(bool b);
    void setPix(const QByteArray &buff);
    void updateGuestWidget(QList<CommentWidget*> cwlist);
    
signals:
    void pushCommentButton();

private slots:
    void on_count_toggled(bool checked);
    void resizeWidget();
    void changeFlag();

protected:
    void resizeEvent(QResizeEvent *ev);

private:
    Ui::statusWidget *ui;
    int wh;
    int ch;
    bool isButtonChange;
    QString countText;
};

#endif // STATUSWIDGET_H
