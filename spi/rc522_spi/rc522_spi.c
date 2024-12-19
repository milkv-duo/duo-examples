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
#include "rc522.h"

 /* RC522（RFID读写模块）的示例代码。
    Example code to RC522 ，RFID module.

    注意：确保设备在3.3伏而不是5伏的电压下使用。Duo GPIO（以及SPI）不能在5伏电平下使用。
    NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Duo
    GPIO (and therefore SPI) cannot be used at 5v.

    如果你想在5伏的电压下使用该模块，需要额外加装电平转换器转换SPI电平。
    You will need to use a level shifter on the SPI lines if you want to run the
    board at 5v.

    请按下面的注释接线，运行程序前请确保引脚复用在正确的功能上。
    Please wire according to the notes below and make sure 
    the pins are set for the correct function before running the program.

    SPI2_CLK -> SCK on RC522 Moudle
    SPI2_MISO -> MISO on RC522 Moudle
    SPI2_MOSI -> MOSI on RC522 Moudle
    GP14 -> NSS on RC522 Moudle
    GP15 -> RST on RC522 Moudle
    3.3v -> VCC on RC522 Moudle
    GND -> GND on RC522 Moudle
 */


/**
  * @brief          把RFID卡的ID号输出到窗口 Output the ID number of the RFID card to the command window
  * @param[in]      id: 指向存放ID号的缓冲区 Points to the buffer storing the ID number
  * @retval         void
  */
void ShowCardID(unsigned char *id)
{
    int IDlen=4;
    printf("Card ID:");
    for(int i=0; i<IDlen; i++){
        printf(" %x %x",0x0F & (id[i]>>4),0x0F & id[i]);
    }
    printf("\n");
}

/**
  * @brief          把RFID卡的卡类型输出到窗口 Output the card type of the RFID card to the command window
  * @param[in]      type: 指向存放卡类型代码的缓冲区 Pointer to the buffer holding the card type code
  * @retval         void
  */
void ShowCardType(unsigned char* type)
{
    printf("Card type: ");
    if(type[0]==0x04&&type[1]==0x00) 
        printf("MFOne-S50");
    else if(type[0]==0x02&&type[1]==0x00)
        printf("MFOne-S70");
    else if(type[0]==0x44&&type[1]==0x00)
        printf("MF-UltraLight");
    else if(type[0]==0x08&&type[1]==0x00)
        printf("MF-Pro");
    else if(type[0]==0x44&&type[1]==0x03)
        printf("MF Desire");
    else
        printf("Unknown");

    printf("\n");
}


int main() {
    int fd_spi;
    unsigned char status = 0;
    unsigned char str[MAX_LEN];

    // Duo:     milkv_duo
    // Duo256M: milkv_duo256m
    // DuoS:    milkv_duos
    if(wiringXSetup("milkv_duo", NULL) == -1) {
        wiringXGC();
        return -1;
    }

    if ((fd_spi = wiringXSPISetup(RC522_SPI_NUM, RC522_SPI_SPEED)) <0) {
        printf("SPI Setup failed: %i\n", fd_spi);
        return -1;
    }

    if(wiringXValidGPIO(RC522_CS_PIN) != 0) {
        printf("Invalid GPIO %d\n", RC522_CS_PIN);
    }
    pinMode(RC522_CS_PIN, PINMODE_OUTPUT);
    digitalWrite(RC522_CS_PIN, HIGH);
    
    if(wiringXValidGPIO(RC522_RST_PIN) != 0) {
        printf("Invalid GPIO %d\n", RC522_RST_PIN);
    }
    pinMode(RC522_RST_PIN, PINMODE_OUTPUT);
    digitalWrite(RC522_RST_PIN, LOW);


    MFRC522_Init();
    
    while (1) {
        status = MFRC522_Request(PICC_REQIDL, str); 
        if (status != MI_OK)
        {
            continue;
        }
        ShowCardType(str);

        status = MFRC522_Anticoll(str);

        if (status != MI_OK)
        {
            continue;
        }
        memcpy(serNum, str, 5);
        ShowCardID(serNum);
 
    
        MFRC522_Halt(); //让卡进入睡眠模式 Command the card into sleep mode 
        sleep(1);
    }
}
