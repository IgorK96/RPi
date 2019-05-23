#include "dialog.h"
#include "ui_dialog.h"

int rtcc;
int fd, adcVal,svetlo;
const char PCF8591 = 0x48; // adresa

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    wiringPiSetup();
    fd = wiringPiI2CSetup(PCF8591);
    rtc=wiringPiI2CSetup(0x51);
    tmr = new QTimer(this);
    connect(tmr,SIGNAL(timeout()),this,SLOT(senzori()));
    tmr -> start(1000);
    ui->dial->setDisabled(true);
    ui->verticalScrollBar->setDisabled(true);

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::senzori()
{
        FILE *ft;
        char tekst[100];
        ft=fopen("/sys/bus/w1/devices/28-000008832b6c/w1_slave","r");

        if(ft==NULL) return;

        int i=0;

        for(i=0;i<22;i++)//samo temperatura
            fscanf(ft,"%s", tekst);

        fclose(ft);

        //obrisati „t=”
        for(i=0;i<10;i++) tekst[i]=tekst[i+2];

        int temp=atoi(tekst); //prebaci u double
        double tem=(double)temp/1000;

        ui->lcdNumber->display(tem);

        int napon,sv;
        wiringPiI2CReadReg8(fd, PCF8591 + 3) ; // dummy
        adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 3) ;
        // upisi tu vrednost u DAC reg, 0x04
        wiringPiI2CWriteReg8 (fd, PCF8591 + 4, adcVal) ;
        // procitaj DAC preko AIN2
        wiringPiI2CReadReg8(fd, PCF8591 + 2) ; // dummy
        adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 2);
        napon = (3.3/255)*adcVal;
        ui->dial->setValue(napon);

        wiringPiI2CReadReg8(fd, PCF8591);
        svetlo =wiringPiI2CReadReg8(fd, PCF8591);
        sv = svetlo*(3.3/255);
        ui->verticalScrollBar->setValue(sv);




}



void Dialog::P8563_init()
{

   g8563_Store[0]=init8563_Store[0];

   P8563_settime();

   //inicijalizacija RTC-a
   WriteBuf[0] = 0x0;
   WriteBuf[1] = 0x00; //normalni rezim rada

  wiringPiI2CWriteReg8(rtc, 0x00, 0x00);
}

void Dialog::P8563_Readtime()
{
   unsigned char time[7];
   WriteBuf[0] = SEC;
   int p;
   wiringPiI2CWrite(rtc, SEC);
   p=read(rtc,time, 7);

   g8563_Store[0] = time[0] & 0x7f;//sek

   g8563_Store[0] = changeHexToInt(g8563_Store[0]);

   //for(int i=0;i<=2;i++)

    QString s_str;
    s_str = QString::number(g8563_Store[0]);


}

void Dialog::P8563_settime()
{

   wiringPiI2CWriteReg8(rtc, 0x02, g8563_Store[0]);

}
