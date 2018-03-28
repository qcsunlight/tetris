#include "connectdia.h"
#include "ui_connectdia.h"
#include <QDebug>

connectDia::connectDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectDia)
{
    ui->setupUi(this);
    connect(ui->closebtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->returnbtn,SIGNAL(clicked()),this,SLOT(on_returnbtn_clicked()));
    setWindowFlags(Qt::FramelessWindowHint);
    ui->host->setText(tr("127.0.0.1"));
    ui->port->setText(tr("8010"));
//    status = false;
//    port = 8010;
//    serverIP = new QHostAddress();
//    connect(ui->okbtn,SIGNAL(clicked(bool)),this,SLOT(slotEnter()));
}
connectDia::~connectDia()
{
    delete ui;
}
void connectDia::on_okbtn_clicked()
{
    QString host = ui->host->text();
    QString port = ui->port->text();
    QString name = ui->name->text();
    if(host.isEmpty()||port.isEmpty()||name.isEmpty())
        QMessageBox::information(NULL,tr("错误"),tr("信息输入不完整！"));
    else if (!isDigitStr(port))
        QMessageBox::information(NULL,tr("错误"),tr("请输入一个正确的端口号！"));
    //qDebug()<<host<<port<<name;
    else{
    this->close();
    emit doubleDiaShow(host,port,name);
    }
}

bool connectDia::isDigitStr(QString src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
    const char *s = ba.data();

    while(*s && *s>='0' && *s<='9') s++;

    if(*s)
        return false;
    else
        return true;
}

//void connectDia::slotEnter()
//{
//    if(!status)
//    {
//        QString ip = "127.0.0.1";
//        if(!serverIP->setAddress(ip))
//        {
//            QMessageBox::information(this,tr("error"),tr("server ip address error!"));
//            return;
//        }

//        if(ui->name->text()=="")
//        {
//            QMessageBox::information(this,tr("error"),tr("User name error!"));
//            return;
//        }

//        userName=ui->name->text();

//        tcpSocket = new QTcpSocket(this);
//        connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
//        connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
//        connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));

//        tcpSocket->connectToHost(*serverIP,port);

//        status=true;
//    }
//    else
//    {
//        int length=0;
//        QString msg=userName+tr(":Leave");
//        if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg. length())
//        {
//            return;
//        }

//        tcpSocket->disconnectFromHost();

//        status=false;
//    }
//    emit doubleDiaShow();
//}

//void connectDia::slotConnected()
//{
//    int length=0;
//    QString msg=userName+tr(":Enter");
//    if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg.length())
//    {
//        return;
//    }
//}

//void connectDia::slotDisconnected()
//{
//    int length=0;
//    QString msg=userName+tr(":Enter");
//    if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg.length())
//    {
//        return;
//    }
//}

//void connectDia::dataReceived()
//{
//    while(tcpSocket->bytesAvailable()>0)
//    {
//        QByteArray datagram;
//        datagram.resize(tcpSocket->bytesAvailable());

//        tcpSocket->read(datagram.data(),datagram.size());

//        QString msg=datagram.data();
//        qDebug()<<msg;
//        //qDebug() << msg.left(datagram.size());
//    }
//}

void connectDia::receiveshow()
{
    this->show();
}
void connectDia::on_returnbtn_clicked()
{
    this->close();
    emit logindiaShow();
}
