#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);
	temperature();

}

Dialog::~Dialog()
{
	delete ui;
}

Dialog::temperature()
{
	FILE *ft;
	char tekst[100];
	ft=fopen("/sys/bus/w1/devices/28-00000???????/w1_slave","r");

	if(ft==NULL) return 0;

	int i=0;

	for(i=0;i<22;i++)//samo temperatura
		fscanf(ft,"%s", tekst);

	fclose(ft);

	//obrisati „t=”
	for(i=0;i<10;i++) tekst[i]=tekst[i+2];

	int temp=atoi(tekst); //prebaci u double
	double tem=(double)temp/1000;

	return tem;
	delay(1000);
	ui->lcdNumber->display(tem);
}
