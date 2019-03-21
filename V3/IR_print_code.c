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
    
    char hex[20];
    char key[10];
    
		//startuj lirc
		if(lirc_init("lirc",1)==-1)
				return 1;
 
  	if(wiringPiSetup() == -1)
		exit(1);
 
 		// Setuj PIN kao izlazni
 	  pinMonde(PIN, OUTPUT);
		
		//procitaj /etc/lirc/lirc/lircrc/lircd.conf
		if(lirc_readconfig(NULL, &config,NULL)==0)
		{
				//radimo dok je LIRC soket otvoren 0=otvoren -1=zatvoren
				while (lirc_nextcode(&code)==0)
				{
						// if code=NULL ništa nije primljeno-preskoči
						if(code==NULL) continue; {
				
								delay(400);
						    sscanf(code,"0000000000%s %*s %s %*s", hex, key);
                printf("0x");
                printf(hex);
                printf(" ");
                printf(key);
                printf("\n");
                fflush(stdout)
						}
						free(code);
				}
				lirc_freeconfig(config);
		}
		lirc_deinit();
 		return 0;
}
