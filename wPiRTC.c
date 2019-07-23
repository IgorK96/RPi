#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <lcd.h>
#include <string.h>

#define SEK 0x02
#define MIN 0x03
#define SAT 0x04

#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16))
const char RTC = 0x51;

const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

char SENZOR = 29;

int fd;
int sati, minuti, sekunde;

char txt_sekunde[4];
char txt_minuti[4];
char txt_sati[4];
int main()
{
	wiringPiSetup();
	pinMode (SENZOR, INPUT);
	int sensor_value = 0;
	int lcd_h;
	int sekunda_tmp = 1;
	if(wiringPiSetup() == -1) exit(1);

	lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
	lcdPosition(lcd_h, 0, 0);
	lcdPrintf(lcd_h,"Vreme detekcije: ");

	fd = wiringPiI2CSetup(RTC);
	wiringPiI2CWriteReg8(fd, SEK, 0x00);
	wiringPiI2CWriteReg8(fd, MIN, 0x59);
	wiringPiI2CWriteReg8(fd, SAT, 0x08);

	wiringPiSetup();
	while(1)
	{
		sensor_value = digitalRead(SENZOR);
		if(sensor_value == 1)
		{
			printf("DETEKCIJA POKRETA!!!");

		}else{
		printf("Vrednost na senzoru: %d ",sensor_value);
		sati = changeHexToInt(wiringPiI2CReadReg8(fd, SAT)); 
		minuti = changeHexToInt(wiringPiI2CReadReg8(fd, MIN));
		sekunde = changeHexToInt(wiringPiI2CReadReg8(fd, SEK));

		sprintf(txt_sati,"%d", sati);
		sprintf(txt_minuti,"%d", minuti);
		sprintf(txt_sekunde,"%d", sekunde);

		printf("Vreme HH:MM:SS %d %d %d \n ", sati, minuti, sekunde);

		lcdPosition(lcd_h, 0, 1);
		lcdPrintf(lcd_h,txt_sati);
		lcdPosition(lcd_h, 3, 1);
		lcdPrintf(lcd_h,":");
		lcdPosition(lcd_h, 4, 1);
		lcdPrintf(lcd_h,txt_minuti);
		lcdPosition(lcd_h, 7, 1);
		lcdPrintf(lcd_h,":");
		lcdPosition(lcd_h, 8, 1);
		lcdPrintf(lcd_h,txt_sekunde);
		}
	}
	return 0;
}
