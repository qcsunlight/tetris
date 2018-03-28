#include "tboard.h"
#include <QtWidgets>
#include <QDebug>

TBoard::TBoard(QWidget *parent)
     : QFrame(parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    countTemp=0;
    secondTemp=0;
    minuteTemp=0;
    sendTemp = 0;
    totaltimer= new QTimer(this);  //this说明是当前类对象的定时器
    //把信号与槽进行连接
    connect(totaltimer,SIGNAL(timeout()),this,SLOT(timeSlot()));
    connect(totaltimer,SIGNAL(timeout()),this,SLOT(slotSend()));

    isStarted = false;
    isPaused = false;
    clearBoard();
    nextT.setRandomType();
    resize(squareWidth()*10,squareWidth()*22);
}
void TBoard::timeSlot()
{
        countTemp+=1;
        if(countTemp==100)
        {
            countTemp=0;
            secondTemp+=1;
            if(secondTemp==60)
            {
                secondTemp=0;
                minuteTemp+=1;
            }
        }
        //把整数转换成字符串
        //QString msecondstr = QString::number(countTemp);
        QString minutestr = QString::number(minuteTemp);
        QString secondstr = QString::number(secondTemp);
        emit Display(minutestr,secondstr);
}

void TBoard::setNextTetrisLabel(QLabel *l)
{
    nextTLabel = l;
}
QSize TBoard::sizeHint() const
{
    return QSize(bWidth * 25 + frameWidth() * 2,
                 bHeight * 25 + frameWidth() * 2);
}
QSize TBoard::minimumSizeHint() const
{
    return QSize(bWidth * 5 + frameWidth() * 2,
                 bHeight * 5 + frameWidth() * 2);
}
void TBoard::start()
{
    if (isPaused)
        return;

    isStarted = true;
    isWait = false;
    numlines = 0;
    numtetris = 0;
    score = 0;
    level = 1;
    countTemp =0;
    secondTemp=0;
    minuteTemp=0;
    clearBoard();

    emit numlinesChanged(numlines);
    emit scoreChanged(score);
    emit levelChanged(level);

    newPiece();
    timer.start(timeoutTime(), this);
    totaltimer->start(10);
}
void TBoard::pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer.stop();
        totaltimer->stop();
    } else {
        timer.start(timeoutTime(), this);
        totaltimer->start(10);
    }
    update();
    emit changePause();
}
void TBoard::stop()
{
    return;
}

void TBoard::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);
    QPainter painter(this);
    painter.setPen(Qt::darkGray);

    QRect rect = contentsRect();
    if (isPaused) {
        painter.drawText(rect, Qt::AlignCenter, tr("暂停"));
        return;
    }
    for(int i=1;i<10;i++)
        painter.drawLine(i*squareWidth()+2,1,i*squareWidth()+2,contentsRect().bottom());
    for(int i=1;i<22;i++)
        painter.drawLine(1,i*squareWidth(),contentsRect().right(),i*squareWidth());

    QPixmap draw[8];
    draw[1].load(":/blocks/images/blocks/1.jpg");
    draw[2].load(":/blocks/images/blocks/2.jpg");
    draw[3].load(":/blocks/images/blocks/3.jpg");
    draw[4].load(":/blocks/images/blocks/4.jpg");
    draw[5].load(":/blocks/images/blocks/5.jpg");
    draw[6].load(":/blocks/images/blocks/6.jpg");
    draw[7].load(":/blocks/images/blocks/7.jpg");
    if (curT.getType() != N) {
        for (int i = 0; i < 4; ++i) {
            int x = curX + curT.getX(i);
            int y = curY - curT.getY(i);
            painter.drawPixmap(rect.left() + x * squareWidth(),
                       (bHeight-y-1)* squareWidth(),squareWidth(),squareWidth(),
                               draw[(int)curT.getType()]);
            }
        }
    for (int i = 0; i < bHeight; i++) {
        for (int j = 0; j < bWidth; j++) {
            TetrisType shape = shapeAt(j, i);
            if (shape != N)
                painter.drawPixmap(rect.left()+j*squareWidth(),(bHeight-i-1)*squareWidth(),squareWidth(),squareWidth(),draw[(int)shape]);
        }
    }
}
void TBoard::keyPressEvent(QKeyEvent *event)
{
    if (!isStarted || isPaused || curT.getType() == N) {
        QFrame::keyPressEvent(event);
        return;
    }
    switch (event->key()) {
    case Qt::Key_Left:
        tryMove(curT, curX - 1, curY);
        break;
    case Qt::Key_Right:
        tryMove(curT, curX + 1, curY);
        break;
    case Qt::Key_Down:
        oneLineDown();
        break;
    case Qt::Key_Up:
        curT.rotated();
        tryMove(curT, curX, curY);
        break;
    case Qt::Key_Space:
        dropDown();
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}
void TBoard::slotSend()
{
    sendTemp++;
    QString list;
    if(sendTemp == 73)
    {
        list = "";

        for(int i=0; i<10;i++)
        {
            for(int j=0;j<22;j++)
            {                
                list += ":";
                list += QString("%1").arg((int)board[j][i]);
            }
        }
        list += ":";
        list += QString("%1").arg((int)score);
        list += ":";
        list += QString("%1").arg((int)numlines);
        list += ":";
        list += QString("%1").arg((int)level);
        if (curT.getType() != N) {
            for (int i = 0; i < 4; ++i) {
//                int x = curX + curT.getX(i);
//                int y = curY - curT.getY(i);
                   list += ":";
                   list += QString("%1").arg((int)curT.getX(i));
                   list += ":";
                   list += QString("%1").arg((int)curT.getY(i));
                }
            list += ":";
            list += QString("%1").arg((int)curX);
            list += ":";
            list += QString("%1").arg((int)curY);
            list += ":";
            list += QString("%1").arg((int)curT.getType());
            }
        //qDebug()<<list;
        emit send(list);
        sendTemp = 0;
    }
}

void TBoard::slotReceive(QString a)
{
    QStringList list = a.split(QRegExp(":"));
    //qDebug() <<list;
    QString temp;
    for(int i=0; i<10;i++)
    {
        for(int j=0;j<22;j++)
        {
            temp = list.at(22*i+j+1);
            board[j][i]= (TetrisType)temp.toInt();
            //qDebug()<<board[j][i];
        }
    }
    temp = list.at(10*22+1);
    score = temp.toInt();
    emit scoreChanged(score);
    temp = list.at(10*22+2);
    numlines = temp.toInt();
    emit numlinesChanged(numlines);
    temp = list.at(10*22+3);
    level = temp.toInt();
    emit levelChanged(level);
    int boardend = 10*22+3;
    if(list.length()>boardend+1)
    {
        for(int i=0;i<4;i++)
        {
            temp = list.at(boardend+2*i+1);
            curT.setX(i,temp.toInt());
            temp = list.at(boardend+2*i+2);
            curT.setY(i,temp.toInt());
        }
        temp = list.at(boardend+9);
        curX = temp.toInt();
        temp = list.at(boardend+10);
        curY = temp.toInt();
        temp = list.at(boardend+11);
        curT.setType((TetrisType)temp.toInt());
    }

    update();
}

void TBoard::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        if (isWait) {
            isWait = false;
            newPiece();
            timer.start(timeoutTime(), this);
        } else {
            oneLineDown();
        }
    } else {
        QFrame::timerEvent(event);
    }
}
void TBoard::clearBoard()
{
    for(int i=0;i<bHeight;i++)
    {
        for(int j=0;j<bWidth;j++)
            board[i][j] = N;
    }
}

