// gcc -o irm1 irm1.c -l bcm2835 -l lirc_client
// sudo ./irm1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <lirc/lirc_client.h>

// LED3 je na DVK512 pločici na P28 što je pin 20 na BCM-u,
// ako se koristi protobord može se
// koristiti isti ovaj pin ili neki drugi
#define PIN 25

int main()
{
		struct lirc_config *config;
		char *code;
    
    int i = 0;
    
		//startuj lirc
		if(lirc_init("lirc",1)==-1)
				return 1;
 
  	if(wiringPiSetup() == -1)
		exit(1);
 
 		// Setuj PIN kao izlazni
 	  pinMode(PIN, OUTPUT);
		
    if(softPwmCreate(PIN,0,100) != 0) //Omogucava realizaciju PWM na odabranom pinu (pin,inicij V, pwmOpseg)
		      exit(2);
		//procitaj /etc/lirc/lirc/lircrc/lircd.conf
		if(lirc_readconfig(NULL, &config,NULL)==0)
		{
				//radimo dok je LIRC soket otvoren 0=otvoren -1=zatvoren
				while (lirc_nextcode(&code)==0)
				{
						// if code=NULL ništa nije primljeno-preskoči
						if(code==NULL) continue; {
				
								delay(400);
						if (strstr(code,"KEY_VOLUMEUP")){
                    
						    i+= 20;
						    if(i > 100) i = 100;

						    printf("i = %d\n",i);
					            fflush(stdout);
                    
						    softPwmWrite(PIN,i);//PWM na pinu i vrednost
               					 }else if (strstr(code,"KEY_VOLUMEDOWN")){
                    
						    i-= 20;
						    if(i < 0) i = 0;

						    printf("i = %d\n",i);
	                                            fflush(stdout);

						    softPwmWrite(PIN,i);//PWM na pinu i vrednost
						}
						}
						free(code);
				}
				lirc_freeconfig(config);
		}
		lirc_deinit();
 		return 0;
}
