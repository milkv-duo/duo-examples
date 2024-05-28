/**
 * Copyright (c) 2023 Milk-V
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include <wiringx.h>

 /* MAX6675（K型热电偶测量模块）的示例代码。
    Example code to MAX6675 ，K type thermocouple measurement module.

    注意：确保设备在3.3伏而不是5伏的电压下使用。Duo GPIO（以及SPI）不能在5伏电平下使用。
    NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Duo
    GPIO (and therefore SPI) cannot be used at 5v.

    如果你想在5伏的电压下使用该模块，需要额外加装电平转换器转换SPI电平。
    You will need to use a level shifter on the SPI lines if you want to run the
    board at 5v.

    请按下面的注释接线，运行程序前请确保引脚复用在正确的功能上。
    Please wire according to the notes below and make sure 
    the pins are set for the correct function before running the program.

    SPI2_CLK -> SCK on MAX6675 Moudle
    SPI2_MISO -> SO on MAX6675 Moudle
    GP14 -> CS on MAX6675 Moudle
    3.3v -> VCC on MAX6675 Moudle
    GND -> GND on MAX6675 Moudle
 */

#define SPI_NUM     2
#define SPI_SPEED   10000

#define MAX6675_CS_PIN  14

typedef struct 
{
    uint16_t state:1;
    uint16_t id:1;
    uint16_t input:1;
    uint16_t temperature:12;
    uint16_t dumm_sig:1;
}max6675_typedef;

int main() {
    int fd_spi;
    uint8_t data[2],tmp;

    // Duo:     milkv_duo
    // Duo256M: milkv_duo256m
    // DuoS:    milkv_duos
    if(wiringXSetup("milkv_duo", NULL) == -1) {
        wiringXGC();
        return -1;
    }

    if ((fd_spi = wiringXSPISetup(SPI_NUM, SPI_SPEED)) <0) {
        printf("SPI Setup failed: %i\n", fd_spi);
        return -1;
    }

    if(wiringXValidGPIO(MAX6675_CS_PIN) != 0) {
        printf("Invalid GPIO %d\n", MAX6675_CS_PIN);
    }
    pinMode(MAX6675_CS_PIN, PINMODE_OUTPUT);
    digitalWrite(MAX6675_CS_PIN, HIGH);
    
    while (1) {
        digitalWrite(MAX6675_CS_PIN, LOW);  //激活片选 Activate chip select
        wiringXSPIDataRW(SPI_NUM, data, 2); //读取数据 Read data
        digitalWrite(MAX6675_CS_PIN, HIGH); //取消片选 Cancel chip select

        tmp = data[0];
        data[0] = data[1];
        data [1] = tmp;     //数据格式大小端转换 Data format big and small endian conversion

        printf("temperature = %.2f C\n",((max6675_typedef *)data) -> temperature / 4.0);
        sleep(1);
    }
}
