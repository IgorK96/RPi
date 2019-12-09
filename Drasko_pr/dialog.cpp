#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setup_pins();
    ui->pushButton->hide();
    tmr = new QTimer(this);
    connect(tmr,SIGNAL(timeout()),this,SLOT(HC_SR04_READ()));
    tmr -> start(1000);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton1_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("1");
    ui->textEdit->moveCursor(QTextCursor::End);
}
void Dialog::on_pushButton_7_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("2");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog::on_pushButton_11_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("3");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog::on_pushButton_2_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("4");
    ui->textEdit->moveCursor(QTextCursor::End);

}

void Dialog::on_pushButton_6_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("5");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog::on_pushButton_10_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("6");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog::on_pushButton_3_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("7");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog::on_pushButton_8_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("8");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog::on_pushButton_12_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("8");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog::on_pushButton_4_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("#");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog::on_pushButton_5_clicked()
{
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText("0");
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Dialog::on_pushButton_9_clicked()
{
    password.clear();
    password = ui->textEdit->toPlainText();
    ui->textEdit->clear();
    if (password == OGpass)
    {
        access = 1;
    }

}
void Dialog::on_pushButton_clicked()
{
    OGpass.clear();
    if(ui->textEdit->toPlainText().length() < 4)
    {
       ui->textEdit->clear();  
        //show
    }
    else
    {
        OGpass = ui->textEdit->toPlainText();
        ui->textEdit->clear();
        reset = 1;
        //hide
    }
    
}
void Dialog::on_textEdit_textChanged()
{
    int maximum = 4;
    if(ui->textEdit->toPlainText().length() > maximum)
    {
        ui->textEdit->textCursor().deletePreviousChar();
    }
}

void Dialog::HC_SR04_READ()
{
    if(k == 10)
    {
        breach = 1;
    }
    ui->textEdit_3->clear();
    QString Sec = QString::number(k);
    ui->textEdit_3->insertPlainText(Sec);
    int echo, previousEcho, lowHigh, highLow;
    //int pass_req = 0;
    double startTime, stopTime, difference;
    double rangeCm;
    struct timeval start, end;


    lowHigh = highLow = echo = previousEcho = 0;
    bcm2835_gpio_write(TRIG, LOW);
    delay(100);
    bcm2835_gpio_write(TRIG, HIGH);
    usleep(10);
    bcm2835_gpio_write(TRIG, LOW);



    while( lowHigh == 0 || highLow == 0)
    {
        previousEcho = echo;
        echo = bcm2835_gpio_lev(ECHO);
        if( lowHigh == 0 && previousEcho == 0 && echo == 1)
        {
            lowHigh = 1;
            gettimeofday(&start, NULL);
        }
        if(lowHigh == 1 && previousEcho == 1 && echo == 0)
        {
            highLow = 1;
            gettimeofday(&end, NULL);
        }
    }
    stopTime = end.tv_usec;
    startTime = start.tv_usec;
    difference = (stopTime - startTime)/10000;
    rangeCm = difference * 170;// 340/2


    QString range = QString::number(rangeCm);
    ui->textEdit_2->clear();
    ui->textEdit_2->insertPlainText(range);
    if (access == 0){
        if (breach == 0){
            if(rangeCm <500)
            {
                ui->textEdit2->clear();
                ui->textEdit2->insertPlainText("ENTER THE PASSWORD OR LEAVE");
                k++; //WARRNING
                bcm2835_gpio_write(GREEN,LOW);
                bcm2835_gpio_write(BLUE,HIGH);
                bcm2835_gpio_write(RED,HIGH);

            }
            else
            {
                ui->textEdit2->clear();
                ui->textEdit2->insertPlainText("SYSTEM ALERT");
                k = 0; //ON ALERT
                bcm2835_gpio_write(GREEN,LOW);
                bcm2835_gpio_write(BLUE,HIGH);
                bcm2835_gpio_write(RED,LOW);
            }

        }else
        {   ui->textEdit2->clear();
            ui->textEdit2->insertPlainText("SYSTEM LOCKDOWN");
            k = 10; //NOT ALLOWED
            bcm2835_gpio_write(GREEN,LOW);
            bcm2835_gpio_write(BLUE,LOW);
            bcm2835_gpio_write(RED,HIGH);
            lockdown = 1;
        }
    }else
    {   if(lockdown != 1)
        {
            ui->pushButton->show();
            ui->textEdit_2->hide();
            ui->label->hide();
            ui->textEdit_3->hide();
            ui->label_2->hide();
            ui->label_3->resize(163,22);
            ui->label_3->clear();
            ui->label_3->setText("NEW PASSWORD");
            ui->textEdit2->clear();
            ui->textEdit2->insertPlainText("YOU HAVE FULL ACCESS");
            enable = 1;
            k = 0; //ALLOWED
            bcm2835_gpio_write(GREEN,HIGH);
            bcm2835_gpio_write(BLUE,LOW);
            bcm2835_gpio_write(RED,LOW);
            if (reset == 1)
            {
                k = 0;
                access = 0;
                enable = 0;
                reset = 0;
                ui->pushButton->hide();
                //hide
                ui->textEdit_2->show();
                ui->label->show();
                ui->textEdit_3->show();
                ui->label_2->show();
                ui->label_3->resize(111,22);
                ui->label_3->clear();
                ui->label_3->setText("PASSWORD:");
                ui->textEdit2->clear();
            }

        }
    }
    delay(100);


}

int Dialog::setup_pins()
{
    bcm2835_init();
    bcm2835_gpio_fsel(RED,BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(GREEN,BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(BLUE,BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(TRIG,BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ECHO,BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_write(GREEN,LOW);
    bcm2835_gpio_write(BLUE,HIGH);
    bcm2835_gpio_write(RED,LOW);

    return 0;
}



