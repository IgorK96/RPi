#include <wiringPi.h>

char LED[]={25,26,27,28};
char i;

int main(){
	wiringPiSetup();
	for(i=0;i<4;i++)
		pinMode(LED[i],OUTPUT);
	while(1){
		for(i=0;i<4;i++){
		digitalWrite(LED[i],i);
		delay(200);
		digitalWrite(LED[i],i);
		delay(200);
		}
	}
}
