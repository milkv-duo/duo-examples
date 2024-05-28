/**
 * Copyright (c) 2023 Milk-V
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include <wiringx.h>
#include "tcs34725_i2c.h"

 /* TCS34725（颜色传感器模块）的示例代码。
    Example code to TCS34725 ，color sensor module.

    注意：确保设备在3.3伏而不是5伏的电压下使用。Duo GPIO（以及I2C）不能在5伏电平下使用。
    NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Duo
    GPIO (and therefore I2C) cannot be used at 5v.

    如果你想在5伏的电压下使用该模块，需要额外加装电平转换器转换I2C电平。
    You will need to use a level shifter on the I2C lines if you want to run the
    board at 5v.

    请按下面的注释接线，运行程序前请确保引脚复用在正确的功能上。
    Please wire according to the notes below and make sure 
    the pins are set for the correct function before running the program.

    I2C1_SDA -> SDA on TCS34725 Moudle
    I2C1_SCL -> SCL on TCS34725 Moudle
    3.3v -> VCC on TCS34725 Moudle
    GND -> GND on TCS34725 Moudle
 */

//使用到的I2C端口 depends on which port to use
#define I2C_DEV "/dev/i2c-1"

int fd_i2c;

/* TCS34725设备启动状态 TCS34725 device startup status */
static bool tcs34725_state = false;

/* 设备默认配置参数 Device default configuration parameters */
struct tcs34725_config _tcs34725_config =
{
    .name = "TCS34725",
    .interrupt_start = false,
};
 
/**
 * @brief 写一字节到寄存器 Write one byte to register
 * 
 * @param reg_addr 寄存器地址 Register address
 * @param write_data 需要写入的寄存器数据 Register data to be written
 * @return uint8_t 无错误时返回0 Returns 0 if there is no error
 */
static uint8_t tcs34725_write8(uint8_t reg_addr, uint8_t write_data)
{
    return wiringXI2CWriteReg8(fd_i2c, TCS34725_COMMAND_BIT | reg_addr, write_data);
}
 
/**
 * @brief 从寄存器读一字节 Read one byte from register
 * 
 * @param reg_addr 寄存器地址 Register address
 * @param read_data 数据存放地址 Point to the data storage address
 * @return uint8_t 无错误时返回 0 Returns 0 if there is no error
 */
static uint8_t tcs34725_read8(uint8_t reg_addr, uint8_t* read_data)
{
    *read_data = wiringXI2CReadReg8(fd_i2c, TCS34725_COMMAND_BIT | reg_addr);
    return 0;
}
 
/**
 * @brief 从寄存器读两字节 Read two byte from register
 * 
 * @param reg_addr 寄存器地址 Register address
 * @param read_data 数据存放地址 Point to the data storage address
 * @return uint8_t 无错误时返回 0 Returns 0 if there is no error
 */
static uint8_t tcs34725_read16(uint8_t reg_addr, uint16_t* read_data)
{
    *read_data = wiringXI2CReadReg16(fd_i2c, TCS34725_COMMAND_BIT | reg_addr);
    return 0;
}
 
/**
 * @brief 启动 tcs34725 设备 Start the tcs34725 device
 * 
 * @param interrupt_start 是否开启中断启动方式 Whether to enable interrupt startup mode
 * @return uint8_t 无错误时返回 0 Returns 0 if there is no error
 */
uint8_t tcs34725_start(bool interrupt_start)
{
    int err = 0;
    if (tcs34725_state)
    {
        return -1;
    }
 
    err = tcs34725_write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);
    err = tcs34725_write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
 
    if (interrupt_start)
    {
        _tcs34725_config.interrupt_start = interrupt_start;
        err = tcs34725_write8(TCS34725_ENABLE, TCS34725_ENABLE_AIEN);
    }
 
    tcs34725_state = true;
    return err;
}
 
/**
 * @brief 停止 tcs34725 设备 Stop tcs34725 device
 * 
 * @return uint8_t 无错误时返回 0 Returns 0 if there is no error
 */
