#include "doubledia.h"
#include "ui_doubledia.h"
#include <QMessageBox>

DoubleDia::DoubleDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DoubleDia)
{
    ui->setupUi(this);

    boarda = new TBoard;
    boardb = new TBoard;
    boarda->setFrameStyle(QFrame::Box | QFrame::Raised);
    boarda->setFocusPolicy(Qt::StrongFocus);
    boardb->setFrameStyle(QFrame::Box | QFrame::Raised);

    ui->horizontalLayout->addWidget(boarda);
    ui->horizontalLayout->addWidget(boardb);
    boarda->setNextTetrisLabel(ui->anext);
    ui->btnstart->setEnabled(false);

    status = false;
    serverIP = new QHostAddress();

    connect(boarda,SIGNAL(scoreChanged(int)),ui->ascore,SLOT(display(int)));
    connect(boarda,SIGNAL(levelChanged(int)),ui->alevel,SLOT(display(int)));
    connect(boarda,SIGNAL(numlinesChanged(int)),ui->alines,SLOT(display(int)));
    connect(boardb,SIGNAL(scoreChanged(int)),ui->bscore,SLOT(display(int)));
    connect(boardb,SIGNAL(levelChanged(int)),ui->blevel,SLOT(display(int)));
    connect(boardb,SIGNAL(numlinesChanged(int)),ui->blines,SLOT(display(int)));
    connect(boarda,SIGNAL(send(QString)),this,SLOT(slotSend(QString)));
    connect(ui->btnstart,SIGNAL(clicked(bool)),boarda,SLOT(start()));
    connect(ui->btnback,SIGNAL(clicked(bool)),this,SLOT(on_btnback_clicked()));
    connect(ui->btnout,SIGNAL(clicked(bool)),this,SLOT(on_btnout_clicked()));


    connect(this,SIGNAL(datareceive(QString)),this,SLOT(receivedata(QString)));

}

DoubleDia::~DoubleDia()
{
    delete ui;
    delete boarda;
    delete boardb;
}
void DoubleDia::on_btnready_clicked()
{
//    int length=0;
//    QString msg=userName+tr(":ready");
//    if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg.length())
//    {
//        return;
//    }
    ui->btnstart->setEnabled(true);
}

void DoubleDia::receiveshow(QString host, QString port, QString name)
{
    this->show();
    ui->lhost->setText(host);
    ui->lport->setText(port);
    ui->aname->setText(name);

    if(!status)
    {
        QString ip = host;
        if(!serverIP->setAddress(ip))
        {
            QMessageBox::information(NULL,tr("error"),tr("server ip address error!"));
            return;
        }
        userName = name;
        sport = port.toInt();

        tcpSocket = new QTcpSocket(this);
        connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
        connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
        connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));

        tcpSocket->connectToHost(*serverIP,sport);

        status=true;
    }
}
void DoubleDia::slotConnected()
{
//    int length=0;
//    QString msg=userName+tr(":Enter");
//    if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg.length())
//    {
//        return;
//    }
}
void DoubleDia::slotDisconnected()
{

}
void DoubleDia::slotSend(QString a)
{
    if(a.isEmpty())
        return;
    QString msg=userName+a;
    //QString msg = a;

    tcpSocket->write(msg.toLatin1(),msg.length());
}

void DoubleDia::slotLeave()
{
    int length=0;
    QString msg=userName+tr(":Leave");
    if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg. length())
    {
        return;
    }

    tcpSocket->disconnectFromHost();

    status=false;
}

void DoubleDia::dataReceived()
{
    while(tcpSocket->bytesAvailable()>0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());

        tcpSocket->read(datagram.data(),datagram.size());

        QString msg=datagram.data();
        //contentListWidget->addItem(msg.left(datagram.size()));
        emit datareceive(msg);
    }
}

void DoubleDia::on_btnout_clicked()
{
    this->close();
}

void DoubleDia::receivedata(QString data)
{
    int len = userName.length();
    QString name = data.left(len);
    if(name != userName)
    {
//        if(data.mid(len+1,5) == "ready")
//            ui->btnstart->setEnabled(true);
//        else
//        {
            boardb->slotReceive(data);
            ui->bname->setText(name);
//        }
    }
}

void DoubleDia::on_btnback_clicked()
{
    this->close();
    emit showmain();
}
