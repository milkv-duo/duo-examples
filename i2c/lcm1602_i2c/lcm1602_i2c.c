/**
 * Copyright (c) 2023 Milk-V
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include <wiringx.h>

 /* 1602 I2C 模块（1602 LCD屏幕）的示例代码。
    Sample code for 1602 I2C module (2004 LCD screen).

	模块链接 Link of Module:
	https://www.keyestudio.com/products/keyestudio-16x2-1602-i2c-twi-lcd-display-module-for-arduino-uno-r3-mega-2560-white-in-blue

    注意：确保设备在3.3伏而不是5伏的电压下使用。Duo GPIO（以及I2C）不能在5伏电平下使用。
    NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Duo
    GPIO (and therefore I2C) cannot be used at 5v.

    如果你想在5伏的电压下使用该模块，需要额外加装电平转换器转换I2C电平。
    You will need to use a level shifter on the I2C lines if you want to run the
    board at 5v.

    请按下面的注释接线，运行程序前请确保引脚复用在正确的功能上。
    Please wire according to the notes below and make sure 
    the pins are set for the correct function before running the program.

    I2C1_SDA -> SDA on LCM1602 Moudle
    I2C1_SCL -> SCL on LCM1602 Moudle
    3.3v -> VCC on LCM1602 Moudle
    GND -> GND on LCM1602 Moudle
 */

// 使用到的I2C地址 The I2C used
#define I2C_DEV "/dev/i2c-1"

#define I2C_1602_ADDR	0x27

int fd_i2c;

int blen = 1;


void write_word(int data)
{
	int temp = data;
	if ( blen == 1 )
		temp |= 0x08;
	else
		temp &= 0xF7;
	wiringXI2CWrite(fd_i2c, temp);
}

void send_command(int comm){
	int buf;
	// Send bit7-4 firstly
	buf = comm & 0xF0;
	buf |= 0x04;			// RS = 0, RW = 0, EN = 1
	write_word(buf);
	delayMicroseconds(2000);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);

	// Send bit3-0 secondly
	buf = (comm & 0x0F) << 4;
	buf |= 0x04;			// RS = 0, RW = 0, EN = 1
	write_word(buf);
	delayMicroseconds(2000);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);
}

void send_data(int data){
	int buf;
	// Send bit7-4 firstly
	buf = data & 0xF0;
	buf |= 0x05;			// RS = 1, RW = 0, EN = 1
	write_word(buf);
	delayMicroseconds(2000);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);

	// Send bit3-0 secondly
	buf = (data & 0x0F) << 4;
	buf |= 0x05;			// RS = 1, RW = 0, EN = 1
	write_word(buf);
	delayMicroseconds(2000);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);
}

void init(){
	send_command(0x33);	// Must initialize to 8-line mode at first
	delayMicroseconds(5000);
	send_command(0x32);	// Then initialize to 4-line mode
	delayMicroseconds(5000);
	send_command(0x28);	// 2 Lines & 5*7 dots
	delayMicroseconds(5000);
	send_command(0x0C);	// Enable display without cursor
	delayMicroseconds(5000);
	send_command(0x01);	// Clear Screen
	wiringXI2CWrite(fd_i2c, 0x08);
}

void clear(){
	send_command(0x01);	//clear Screen
}

void show_string(int x, int y, char data[]){
	int addr, i;
	int tmp;
	if (x < 0)  x = 0;
	if (x > 15) x = 15;
	if (y < 0)  y = 0;
	if (y > 1)  y = 1;

	addr = 0x80 + 0x40 * y + x;
	send_command(addr);
	
	tmp = strlen(data);
	for (i = 0; i < tmp; i++){
		send_data(data[i]);
	}
}

int main() {
    int data = 0;

    // Duo:     milkv_duo
    // Duo256M: milkv_duo256m
    // DuoS:    milkv_duos
    if(wiringXSetup("milkv_duo", NULL) == -1) {
        wiringXGC();
        return -1;
    }

    if ((fd_i2c = wiringXI2CSetup(I2C_DEV, I2C_1602_ADDR)) <0) {
        printf("I2C Setup failed: %i\n", fd_i2c);
        return -1;
    }

    init();
	show_string(0, 0, "Hello MilkV Duo!");
	show_string(0, 1, "Have a Nice Day!");
	sleep(1);
}
