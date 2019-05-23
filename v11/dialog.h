#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QtGlobal>
#include <QWidget>
#include <QDialog>

#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16) )

#define SEC 0x02

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void P8563_Readtime();
    void temperature();

private:
    Ui::Dialog *ui;

    int s;
            int rtc;
            unsigned char WriteBuf[6];
            unsigned char ReadBuf;
            unsigned char g8563_Store[3];
            unsigned char init8563_Store[3];
            QTimer *tmr;
            void P8563_init();

            void P8563_settime();
};

#endif // DIALOG_H
