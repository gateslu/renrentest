#include "commentwidget.h"
#include "ui_commentwidget.h"
#include <QDebug>

CommentWidget::CommentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentWidget)
{
    ui->setupUi(this);
//    QTimer::singleShot(50, this, SLOT(resizeWidget()));
}

CommentWidget::~CommentWidget()
{
    delete ui;
}

int CommentWidget::documentHeight()
{
    return ui->comment->document()->size().rheight();
}

void CommentWidget::setComment(const QString &text)
{
    ui->comment->setText(text);
}

void CommentWidget::setName(const QString &text)
{
    ui->name->setText(text);
}

void CommentWidget::setTime(const QString &text)
{
    ui->time->setText(text);
}

void CommentWidget::setPix(const QByteArray &buff)
{
    QPixmap pix;
    pix.loadFromData(buff);
    ui->head->clear();
    ui->head->setPixmap(pix);
    ui->head->setMaximumSize(40, 40);
}

void CommentWidget::resizeWidget()
{
    int dh = ui->comment->document()->size().rheight();
    qDebug() << "comment";
    wh = 30 + dh;
    this->setMaximumHeight(wh);
    this->setMinimumHeight(wh);
}

void CommentWidget::resizeEvent(QResizeEvent *ev)
{
    int dh = ui->comment->document()->size().rheight();
    wh = 45;
    this->setMaximumHeight(wh);
    this->setMinimumHeight(wh);
    QWidget::resizeEvent(ev);
}
