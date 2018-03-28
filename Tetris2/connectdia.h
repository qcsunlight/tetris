#ifndef CONNECTDIA_H
#define CONNECTDIA_H

#include <QDialog>
#include <QString>
#include <QHostAddress>
#include <QTcpSocket>
#include <QMessageBox>

namespace Ui {
class connectDia;
}

class connectDia : public QDialog
{
    Q_OBJECT

public:
    explicit connectDia(QWidget *parent = 0);
    ~connectDia();
    bool isDigitStr(QString src);
private slots:
    void receiveshow();
    void on_returnbtn_clicked();
    void on_okbtn_clicked();
//    void slotConnected();
//    void slotEnter();
//    void slotDisconnected();
//    void dataReceived();
signals:
    void logindiaShow();
    void doubleDiaShow(QString, QString, QString);
private:
    Ui::connectDia *ui;

//    bool status;
//    int port;
//    QHostAddress *serverIP;
//    QString userName;
//    QTcpSocket *tcpSocket;
};

#endif // CONNECTDIA_H
