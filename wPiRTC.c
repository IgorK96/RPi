#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <lcd.h>
#include <string.h>

#define SEC 0x02
#define MIN 0x03
#define HOU 0x04

#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16))
const char RTC = 0x51;

const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

char SENSOR = 29;
char BUTTON = 24;

int fd;
int hours, minutes, seconds;

char txt_seconds[4];
char txt_minutes[4];
char txt_hours[4];

int main()
{	
	if(wiringPiSetup() == -1) exit(1);
	pinMode (SENSOR, INPUT);
	pinMode (BUTTON, INPUT);
	pullUpDnControl(BUTTON, PUD_UP);

	int sensor_value = 0;
	int button_value = 1;
	int lcd_h;
	int seconds_tmp = 1;
	int dec_hours;
	int dec_minutes;
	int dec_seconds;
	int enable = 0;


	lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);

	fd = wiringPiI2CSetup(RTC);
	wiringPiI2CWriteReg8(fd, HOU, 0x23);
	wiringPiI2CWriteReg8(fd, MIN, 0x59);
	wiringPiI2CWriteReg8(fd, SEC, 0x00);

	while(1)
	{	if(enable == 0){
		sensor_value = digitalRead(SENSOR);
		if(sensor_value == 1)
		{
			enable = 1;
			dec_hours = hours;
			dec_minutes = minutes;
			dec_seconds = seconds;
		}else
			{
				//printf("Vrednost na senzoru: %d ",sensor_value);
				hours = changeHexToInt(wiringPiI2CReadReg8(fd, HOU)& 0x3f);  //Treba ograniciti na 24 nekako ?
				minutes = changeHexToInt(wiringPiI2CReadReg8(fd, MIN)& 0x7f);
				seconds = changeHexToInt(wiringPiI2CReadReg8(fd, SEC)& 0x7f);

				sprintf(txt_hours,"%d", hours);
				sprintf(txt_minutes,"%d", minutes);
				sprintf(txt_seconds,"%d", seconds);

				//printf("Vreme HH:MM:SS %d %d %d \n ", hours, minutes, seconds);
				lcdPosition(lcd_h, 0, 0);
				lcdPrintf(lcd_h,"No Movment");
				lcdPosition(lcd_h, 0, 1);
				lcdPrintf(lcd_h,"Time:");
				lcdPosition(lcd_h, 6, 1);
				lcdPrintf(lcd_h,txt_hours);
				lcdPosition(lcd_h, 8, 1);
				lcdPrintf(lcd_h,":");
				lcdPosition(lcd_h, 9, 1);
				lcdPrintf(lcd_h,txt_minutes);
				lcdPosition(lcd_h, 11, 1);
				lcdPrintf(lcd_h,":");
				lcdPosition(lcd_h, 12, 1);
				lcdPrintf(lcd_h,txt_seconds);
			}
		}else
			{	
				sprintf(txt_hours, "%d", dec_hours);
				sprintf(txt_minutes, "%d", dec_minutes);
				sprintf(txt_seconds, "%d", dec_seconds);
				
				lcdPosition(lcd_h, 0, 0);
				lcdPrintf(lcd_h, "MOVMENT DETECTED !");
				lcdPosition(lcd_h, 0, 1);
				lcdPrintf(lcd_h, "Time: ");
				lcdPosition(lcd_h, 6, 1);
				lcdPrintf(lcd_h,txt_hours);
				lcdPosition(lcd_h, 8, 1);
				lcdPrintf(lcd_h,":");
				lcdPosition(lcd_h, 9, 1);
				lcdPrintf(lcd_h,txt_minutes);
				lcdPosition(lcd_h, 11, 1);
				lcdPrintf(lcd_h,":");
				lcdPosition(lcd_h, 12, 1);
				lcdPrintf(lcd_h,txt_seconds);
				//printf("Movment detected at : %d %d %d", dec_hours, dec_minutes, dec_seconds);
				
				button_value = digitalRead(BUTTON);
				if(button_value == 0)
				{
					enable = 0;
					lcdClear(lcd_h);
				}
			}
	}
	return 0;
}
