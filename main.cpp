#include <QtGui/QApplication>
#include <QTextCodec>
#include "renrentest.h"
#include "logindialog.h"
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);

    LoginDialog *loginDialog = new LoginDialog;
    if (loginDialog->exec() == QDialog::Accepted)
    {
        QString sessionKey = loginDialog->sessionKey();

        renrentest m_renrentest(sessionKey);
        m_renrentest.show();

        return a.exec();
    }
    else
    {
        return 0;
    }
}
