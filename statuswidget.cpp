#include "statuswidget.h"
#include "ui_statuswidget.h"
#include <QDebug>
#include <QTextDocument>
#include <QThread>
#include <QApplication>
#include <QTimer>

statusWidget::statusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statusWidget)
{
    isButtonChange = false;
    countText = "";
    ch = 0;
    ui->setupUi(this);
    ui->gusetWidget->setVisible(false);
    ui->comment->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //    this->setMaximumHeight(89);
    //    this->setMinimumHeight(89);

    QTimer::singleShot(20, this, SLOT(resizeWidget()));
}

statusWidget::~statusWidget()
{
    delete ui;
}

int statusWidget::documentHeight()
{
    return ui->comment->document()->size().rheight();
}

void statusWidget::setComment(const QString &text)
{
    ui->comment->setText(text);
}

void statusWidget::setName(const QString &text)
{
    ui->name->setText(text);
}

void statusWidget::setTime(const QString &text)
{
    ui->time->setText(text);
}

void statusWidget::setCount(int c)
{
    ui->count->setText(tr("回复(%1)").arg(QString::number(c)));
    countText = ui->count->text();
}

void statusWidget::setCountDisable(bool b)
{
    ui->count->setDisabled(b);
}

void statusWidget::setPix(const QByteArray &buff)
{
    QPixmap pix;
    pix.loadFromData(buff);
    ui->head->clear();
    ui->head->setPixmap(pix);
    ui->head->setMaximumSize(50, 50);
}

void statusWidget::updateGuestWidget(QList<CommentWidget *> cwlist)
{
    int c = cwlist.size();
    for (int i = 0; i < c; i++)
    {
        ui->gusetWL->addWidget(cwlist.at(i));
        qDebug() << cwlist.at(i)->minimumHeight();
        ch += cwlist.at(i)->minimumHeight();
    }
    ui->gusetWL->addStretch();
}

void statusWidget::on_count_toggled(bool checked)
{
    isButtonChange = true;
    qDebug() << "button1";
    ui->gusetWidget->setVisible(checked);
    emit pushCommentButton();
    //    int dh = ui->comment->document()->size().rheight();
    int wmh = this->minimumHeight();
    if (checked)
    {
        ui->count->setText(tr("收起回复"));
        this->setMaximumHeight(wmh+6+ch);
        this->setMinimumHeight(wmh+6+ch);
    }
    else
    {
        ui->count->setText(countText);
        this->setMaximumHeight(wmh-6-ch);
        this->setMinimumHeight(wmh-6-ch);
    }
    QTimer::singleShot(50, this, SLOT(changeFlag()));
}

void statusWidget::resizeWidget()
{
    int dh = ui->comment->document()->size().rheight();
    wh = 67+dh;
    this->setMaximumHeight(wh);
    this->setMinimumHeight(wh);
}

void statusWidget::changeFlag()
{
    qDebug() << "isButtonChange";
    isButtonChange = false;
}

void statusWidget::resizeEvent(QResizeEvent *ev)
{
//    qDebug() << "resize";
    if (isButtonChange)
        return;
    int dh = ui->comment->document()->size().rheight();
    if (ui->count->isChecked())
    {
        wh = 67+6+ch+dh;
    }
    else
    {
        wh = 67+dh;
    }
    this->setMaximumHeight(wh);
    this->setMinimumHeight(wh);
    QWidget::resizeEvent(ev);
}

