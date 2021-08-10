#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>

char KEY[]={21,22,23,24};


int main()
{
	if(wiringPiSetup()<0) return 1;
	int n;
int i;
	for(i =0;i<4;i++)
	{
		pinMode(KEY[i],INPUT);
		pullUpDnControl(KEY[i],PUD_UP);
	}
	while(1)
	{
		for(i = 0;i<4;i++){
			n = digitalRead(KEY[i]);
			printf("KEY %d ima vrednost %d",i,n); 
			delay(500);
		}
	}
return 0;
}
