#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcnt1.h>

int main(int argc,char *argv[]){

	int fd = -1,ret;
	char *tmp1,tmp2[10],ch='t';
	char devname_head[50] = "/sys/devices/w1_bus_master1/28-00000";

	char dev_name_end[10] = "/w1_slave";
	char dev_name[100];
	long value;
	int integer,decimal;
	char buffer[100];
	int i,j;
	
	strcpy(dev_name, devname_head);
	strcat(dev_name,argv[1]);
	strcat(dev_name, devname_end);\
	if() 
}
