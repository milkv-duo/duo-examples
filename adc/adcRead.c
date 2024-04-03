/*
	Name: adcRead.c
    	Description: Source code to enable ADC reads with SARADC module.
    	Dev: Paulo Antunes BR
    	Date: 18/01/2024
    	Versão: 1.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	if ((system("lsmod | grep -q \"cv180x_saradc\"") == 0)||(system("lsmod | grep -q \"cv181x_saradc\"") == 0)){
		printf("SARADC module already loaded.\n");
	}else{
		system("insmod $(find / -name \"cv180x_saradc.ko\" 2>/dev/null)");
		system("insmod $(find / -name \"cv181x_saradc.ko\" 2>/dev/null)");
		printf("SARADC module loaded.\n");
	}
	int fd = open("/sys/class/cvi-saradc/cvi-saradc0/device/cv_saradc", O_RDWR|O_NOCTTY|O_NDELAY);
	if (fd < 0){
		printf("Error at opening ADC!\n");
		return 1;
	}
	printf("Define the ADC channel: \n 1: ADC1 (GP26|PIN31)\n 2: ADC2 (GP27|PIN32)\n 3: ???\n 4: VDDC_RTC\n 5: PWR_GPIO1\n 6: PWR_VBAT_V\n");
	
	char adc_channel;
	scanf("%c", &adc_channel);
	
	if(adc_channel > '0' && adc_channel <= '6'){
		write(fd, &adc_channel, 1);
	} else{
		printf("Invalid ADC channel.\n");
		return 1;
	}
	
	char buffer[512];
	int len = 0;
	int adc_value = 0;
	
	while(1){
		for(int i = 0; i < sizeof(buffer); i++){
			buffer[i] = 0;
		}
		lseek(fd, 0, SEEK_SET);
		len = read(fd, buffer, sizeof(buffer) -1);
		if(len != 0){
			adc_value = atoi(buffer);
			printf("ADC%c value is %d\n", adc_channel, adc_value);	
		}
		sleep(1);
	}
	close(fd);
	return 0;
}
