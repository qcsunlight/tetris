#include "logindia.h"
#include "ui_logindia.h"

LoginDia::LoginDia(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::LoginDia)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    connect(ui->quitbt,SIGNAL(clicked()),this,SLOT(close()));
    m_areaMovable = QRect(0,0,width()-20,20);
    setWindowTitle(tr("俄罗斯方块"));

    areaSingalBtn = QRect(ui->singalbt->pos(),QSize(ui->singalbt->rect().width(),ui->singalbt->rect().height()));
    areaDoubleBtn = QRect(ui->doublebt->pos(),QSize(ui->doublebt->rect().width(),ui->doublebt->rect().height()));
    //connect(ui->singalbt,SIGNAL(clicked(bool)),this,SLOT(btnSignalPressed()));
    connect(ui->singalbt,SIGNAL(clicked()),this,SLOT(on_signalbtn_clicked()));
    connect(ui->doublebt,SIGNAL(clicked()),this,SLOT(on_doublebtn_clicked()));

    setMouseTracking(true);
    ui->singalbt->setMouseTracking(true);
    ui->doublebt->setMouseTracking(true);
}

LoginDia::~LoginDia()
{
    delete ui;
    delete sound;
}
void LoginDia::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bPressed)
    {
        move(pos() + event->pos() - m_ptPress);
    }
    if(areaSingalBtn.contains(event->pos()))
    {
        ui->singalbt->setStyleSheet("border-image: url(:/images/2.jpg);");
        if(enterSAreaFlag==0)
        {
        sound->play();
        enterSAreaFlag = 1;
        }
    }else
    {
        ui->singalbt->setStyleSheet("border-image: url(:/images/1.jpg);");
        enterSAreaFlag = 0;
    }
    if(areaDoubleBtn.contains(event->pos()))
    {
        ui->doublebt->setStyleSheet("border-image: url(:/images/4.jpg);");
        if(enterDAreaFlag==0)
        {
        sound->play();
        enterDAreaFlag = 1;
        }
    }else
    {
        ui->doublebt->setStyleSheet("border-image: url(:/images/3.jpg);");
        enterDAreaFlag = 0;
    }

}
void LoginDia::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_ptPress = e->pos();
        m_bPressed = m_areaMovable.contains(m_ptPress);
    }
}
void LoginDia::mouseReleaseEvent(QMouseEvent *)
{
    m_bPressed = false;
}
void LoginDia::on_signalbtn_clicked()
{
    this->close();
    emit mainwindowShow();
}
void LoginDia::on_doublebtn_clicked()
{
    this->close();
    emit connectdiaShow();
}
void LoginDia::receiveshow()
{
    this->show();
}
