#include "singaldia.h"
#include "ui_singaldia.h"

#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QString>

SingalDia::SingalDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingalDia)
{
    ui->setupUi(this);
    connect(ui->backbtn,SIGNAL(clicked()),this,SLOT(on_backbtn_clicked()));
    connect(ui->quitbtn,SIGNAL(clicked()),qApp,SLOT(quit()));
    board = new TBoard;
    board->setFrameStyle(QFrame::Box | QFrame::Raised);
    board->setFocusPolicy(Qt::StrongFocus);
    board->setNextTetrisLabel(ui->label);
    ui->verticalLayout->addWidget(board);
    connect(ui->beginbtn,SIGNAL(clicked()),board,SLOT(start()));
    connect(ui->pausebtn,SIGNAL(clicked()),board,SLOT(pause()));
    connect(board,SIGNAL(changePause()),this,SLOT(changePauseTitle()));
    connect(ui->backbtn,SIGNAL(clicked(bool)),board,SLOT(stop()));
    connect(board,SIGNAL(scoreChanged(int)),ui->scorel,SLOT(display(int)));
    connect(board,SIGNAL(numlinesChanged(int)),ui->linesl,SLOT(display(int)));
    connect(board,SIGNAL(levelChanged(int)),ui->levell,SLOT(display(int)));
    connect(board,SIGNAL(Display(QString,QString)),this,SLOT(showTotalTime(QString, QString)));
}
SingalDia::~SingalDia()
{
    delete ui;
}
void SingalDia::receiveshow()
{
    this->show();
}
void SingalDia::on_backbtn_clicked()
{
    this->close();
    emit showloginDia();
}
void SingalDia::changePauseTitle()
{
    QString text = ui->pausebtn->text();
    int rel = QString::compare(text,tr("暂停"));
    if(rel == 0)
    {
        ui->pausebtn->setText(tr("恢复"));
    }
    else
    ui->pausebtn->setText(tr("暂停"));
}

void SingalDia::showTotalTime(QString a, QString b)
{
    QString show = a + ":" + b ;//+ ":" + c;
    ui->totaltime->display(show);
}
