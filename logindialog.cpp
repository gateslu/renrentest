#include "logindialog.h"
#include "ui_logindialog.h"
#include <QWebElement>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QWebView>
#include <QMessageBox>
#include <stdio.h>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),isConnecting(true),isAccept(false),m_sessionKey("")
{
    ui->setupUi(this);
    connect(ui->refreshIcode, SIGNAL(refresh()), this, SLOT(refreshLabel()));

    webView = new QWebView;

    connect(webView->page()->networkAccessManager(),
            SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
            this,
            SLOT(sslErrorHandler(QNetworkReply*, const QList<QSslError> & )));


    initUrl = "https://graph.renren.com/oauth/authorize?"
            "client_id=004911f885614b67a940c44567023ab9&redirect_uri=http://graph.renren.com/oauth/"
            "login_success.html&response_type=token&"
            "scope=read_user_album+read_user_feed+read_user_status+status_update";

//    initUrl = "https://gmail.com";

    //    m_cookieJar = new QNetworkCookieJar;
    //    webView->page()->networkAccessManager()->setCookieJar(m_cookieJar);

    connect(webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(populateJavaScriptWindowObject()));
    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(loadfinished(bool)));
    connect(webView, SIGNAL(loadProgress(int)), this, SLOT(setProgress(int)));
    webView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    webView->settings()->setAttribute(QWebSettings::PluginsEnabled,true);

    webView->setUrl(QUrl(initUrl));

    inputFinished = false;
    isShowIcode(false);
    //    webView->setVisible(false);
    ui->verticalLayout->addWidget(webView);
    ui->widget->setVisible(false);
    ui->loginButton->setDefault(true);
}

LoginDialog::~LoginDialog()
{
    //    qDebug() << "exit!";
    delete ui;
}

void LoginDialog::isShowIcode(bool b)
{
    ui->noLabel->setVisible(b);
    ui->icodeLabel->setVisible(b);
    ui->refreshIcode->setVisible(b);
    ui->icodeNmae->setVisible(b);
    ui->icodeEdit->setVisible(b);
}

void LoginDialog::refreshLabel()
{
    QNetworkAccessManager *manager;
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    webView->page()->mainFrame()->evaluateJavaScript(QString( "refreshCode();" ));

    reply = manager->get(QNetworkRequest(QUrl("http://icode.renren.com/getcode.do?t=openplatform")));
}

void LoginDialog::populateJavaScriptWindowObject()
{
    QString url = webView->url().toString();
    if (url.startsWith("http://graph.renren.com/oauth/login_success.html#access_token=185779|"))
    {
        m_sessionKey = url.mid(69, 63);
        isAccept = true;
    }
    else if (url.startsWith("http://graph.renren.com/login?"
                            "redirect_uri=http://graph.renren.com/oauth/authorize?"
                            "client_id=004911f885614b67a940c44567023ab9&redirect_"
                            "uri=http%3A%2F%2Fgraph.renren.com%2Foauth%2Flogin_success.html")
             && isConnecting)
    {
        on_loginButton_clicked();
    }
}

void LoginDialog::loadfinished(bool)
{
    if (isAccept)
        accept();

    if (isConnecting)
    {
        ui->urlLoadPB->setVisible(false);
        ui->widget->setVisible(true);
        isConnecting = false;
    }

    //    QByteArray string;

    //    QNetworkCookie cookie;
    //    QList<QNetworkCookie> list = m_cookieJar->cookiesForUrl (QUrl(webView->url().toString()));
    //    foreach (cookie ,list)
    //    {
    //        string += cookie.toRawForm() + "\n";
    //    }

    QString str = webView->page()->mainFrame()->toHtml();

    if (str.contains(tr("帐号或密码错误，请重试"), Qt::CaseInsensitive))
    {
        ui->errorLabel->setText(tr("<font color='red'>帐号或密码错误，请重试</font>"));
        ui->passwdEdit->clear();
        ui->icodeEdit->clear();
        ui->emaliEdit->setFocus();
    }
    else if (str.contains(tr("验证码错误"), Qt::CaseInsensitive))
    {
        ui->errorLabel->setText(tr("<font color='red'>验证码错误</font>"));
        ui->passwdEdit->clear();
        ui->icodeEdit->clear();
        ui->emaliEdit->setFocus();
    }
    else if (str.contains(tr("onclick=\"forms[0].submit();return false;\">进入应用</a></div>"), Qt::CaseInsensitive))
    {
        int ret = QMessageBox::question(this, tr("连接人人网"),
                                        tr("第一次连接, 是否愿意授权本软件连接你的人人账号?\n"),
                                        QMessageBox::Yes | QMessageBox::Discard,
                                        QMessageBox::Yes);

        switch (ret) {
        case QMessageBox::Yes:
        {
            qDebug() << "yes i'm";
            QWebElementCollection col = webView->page()->mainFrame()->findAllElements("a");
            foreach (QWebElement el, col) {
                if (el.geometry().width() == 60 && el.evaluateJavaScript("this.href").toString() == "javascript:;")
                {
                    el.evaluateJavaScript("document.forms[0].submit(); fasle;");
                }
            }
            break;
        }
        case QMessageBox::Discard:
            reject();
            break;
        default:
            // should never be reached
            break;
        }
    }
    else
    {
        ui->errorLabel->setText(tr(""));
    }
    qDebug() << "here";
}

