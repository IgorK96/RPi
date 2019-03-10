#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

int main(){
	int i=0, taster_pritisnut1=0, taster_pritisnut2=0;
	int r_value1, r_value2;

	if(wiringPiSetup() == -1)
		exit(1);

	pinMode(21,INPUT);
	pinMode(22,INPUT);
	pinMode(25,OUTPUT);

	digitalWrite(25,HIGH);

	if(softPwmCreate(28,0,100) != 0) //Omogucava realizaciju PWM na odabranom pinu (pin,inicij V, pwmOpseg)
		exit(2);

	i = 0;
	taster_pritisnut1 = 0;
	taster_pritisnut2 = 0;

	while(1){
		r_value1 = digitalRead(21);  //procitaj vrednost KEY0
		r_value2 = digitalRead(22);  //procitaj vrednost KEY1
		digitalWrite(25,r_value1);
		digitalWrite(25,r_value2);
		//Cekamo na pritisak tastera
		if(!r_value1 && !taster_pritisnut1){
			taster_pritisnut1 = 1;

			i += 20;
			if(i > 100) i = 100;

			printf("i = %d\n",i);
			fflush(stdout);

			softPwmWrite(28,1);//PWM na pinu i vrednost
		}
		if(!r_value2 && !taster_pritisnut2){
			taster_pritisnut2 = 1;

			i -= 20;
			if(i < 0) i = 0;

			printf("i = %d\n",i);
			fflush(stdout);

			softPwmWrite(28,1);
		}
		//Cekamo da se taster otpusti
		if(r_value1) taster_pritisnut1 = 0;

		if(r_value2) taster_pritisnut2 = 0;

	}
}
