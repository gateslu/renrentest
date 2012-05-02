#include "renrentest.h"
#include "ui_renrentest.h"
#include "statuswidget.h"
#include <QMovie>
#include <QTimer>
#include "commentwidget.h"

renrentest::renrentest(const QString &m_sessionkey, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::renrentest)
{
    ui->setupUi(this);

    isallowrefresh0 = true;
    isallowrefresh1 = true;
    isallowrefresh2 = true;

    timer0 = new QTimer(this);
    connect(timer0, SIGNAL(timeout()), this, SLOT(chageRefresh0()));
    timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(chageRefresh1()));
    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(chageRefresh2()));

    progressBar = new QProgressBar;
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setMinimumSize(200, 15);
    progressBar->setMaximumSize(200, 15);

    QMovie *movie = new QMovie(":/facial.gif");
    ui->facialGif->setMovie(movie);
    movie->start();

    QLabel *label = new QLabel;
    label->setText(tr("加载图片"));
    ui->statusbar->addWidget(label);
    ui->statusbar->addWidget(progressBar);

    downThread = new DownLoadFun;
    downThread->moveToThread(&downloadthread);
    connect(&download, SIGNAL(down(STATUSID, QString)), downThread, SLOT(down(STATUSID, QString)), Qt::DirectConnection);
    connect(downThread, SIGNAL(httpData(STATUSID, QByteArray)), this, SLOT(setStatusHead(STATUSID, QByteArray)), Qt::DirectConnection);

    exThread = new ExchangeThread(m_sessionkey);
    exThread->moveToThread(&thread);
    connect(&obj, SIGNAL(sig(int)), exThread, SLOT(infoType(int)));
    connect(exThread, SIGNAL(httpData(QByteArray)), this, SLOT(setPixmap(QByteArray)));
    connect(exThread, SIGNAL(updateUIProgress(qint64,qint64)), this, SLOT(updateUIProgress(qint64,qint64)));
    connect(exThread, SIGNAL(s_updateStatusOK()), this, SLOT(updateStatus()));
    //    connect(this, SIGNAL(changeType(int)), exThread, SLOT(infoType(int)), Qt::DirectConnection);
    //    connect(this, SIGNAL(changeType(int)), exThread, SLOT(infoType(int)));

    connect(exThread, SIGNAL(s_userInfoList(QVector<UserInfo>)),
            this, SLOT(getUserInfo(QVector<UserInfo>)), Qt::DirectConnection);
    connect(exThread, SIGNAL(s_getStatus(QVector<StatusInfo>)),
            this, SLOT(getStatus(QVector<StatusInfo>)), Qt::DirectConnection);

    qDebug() << "m_sessionkey : " << m_sessionkey;
    qDebug()<<"main thread:" <<QThread::currentThreadId();
    on_tabWidget_currentChanged(0);
}

renrentest::~renrentest()
{
    threadExit();
    delete ui;
}

//QString与string转换
QString renrentest::qfs(string cs)
{
    return QString::fromStdString(cs);
}

void renrentest::threadExit()
{
    if (downloadthread.isRunning())
    {
        downloadthread.exit();
        downloadthread.wait();
    }

    if (thread.isRunning())
    {
        thread.exit();
        thread.wait();
    }
}

QString renrentest::userConstellation(const QString &birthday)
{
    QStringList constellation =  QStringList()<< tr("摩羯座") << tr("水瓶座") << tr("双鱼座") << tr("白羊座")
                                              << tr("金牛座") << tr("双子座") << tr("巨蟹座") << tr("狮子座")
                                              << tr("处女座") << tr("天秤座") << tr("天蝎座") << tr("射手座");

    QString m_constellation;
    QStringList list = birthday.split("-");
    int date = list.at(2).toInt();
    switch (list.at(1).toInt())
    {
    case 1:
        if (date >= 1 && date <= 19)
            m_constellation = constellation.at(0);
        else
            m_constellation = constellation.at(1);
        break;
    case 2:
        if (date >= 1 && date <= 18)
            m_constellation = constellation.at(1);
        else
            m_constellation = constellation.at(2);
        break;
    case 3:
        if (date >= 1 && date <= 20)
            m_constellation = constellation.at(2);
        else
            m_constellation = constellation.at(3);
        break;
    case 4:
        if (date >= 1 && date <= 19)
            m_constellation = constellation.at(3);
        else
            m_constellation = constellation.at(4);
        break;
    case 5:
        if (date >= 1 && date <= 20)
            m_constellation = constellation.at(4);
        else
            m_constellation = constellation.at(5);
        break;
    case 6:
        if (date >= 1 && date <= 21)
            m_constellation = constellation.at(5);
        else
            m_constellation = constellation.at(6);
        break;
    case 7:
        if (date >= 1 && date <= 22)
            m_constellation = constellation.at(6);
        else
            m_constellation = constellation.at(7);
        break;
    case 8:
        if (date >= 1 && date <= 22)
            m_constellation = constellation.at(7);
        else
            m_constellation = constellation.at(8);
        break;
    case 9:
        if (date >= 1 && date <= 22)
            m_constellation = constellation.at(8);
        else
            m_constellation = constellation.at(9);
        break;
    case 10:
        if (date >= 1 && date <= 23)
            m_constellation = constellation.at(9);
        else
            m_constellation = constellation.at(10);
        break;
    case 11:
        if (date >= 1 && date <= 22)
            m_constellation = constellation.at(10);
        else
            m_constellation = constellation.at(11);
        break;
    case 12:
        if (date >= 1 && date <= 21)
            m_constellation = constellation.at(11);
        else
            m_constellation = constellation.at(0);
        break;
    default:
        m_constellation = tr("");
        break;
    }
    return m_constellation;
}

