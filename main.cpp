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

//        LoginDialog *loginDialog = new LoginDialog;
//        if (loginDialog->exec() == QDialog::Accepted)
//        {
//            QString sessionKey = loginDialog->sessionKey();

//            renrentest m_renrentest(sessionKey);
//            m_renrentest.show();

//            return a.exec();
//        }
//        else
//        {
//            return 0;
//        }

    //"6.c757661bf410e6d36599907b0380a22a.2592000.1335405600-448992126";
    //"6.a99bb66a4b2e95ffa43d1506c8e7e200.2592000.1337446800-450631571"
    renrentest m_renrentest("6.a99bb66a4b2e95ffa43d1506c8e7e200.2592000.1337446800-450631571");
//    renrentest m_renrentest("6.c757661bf410e6d36599907b0380a22a.2592000.1335405600-448992126");
    m_renrentest.show();

    return a.exec();
}