uint8_t tcs34725_stop(void)
{
    uint8_t err = 0;
    uint8_t data = 0;
    err = tcs34725_read8(TCS34725_ENABLE, &data);
    err = tcs34725_write8(TCS34725_ENABLE, data & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
 
    if (_tcs34725_config.interrupt_start)
    {
        err = tcs34725_write8(TCS34725_ENABLE, data & ~TCS34725_ENABLE_AIEN);
    }
 
    tcs34725_state = false;
    return err;
}
 
/**
 * @brief 读取设备类型 Read device type
 * 
 * @return uint8_t 设备识别号 Device identification number 0x44 = TCS34721/TCS34725, 0x4D = TCS34723/TCS34727
 */
uint8_t get_tcs34725_type(void)
{
    uint8_t data = 0;
    tcs34725_read8(TCS34725_ID, &data);
    return data;
}
 
/**
 * @brief 设置集成时间 Set integration time
 * 
 * @param integration_time 集成时间 integration time
 * @return uint8_t 无错误时返回 0 Returns 0 if there is no error
 */
uint8_t set_tcs34725_integration_time(tcs34725_integration_time_t integration_time)
{
    _tcs34725_config.integration_time = integration_time;
    return tcs34725_write8(TCS34725_ATIME, integration_time);
}
 
/**
 * @brief 获取设置的集成时间 Get the set integration time
 * 
 * @return 集成时间配置参数 Integration time configuration parameters
 */
tcs34725_integration_time_t get_tcs34725_integration_time(void)
{
    return _tcs34725_config.integration_time;
}
 
/**
 * @brief 设置增益倍数 Set gain multiplier
 * 
 * @param gain 增益倍数 Gain multiple
 * @return uint8_t 无错误时返回 0 Returns 0 if there is no error
 */
uint8_t set_tcs34725_gain(tcs34725_gain_t gain)
{
    _tcs34725_config.gain = gain;
    return tcs34725_write8(TCS34725_CONTROL, gain);
}
 
/**
 * @brief 获取设置的增益倍数 Get the set gain multiplier
 * 
 * @return 增益倍数 Gain multiple
 */
tcs34725_gain_t get_tcs34725_gain(void)
{
    return _tcs34725_config.gain;
}
 
/**
 * @brief 获取RGBC的值 Get the value of RGBC
 * 
 * @param colour_r 红色数据存放地址 Red data storage address
 * @param colour_g 绿色数据存放地址 Green data storage address
 * @param colour_b 蓝色数据存放地址 Blue data storage address
 * @param colour_c 亮度数据存放地址 Brightness data storage address
 * @return uint8_t 无错误时返回 0 Returns 0 if there is no error
 */
uint8_t get_tcs34725_rgbc(uint16_t *colour_r, uint16_t *colour_g, uint16_t *colour_b, uint16_t *colour_c)
{
    uint8_t err = 0;
    err = tcs34725_read16(TCS34725_RDATAL, colour_r);
    err = tcs34725_read16(TCS34725_GDATAL, colour_g);
    err = tcs34725_read16(TCS34725_BDATAL, colour_b);
    err = tcs34725_read16(TCS34725_CDATAL, colour_c);
    return err;
}

int main() {
    uint16_t r,g,b,l;

    // Duo:     milkv_duo
    // Duo256M: milkv_duo256m
    // DuoS:    milkv_duos
    if(wiringXSetup("milkv_duo", NULL) == -1) {
        wiringXGC();
        return -1;
    }

    if ((fd_i2c = wiringXI2CSetup(I2C_DEV, TCS34725_ADDR)) <0) {
        printf("I2C Setup failed: %i\n", fd_i2c);
        return -1;
    }

    uint8_t tcs34725_type = get_tcs34725_type();
    printf("device type is : %x \n", tcs34725_type);
    if (!((tcs34725_type == 0x44) || (tcs34725_type == 0x4D)))
    {
        printf("Wrong device type! exit\n");
        return -1;
    }

    set_tcs34725_integration_time(TCS34725_INTEGRATIONTIME_50MS);
    set_tcs34725_gain(TCS34725_GAIN_4X);
    tcs34725_start(0);

    delayMicroseconds(100000);

    get_tcs34725_rgbc(&r, &g, &b, &l);
    tcs34725_stop();
    printf("get sensor val R:%d G:%d B:%d Brightness:%d\n",r,g,b,l);

    return 0;
}
