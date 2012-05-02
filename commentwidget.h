#ifndef COMMENTWIDGET_H
#define COMMENTWIDGET_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class CommentWidget;
}

class CommentWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CommentWidget(QWidget *parent = 0);
    ~CommentWidget();
    int documentHeight();
    void setComment(const QString &text);
    void setName(const QString &text);
    void setTime(const QString &text);
    void setPix(const QByteArray &buff);

public slots:
    void resizeWidget();

protected:
    void resizeEvent(QResizeEvent *ev);

private:
    Ui::CommentWidget *ui;
    int wh;
};

#endif // COMMENTWIDGET_H
