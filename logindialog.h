#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtGui/QWidget>
#include <QWebFrame>
#include <QPixmap>
#include <QNetworkReply>
#include <QWebView>
#include <QPainter>
#include <QtNetwork>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void isShowIcode(bool b);

    QString sessionKey()
    {
        return m_sessionKey;
    }
    
private slots:
    void refreshLabel();

    void populateJavaScriptWindowObject();

    void loadfinished(bool);

    void setProgress(int i);

    void replyFinished(QNetworkReply* m_reply);

    void on_loginButton_clicked();

    void on_emaliEdit_lostFocus();

    void on_emaliEdit_textChanged(const QString &arg1);

    void on_passwdEdit_textChanged(const QString &arg1);

    void on_icodeEdit_textChanged(const QString &arg1);

    void sslErrorHandler(QNetworkReply* qnr, const QList<QSslError> & errlist);

private:
    Ui::LoginDialog *ui;
    QWebView *webView;
    bool inputFinished;
    bool isConnecting;
    bool isAccept;
    QNetworkReply *reply;
    QString showIcode;
    QString m_sessionKey;
//    QNetworkCookieJar *m_cookieJar;
    QString initUrl;
};

#endif // LOGINDIALOG_H
