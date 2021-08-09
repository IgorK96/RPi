#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <stdio.h>
#include <stdlib.h>


#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QWidget>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void Ball_Move();
    void on_reset_clicked();

private:
    Ui::Dialog *ui;
    QTimer *tmr;


    int setup_pins();
    int16_t ACCxyz[3];
    int16_t AmpedAcc[3];
    int8_t ball_move;
    int16_t ball_position[3];
    int16_t prev_ball_pos[3];
};

#endif // DIALOG_H
