#ifndef TBOARD_H
#define TBOARD_H

#include "tetris.h"
#include <QBasicTimer>
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QFrame>
#include <QLabel>
#include <QPointer>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QRect>

class TBoard : public QFrame
{
    Q_OBJECT
public:
    TBoard(QWidget *parent = 0);

    void setNextTetrisLabel(QLabel *l);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void start();
    void pause();
    void stop();
    void timeSlot();
    void slotReceive(QString);
    void slotSend();
signals:
    void changePause();
    void scoreChanged(int score);
    void levelChanged(int level);
    void numlinesChanged(int numlines);
    void send(QString);
    void Display(QString,QString);
protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);
private:
    TetrisType &shapeAt(int x, int y) { return board[y][x]; }
    int timeoutTime() { return 1000 / (1 + level); }
    int squareWidth() { return contentsRect().width() / bWidth; }
    void clearBoard();
    void dropDown();
    void oneLineDown();
    void pieceDropped(int dropHeight);
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    bool tryMove(const Tetris &newPiece, int newX, int newY);
private:
    int score;
    int level;
    int numlines;
    int numtetris;
    int curX;
    int curY;

    QTimer *totaltimer;
    int minuteTemp;         //Minute
    int secondTemp;         //Second
    int countTemp;
    int sendTemp;
    int key;

    bool isStarted;
    bool isPaused;
    bool isWait;
    Tetris curT;
    Tetris nextT;
    QBasicTimer timer;
    QPointer<QLabel> nextTLabel;

    static const int bWidth = 10;
    static const int bHeight = 22;
    TetrisType board[bHeight][bWidth];
};

#endif // TBOARD_H
