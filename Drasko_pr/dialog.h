#ifndef DIALOG_H
#define DIALOG_H

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <bcm2835.h>
#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QWidget>

#define TRIG 23
#define ECHO 24
#define RED 16
#define GREEN 20
#define BLUE 26
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString newpass;

private slots:
    void HC_SR04_READ();
    void on_pushButton_9_clicked();

    void on_pushButton1_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_textEdit_textChanged();


    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    QString password;
    QString OGpass = "0000";
    QTimer *tmr;
    int permission;
    int no_tries;
    double permited_range;
    int setup_pins();
    int k = 0;
    int breach = 0;
    int access = 0;
    int lockdown = 0;
    int enable = 0;
    int reset = 0;
};

#endif // DIALOG_H
