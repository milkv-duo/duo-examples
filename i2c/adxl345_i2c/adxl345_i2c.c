/**
 * Copyright (c) 2023 Milk-V
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "adxl345.h"
#include "driver_adxl345.h"

 /* ADXL345 模块（三轴加速度传感器）的示例代码。
    Sample code for ADXL345 module (three-axis acceleration sensor).

    注意：确保设备在3.3伏而不是5伏的电压下使用。Duo GPIO（以及I2C）不能在5伏电平下使用。
    NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Duo
    GPIO (and therefore I2C) cannot be used at 5v.

    如果你想在5伏的电压下使用该模块，需要额外加装电平转换器转换I2C电平。
    You will need to use a level shifter on the I2C lines if you want to run the
    board at 5v.

    请按下面的注释接线，运行程序前请确保引脚复用在正确的功能上。
    Please wire according to the notes below and make sure 
    the pins are set for the correct function before running the program.

    I2C1_SDA -> SDA on ADXL345 Moudle
    I2C1_SCL -> SCL on ADXL345 Moudle
    3.3v -> VCC on ADXL345 Moudle
    GND -> GND on ADXL345 Moudle
 */

adxl345_info_t adxl345_info_handle;

int main() 
{
    float acc[3] = {0};

    if(adxl345_basic_init(ADXL345_INTERFACE_IIC, ADXL345_ADDR))
    {
        printf("adxl345 init failed!");
        return -1;
    }

    if(adxl345_info(&adxl345_info_handle))
    {
        printf("failed in get adxl345 info.\n");
        return -1;
    }
    printf("chip name: %s\n",adxl345_info_handle.chip_name);

    while(1)
    {
        adxl345_basic_read(acc);
        printf("get acceleration information-x:%.2f y:%.2f z:%.2f\n",acc[0],acc[1],acc[2]);
        sleep(1);
    }

    if(adxl345_basic_deinit())
    {
        printf("adxl345 deinit failed!\n");
        return -1;
    }

    return 0;
}