void LoginDialog::setProgress(int i)
{
    ui->urlLoadPB->setValue(i);
}

void LoginDialog::replyFinished(QNetworkReply *m_reply)
{
    QWebElement icodeSrc = webView->page()->mainFrame()->findFirstElement("#verifyPic");
    QPixmap pix(icodeSrc.geometry().size());
    QPainter p(&pix);
    icodeSrc.render(&p);
    ui->icodeLabel->setPixmap(pix);
}

void LoginDialog::on_loginButton_clicked()
{
    if (ui->emaliEdit->text().isEmpty())
    {
        ui->errorLabel->setText(tr("<font color='red'>您还没有填写帐号</font>"));
        return;
    }

    if (ui->passwdEdit->text().isEmpty())
    {
        ui->errorLabel->setText(tr("<font color='red'>您还没有填写密码</font>"));
        return;
    }

    if (ui->icodeEdit->text().isEmpty() && showIcode == "true")
    {
        ui->errorLabel->setText(tr("<font color='red'>您还没有填写验证码</font>"));
        return;
    }

    ui->urlLoadPB->setVisible(true);
    ui->widget->setVisible(false);
    isConnecting = true;

    //    webView->page()->mainFrame()->evaluateJavaScript(QString("checkForm();"));
    webView->page()->mainFrame()->evaluateJavaScript(QString("document.forms[0].submit();"));
}

void LoginDialog::on_emaliEdit_lostFocus()
{
    if (inputFinished)
        webView->page()->mainFrame()->evaluateJavaScript(QString( "showCaptcha();" ));

    QWebElement isNeedIcode = webView->page()->mainFrame()->findFirstElement("#isNeedIcode");
    QString showicode = isNeedIcode.evaluateJavaScript("this.value").toString();
    showIcode = showicode;
    //    qDebug() << showicode;
    if (showicode == "true")
    {
        //        QPixmap pix(120, 45);
        QWebElement icodeSrc = webView->page()->mainFrame()->findFirstElement("#verifyPic");
        if (icodeSrc.geometry().size().width() == 0 || icodeSrc.geometry().size().height() == 0)
            return;
        isShowIcode(true);
        QPixmap pix(icodeSrc.geometry().size());
        QPainter p(&pix);
        icodeSrc.render(&p);
        ui->icodeLabel->setPixmap(pix);
    }
    else
        isShowIcode(false);
}

void LoginDialog::on_emaliEdit_textChanged(const QString &arg1)
{
    webView->page()->mainFrame()->evaluateJavaScript(QString( "document.getElementById('email').value = \"%1\";" ).arg(arg1));
    if (arg1.contains(tr("@")) && arg1.endsWith(tr(".com")))
    {
        inputFinished = true;
        //        qDebug() << "inputFinished =" << inputFinished;
        webView->page()->mainFrame()->evaluateJavaScript(QString( "showCaptcha();" ));
    }
    else
    {
        inputFinished = false;
        //        qDebug() << "inputFinished =" << inputFinished;
    }
}

void LoginDialog::on_passwdEdit_textChanged(const QString &arg1)
{
    webView->page()->mainFrame()->evaluateJavaScript(QString( "document.getElementById('password').value = \"%1\";" ).arg(arg1));
    on_emaliEdit_lostFocus();
}

void LoginDialog::on_icodeEdit_textChanged(const QString &arg1)
{
    webView->page()->mainFrame()->evaluateJavaScript(QString( "document.getElementById('icode').value = \"%1\";" ).arg(arg1));
}

void LoginDialog::sslErrorHandler(QNetworkReply *qnr, const QList<QSslError> &errlist)
{
#if DEBUG_BUYIT
    qDebug() << "---frmBuyIt::sslErrorHandler: ";
    // show list of all ssl errors
    foreach (QSslError err, errlist)
        qDebug() << "ssl error: " << err;
#endif

    qnr->ignoreSslErrors();
}
