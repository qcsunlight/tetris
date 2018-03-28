#ifndef DOUBLEDIA_H
#define DOUBLEDIA_H

#include <QDialog>
#include "tboard.h"
#include <QString>
#include <QHostAddress>
#include <QTcpSocket>

namespace Ui {
class DoubleDia;
}

class DoubleDia : public QDialog
{
    Q_OBJECT

public:
    explicit DoubleDia(QWidget *parent = 0);
    ~DoubleDia();
public slots:
    void receiveshow(QString, QString, QString);
    void receivedata(QString);
    void on_btnback_clicked();
    void on_btnout_clicked();
    void on_btnready_clicked();

    void slotConnected();
    void slotDisconnected();
    void dataReceived();
    void slotLeave();
    void slotSend(QString);
signals:
    void showmain();
    void datareceive(QString);

private:
    Ui::DoubleDia *ui;

    TBoard *boarda;
    TBoard *boardb;

    bool status;
    int sport;
    QHostAddress *serverIP;
    QString userName;
    QTcpSocket *tcpSocket;
};

#endif // DOUBLEDIA_H
