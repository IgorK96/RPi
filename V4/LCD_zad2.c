// gcc -o irm1 irm1.c -l bcm2835 -l lirc_client
// sudo ./irm1

//startuj lircs sudo /etc/init.d/lircd start

//#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <lirc/lirc_client.h>
#include <lcd.h>
#include <time.h>
#include <errno.h>

// dodela vrednosti za konkretne pinove
// prema gornjoj tabeli i semi DVK512
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int main()
{
    int lcd_h;
    int x = 0;
    int y = 0;
    if (wiringPiSetup() < 0){
      fprintf (stderr, "Greška pri inicijalizaciji: %s\n", strerror (errno)) ;
      return 1 ;
    }
    lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
		
    lcdPosition(lcd_h, x,y);
    lcdCursor(lcd_h,1);
    
    struct lirc_config *config;
		char *code;
    
    int i = 0;
    
		//startuj lirc
		if(lirc_init("lirc",1)==-1)
				return 1;
     
		//procitaj /etc/lirc/lirc/lircrc/lircd.conf
		if(lirc_readconfig(NULL, &config,NULL)==0)
		{ 
				//radimo dok je LIRC soket otvoren 0=otvoren -1=zatvoren
				while (lirc_nextcode(&code)==0)
				{
            
					if(code==NULL) continue; {
				
						delay(400);
					if (strstr(code,"KEY_NEXT")){
             					x += 1;
           				}else if (strstr(code,"KEY_PREVIOUS")){
              					x -= 1;
            				}else if (strstr(code,"KEY_UP")){
              					y += 1;
            				}else if (strstr(code,"KEY_DOWN")){
              					y -= 1;
            				}
            
            				if(x == 16){
                				x = 0;
            				}else if(x == -1){
                				x = 15;
            				}
             
            				if(y == 2){
                				y = 0;
            				}else if( y == -1){
                				y = 1;
            				}	
              				delay(300);
            				lcdPosition(lcd_h, x,y);
              
					}
				free(code);
				}
				lirc_freeconfig(config);
		}
		lirc_deinit();
 		return 0;
}
