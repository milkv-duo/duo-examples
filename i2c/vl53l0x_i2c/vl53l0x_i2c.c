/**
 * Copyright (c) 2023 Milk-V
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "tof.h"

 /* 关于VL53L0X TOF模块的示例代码 
    Example code to VL53L0X Time of Flight Module

    注意：确保设备在3.3伏而不是5伏的电压下使用。Duo GPIO（以及I2C）不能在5伏电平下使用。
    NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Duo
    GPIO (and therefore I2C) cannot be used at 5v.

    如果你想在5伏的电压下使用该模块，需要额外加装电平转换器转换I2C电平。
    You will need to use a level shifter on the I2C lines if you want to run the
    board at 5v.

    请按下面的注释接线，运行程序前请确保引脚复用在正确的功能上。
    Please wire according to the notes below and make sure 
    the pins are set for the correct function before running the program.

    I2C1_SDA -> SDA on VL53L0X Moudle
    I2C1_SCL -> SCL on VL53L0X Moudle
    3.3v -> VCC on VL53L0X Moudle
    GND -> GND on VL53L0X Moudle
 */

// 使用到的I2C编号 The I2C number used
#define I2C_NUM     1

// 器件地址 device address
#define I2C_ADDR    0x29

int main() {
    int data = 0;

    tofInit(I2C_NUM, I2C_ADDR, 0);

    while (1) {
        data = tofReadDistance();
        printf("VL53L0X get distance: %dmm\n",data);
        sleep(1);
    }
}