void renrentest::setTabbarEnable(int c,bool b)
{
    int tc = ui->tabWidget->count();

    for (int i = 0; i < tc; i++)
    {
        if (i != c)
            ui->tabWidget->setTabEnabled(i, b);
    }
}

//设置刷新
bool renrentest::isAllowRefresh(int type)
{
    bool isallow = true;
    switch (type)
    {
    case 0:
        if (isallowrefresh0)
            isallow = false;
        break;
    case 1:
        if (isallowrefresh1)
            isallow = false;
        break;
    case 2:
        if (isallowrefresh2)
            isallow = false;
        break;
    default:
        isallow = false;
        break;
    }
    return isallow;
}

void renrentest::getUserInfo(QVector<UserInfo> userInfoList)
{
    ui->nameLB->setText(qfs(userInfoList.at(0).m_name));
    ui->IDLB->setText(QString::number(userInfoList.at(0).m_uid));

    tiny_head = qfs(userInfoList.at(0).m_tinyURL);
    qDebug() << tiny_head;

    if (downloadthread.isRunning())
        downloadthread.exit();
    downloadthread.start();
    download.emitdown(0, tiny_head);

    if (userInfoList.at(0).m_sex)
        ui->sexLB->setText(tr("男"));
    else
        ui->sexLB->setText(tr("女"));

    ui->constellationLB->setText(userConstellation(qfs(userInfoList.at(0).m_birthday)));

    ui->birthdayLB->setText(qfs(userInfoList.at(0).m_birthday));

    ui->hometownLB->setText(qfs(userInfoList.at(0).m_hometown.m_city));

    if (userInfoList.at(0).m_univHistory.size() > 0)
    {
        QString universityInfo;
        universityInfo = qfs(userInfoList.at(0).m_univHistory.at(0).m_name) + " - "
                + QString::number(userInfoList.at(0).m_univHistory.at(0).m_year) + "年 － "
                + qfs(userInfoList.at(0).m_univHistory.at(0).m_department);
        ui->universityLB->setText(universityInfo);
    }

    if (userInfoList.at(0).m_workHistory.size() > 0)
    {
        ui->companyLB->setText(qfs(userInfoList.at(0).m_workHistory.at(0).m_company));
    }
}

void renrentest::getStatus(QVector<StatusInfo> list)
{
    if (!stwHash.isEmpty())
    {
        QHashIterator<STATUSID, statusWidget*> i(stwHash);
        while (i.hasNext()) {
            i.next();
            ui->statusLayout->removeWidget(i.value());
            delete i.value();
        }
        stwHash.clear();
    }

    qApp->processEvents();
    qDebug() << list.size();
    for (int i = 0; i < list.size(); i++)
    {
//        qDebug() << "*****************************";
//        qDebug() << qfs(list.at(i).m_message);
//        qDebug() << list.at(i).m_commentCount;;
//        qDebug() << qfs(list.at(i).m_time);
//        //        qDebug() << list.at(i).m_place;
//        qDebug() << qfs(list.at(i).m_srcName);
//        qDebug() << qfs(list.at(i).m_srcURL);
//        qDebug() << list.at(i).m_statusId;
//        qDebug() << list.at(i).m_uid;
//        qDebug() << "*****************************";
        qApp->processEvents();
        stWidget = new statusWidget(this);
        stWidget->setComment(qfs(list.at(i).m_message));
        stWidget->setName(ui->nameLB->text()+tr("："));
        stWidget->setTime(qfs(list.at(i).m_time));
        stWidget->setCount(list.at(i).m_commentCount);
        if (!headPixBuff.isEmpty())
            stWidget->setPix(headPixBuff);
        if (list.at(i).m_commentCount == 0)
            stWidget->setCountDisable(true);
        else
        {
            int sub = list.at(i).m_commentCount;
            QList<CommentWidget *> cwList;
            for (int j = 0; j < sub; j++)
            {
                CommentWidget *subwidget = new CommentWidget(stWidget);
                connect(stWidget, SIGNAL(pushCommentButton()), subwidget, SLOT(resizeWidget()), Qt::DirectConnection);
                cwList << subwidget;
            }
            stWidget->updateGuestWidget(cwList);
            qApp->processEvents();
        }
        ui->statusLayout->addWidget(stWidget);
        stwHash.insert(list.at(i).m_statusId, stWidget);
        qApp->processEvents();
    }
    qDebug() << "stwHash" << stwHash.size();
    ui->statusLayout->addStretch();
}

