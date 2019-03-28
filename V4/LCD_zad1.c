// lcd1602.c
// kompajlirati sa -lwiringPi -lwiringPiDev
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <lcd.h>
// dodela vrednosti za konkretne pinove
// prema gornjoj tabeli i semi DVK512
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

double temperatura(void)//očitavanje temperature
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
};

int main(){
  double tren_temp;
  char temp_s[10]; 
  
  int lcd_h;
  if (wiringPiSetup() < 0){
    fprintf (stderr, "Greška pri inicijalizaciji: %s\n", strerror (errno)) ;
    return 1 ;
  }
  lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
  
  lcdPosition(lcd_h, 0,0);
  lcdPrintf(lcd_h,"Trenutna temp: ");
  while(1){
    
    tren_temp = temperatura();
    sprintf(temp_s,"%.2f", tren_temp);
    lcdPosition(lcd_h, 0,1);
    lcdPrintf(lcd_h, temp_s);
  
    delay(400);
  }	  
}
