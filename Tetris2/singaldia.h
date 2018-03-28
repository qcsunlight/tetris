#ifndef SINGALDIA_H
#define SINGALDIA_H

#include "tboard.h"
#include <QDialog>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QString>

namespace Ui {
class SingalDia;
}

class SingalDia : public QDialog
{
    Q_OBJECT

public:
    explicit SingalDia(QWidget *parent = 0);
    ~SingalDia();
signals:
    void showloginDia();
public slots:
    void receiveshow();
    void on_backbtn_clicked();
    void changePauseTitle();
    void showTotalTime(QString, QString);
private:
    Ui::SingalDia *ui;
    TBoard *board;
};

#endif // SINGALDIA_H