void renrentest::setPixmap(QByteArray tmpData)
{
    QPixmap pix;
    pix.loadFromData(tmpData);
    ui->headImage->clear();
    ui->headImage->setPixmap(pix);
    ui->headImage->setMaximumSize(128, 128*pix.height()/pix.width());
}

void renrentest::setStatusHead(STATUSID id, QByteArray tmpData)
{
    Q_UNUSED(id);
    headPixBuff = tmpData;
}

//切换界面
void renrentest::on_tabWidget_currentChanged(int index)
{
    if (isAllowRefresh(index))
        return;

    if (thread.isRunning())
        thread.exit();
    progressBar->setValue(0);
    tabCurrentIndex = ui->tabWidget->currentIndex();
    setTabbarEnable(tabCurrentIndex, false);
    qApp->processEvents();
    if (index == 0 )
    {
        limitClick(2000);         //最短操作间隔,2000毫秒
        isallowrefresh0 = false;
        thread.start();
        obj.emitsig(index+1);
//        QTimer::singleShot(600000, this, SLOT(chageRefresh0()));
        if (timer0->isActive())
            timer0->stop();
        timer0->start(7200000);
    }
    else if (index == 1)
    {
        limitClick(2000);         //最短操作间隔,2000毫秒
        isallowrefresh1 = false;
        exThread->infoType(index+1);
//        QTimer::singleShot(5000, this, SLOT(chageRefresh1()));
        if (timer1->isActive())
            timer1->stop();
        timer1->start(120000);
    }
    else if (index == 2)
    {
        limitClick(2000);         //最短操作间隔,2000毫秒
        isallowrefresh2 = false;
        exThread->infoType(index+1);
//        QTimer::singleShot(120000, this, SLOT(chageRefresh2()));
        if (timer2->isActive())
            timer2->stop();
        timer2->start(120000);
    }
    else if (index == 999)
    {
//        limitClick(2000);         //最短操作间隔,2000毫秒
        setTabbarEnable(tabCurrentIndex, true);
        if (ui->statusContent->toPlainText().isEmpty() || ui->statusContent->toPlainText().size() > 234)
        {
            ui->statusbar->showMessage(tr("请分享你的状态！！"), 1500);
            return;
        }
        ui->publishButton->setDisabled(true);
        exThread->setStatusContent(ui->statusContent->toPlainText());
        thread.start();
        obj.emitsig(index+1);
    }
}

//图片载入进度条
void renrentest::updateUIProgress(qint64 bytesRead, qint64 totalBytes)
{
    progressBar->setMaximum(totalBytes); //最大值
    progressBar->setValue(bytesRead);  //当前值
}

void renrentest::changeTabState()
{
    setTabbarEnable(tabCurrentIndex, true);
}

//发布状态后更新页面
void renrentest::updateStatus()
{
    isallowrefresh1 = true;
    ui->statusContent->clear();
    ui->publishButton->setDisabled(false);
    on_tabWidget_currentChanged(1);
}

//最短操作间隔
void renrentest::limitClick(int msec)
{
    QTimer::singleShot(msec, this, SLOT(changeTabState()));
}

//激活刷新
void renrentest::chageRefresh0()
{
    timer0->stop();
    isallowrefresh0 = true;
}

void renrentest::chageRefresh1()
{
    timer1->stop();
    isallowrefresh1 = true;
}

void renrentest::chageRefresh2()
{
    timer2->stop();
    isallowrefresh2 = true;
}

void renrentest::resizeEvent(QResizeEvent *ev)
{
    //    qDebug() << "resize";
    QMainWindow::resizeEvent(ev);
}

void renrentest::on_publishButton_clicked()
{
    on_tabWidget_currentChanged(999);
}

void renrentest::on_statusContent_textChanged()
{
    int c = ui->statusContent->toPlainText().size();
    ui->charCount->setText(tr("%1/234").arg(QString::number(c)));
}
