#ifndef LOGINDIA_H
#define LOGINDIA_H

#include <QDialog>
#include <QMouseEvent>
#include <QSound>
#include <QDebug>

namespace Ui {
class LoginDia;
}

class LoginDia : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDia(QDialog *parent = 0);
    ~LoginDia();
signals:
    void mainwindowShow();
    void connectdiaShow();
public slots:
    void on_signalbtn_clicked();
    void on_doublebtn_clicked();
    void receiveshow();
private:
    Ui::LoginDia *ui;
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    int enterSAreaFlag = 0;
    int enterDAreaFlag = 0;
    QRect m_areaMovable;//可移动窗口的区域，鼠标只有在该区域按下才能移动窗口
    bool m_bPressed = false;//鼠标按下标志（不分左右键）
    QPoint m_ptPress;//鼠标按下的初始位置
    QRect areaSingalBtn;//单人游戏按钮区域
    QRect areaDoubleBtn;//双人游戏按钮区域
    QSound *sound = new QSound(":/sounds/catch.wav", this);
};

#endif // LOGINDIA_H
