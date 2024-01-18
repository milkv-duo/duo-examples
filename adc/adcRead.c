#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int fd = open("/sys/class/cvi-saradc/cvi-saradc0/device/cv_saradc", O_RDWR|O_NOCTTY|O_NDELAY);
	if (fd < 0){
		printf("Error at opening ADC!\n");
		return 1;
	}
	write(fd, "1", 1);

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
			printf("adc value is %d\n", adc_value);	
		}
		sleep(1);
	}
	close(fd);
	return 0;
}
