#include "logindia.h"
#include "connectdia.h"
#include "singaldia.h"
#include "doubledia.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDia d;
    SingalDia w;
    connectDia c;
    DoubleDia dd;
    d.show();
    QObject::connect(&d,SIGNAL(mainwindowShow()),&w,SLOT(receiveshow()));
    QObject::connect(&d,SIGNAL(connectdiaShow()),&c,SLOT(receiveshow()));
    QObject::connect(&c,SIGNAL(logindiaShow()),&d,SLOT(receiveshow()));
    QObject::connect(&w,SIGNAL(showloginDia()),&d,SLOT(receiveshow()));
    QObject::connect(&c,SIGNAL(doubleDiaShow(QString,QString,QString)),&dd,SLOT(receiveshow(QString,QString,QString)));
    QObject::connect(&dd,SIGNAL(showmain()),&d,SLOT(receiveshow()));

    return a.exec();
}
