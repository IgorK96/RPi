#include <stdint.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <math.h>

#define RED 16
#define GREEN 20
#define BLUE 26
#define PI 3.141592654

uint16_t control = 0;
uint16_t start = 0x01;
uint16_t end = 0x00;
uint16_t chan = 0x00;
uint16_t x1_value = 0x00;
uint16_t center_x1_pos;
uint16_t center_x2_pos;
uint16_t center_y1_pos;
uint16_t center_y2_pos;
uint16_t y1_value = 0x00;
uint16_t sw1_value = 0x00;
uint16_t x2_value = 0x00;
uint16_t y2_value = 0x00;
uint16_t sw2_value = 0x00;
float dx,dy,rads;
int readADC(uint8_t chan);
float volts_adc(int adc);

int myAnalogRead(int spiChannel,int channelConfig,int analogChannel)
{
    if(analogChannel<0 || analogChannel>7)
        return -1;
    unsigned char buffer[3] = {1}; // start bit
    buffer[1] = (channelConfig+analogChannel) << 4;
    wiringPiSPIDataRW(spiChannel, buffer, 3);
    return ( (buffer[1] & 3 ) << 8 ) + buffer[2]; // get last 10 bits
}

int adjust_angle(int angle,char led){
	int led_peak_angle;
	if(led == 'R'){
		led_peak_angle = 90;
	}
	if(led == 'B'){
		led_peak_angle = 210;
	}
	if(led == 'G'){
		led_peak_angle = 330;
	}
	return(((angle - led_peak_angle)+360)%360);
}

int calculate_next_pwm_duty_cycle(int angle, char led){
	angle = adjust_angle(angle, led);
	if((angle > 120) && (angle < 240)){
        	return 0;
	}else{
	if(angle <= 120){
       		return (100 - (angle * (100 / 120.0)));
	}
	else{
        return 100 - ((360 - angle) * (100 / 120.0));
	}}
}
int main(){
	wiringPiSetup();
	wiringPiSPISetup(0,10000); 
	center_x1_pos = 512;
	center_y1_pos = 512;
	if(softPwmCreate(27,0,100)!=0);//RED
		printf("Doslo je do greske. \n");
	if(softPwmCreate(28,0,50)!=0);//GREEN
		printf("Doslo je do greske. \n");
	if(softPwmCreate(25,0,50)!=0);//BLUE
		printf("Doslo je do greske. \n");
	while(1){
	  x1_value = myAnalogRead(0,8,1);
 	  y1_value = myAnalogRead(0,8,0);
          sw1_value = myAnalogRead(0,8,2);
	  x2_value = myAnalogRead(0,8,4);
	  y2_value = myAnalogRead(0,8,3);
	  sw2_value = myAnalogRead(0,8,5);
	  printf("Vrednosti x1: %d , y1: %d , sw ,: %d , x2: %d , y2: %d , sw2: %d, control %d  \n",x1_value, y1_value, sw1_value, x2_value, y2_value, sw2_value, control);
          dx = x1_value - center_x1_pos;
          dy = y1_value - center_y1_pos;
	  rads = (atan2(-dy, dx))*180/PI;
	  if(sw1_value < 10){
		delay(50);
		if(control == 1){
			control = 0;}
		else control = 1;

	  }
	  if(control == 0){
	  	if((abs(dx) < 10) && (abs(dy) < 10)){
	  	 	softPwmWrite(27, 100);
	 	 	softPwmWrite(28, 100);
	  	 	softPwmWrite(25, 100);
	  	}else{
	  		softPwmWrite(27, calculate_next_pwm_duty_cycle(rads,'R'));
	  		softPwmWrite(28, calculate_next_pwm_duty_cycle(rads,'G'));
	  		softPwmWrite(25, calculate_next_pwm_duty_cycle(rads,'B'));
	  		}
	  }else{
		 softPwmWrite(27, 0);
		 softPwmWrite(28, 0);
		 softPwmWrite(25, 0);
	  }
	
	  printf ("Vrednost rads: %f \n" , rads);
	  delay(100); 
	}
}