void TBoard::dropDown()
{
    int dropHeight = 0;
    int newY = curY;
    while (newY > 0) {
        if (!tryMove(curT, curX, newY - 1))
            break;
        --newY;
        ++dropHeight;
    }
    pieceDropped(dropHeight);
}
void TBoard::oneLineDown()
{
    if (!tryMove(curT, curX, curY - 1))
        pieceDropped(0);
}
void TBoard::pieceDropped(int dropHeight)
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + curT.getX(i);
        int y = curY - curT.getY(i);
        shapeAt(x, y) = curT.getType();
    }

    ++numtetris;
    if (numtetris % 30 == 0) {
        ++level;
        timer.start(timeoutTime(), this);
        emit levelChanged(level);
    }

    score += dropHeight + 10;
    emit scoreChanged(score);
    removeFullLines();

    if (!isWait)
        newPiece();
}
void TBoard::removeFullLines()
{
    int numFullLines = 0;

    for (int i = bHeight - 1; i >= 0; --i) {
        bool lineIsFull = true;

        for (int j = 0; j < bWidth; ++j) {
            if (shapeAt(j, i) == N) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
            ++numFullLines;
            for (int k = i; k < bHeight - 1; ++k) {
                for (int j = 0; j < bWidth; ++j)
                    shapeAt(j, k) = shapeAt(j, k + 1);
            }

            for (int j = 0; j < bWidth; ++j)
                shapeAt(j, bHeight - 1) = N;
        }
    }
    if (numFullLines > 0) {
        numlines += numFullLines;
        score += 100 * numFullLines;
        emit numlinesChanged(numlines);
        emit scoreChanged(score);

        timer.start(500, this);
        isWait = true;
        curT.setTetrisType(N);
        update();
    }
}
void TBoard::newPiece()
{
    curT = nextT;
    //qDebug()<<curT.getType();
    nextT.setRandomType(); ;
    //qDebug()<<nextT.getType();
    showNextPiece();
    curX = bWidth / 2 + 1;
    curY = bHeight - 1 + curT.getMinY();
    //qDebug()<<curX<<curY;

    if (!tryMove(curT, curX, curY)) {
        curT.setTetrisType(N);
        timer.stop();
        isStarted = false;
    }
}
void TBoard::showNextPiece()
{
    if (!nextTLabel)
        return;

    int dx = nextT.getMaxX() - nextT.getMinX() + 1;
    int dy = nextT.getMaxY() - nextT.getMinY() + 1;
    QPixmap draw[8];
    draw[1].load(":/blocks/images/blocks/1.jpg");
    draw[2].load(":/blocks/images/blocks/2.jpg");
    draw[3].load(":/blocks/images/blocks/3.jpg");
    draw[4].load(":/blocks/images/blocks/4.jpg");
    draw[5].load(":/blocks/images/blocks/5.jpg");
    draw[6].load(":/blocks/images/blocks/6.jpg");
    draw[7].load(":/blocks/images/blocks/7.jpg");

    QPixmap pixmap(dx * squareWidth(), dy * squareWidth());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextTLabel->palette().background());
    for (int i = 0; i < 4; ++i) {
        int x = nextT.getX(i) - nextT.getMinX();
        int y = nextT.getY(i) - nextT.getMinY();
        painter.drawPixmap(x*squareWidth(),y*squareWidth(),squareWidth(),squareWidth(),draw[(int)nextT.getType()]);
    }
    nextTLabel->setPixmap(pixmap);
}
bool TBoard::tryMove(const Tetris &newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.getX(i);
        int y = newY - newPiece.getY(i);
        //qDebug()<<"i:"<<i<<"x:"<<x<<"y:"<<y;
        if (x < 0 || x >= bWidth || y < 0 || y >= bHeight)
            return false;
        if (shapeAt(x, y) != N)
            return false;
    }
    curT = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}
