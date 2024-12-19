#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include <wiringx.h>
#include "adxl345.h"

int fd_i2c;

uint8_t duo_i2cinit(void)
{
    // Duo:     milkv_duo
    // Duo256M: milkv_duo256m
    // DuoS:    milkv_duos
    if(wiringXSetup("milkv_duo", NULL) == -1) {
        wiringXGC();
        return -1;
    }

    if ((fd_i2c = wiringXI2CSetup(I2C_DEV, ADXL345_ADDR)) <0) {
        printf("I2C Setup failed: %i\n", fd_i2c);
        return -1;
    }

    return 0;
}
uint8_t duo_i2cdeinit(void)
{
    return 0;
}                                                       
uint8_t duo_i2cread(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint16_t lenth = len;
    uint8_t *p = buf;
    *p = wiringXI2CReadReg8(fd_i2c, reg);
    if (*p < 0) return 1;
    lenth--;
    p++;

    while(lenth > 0)
    {
        *p = wiringXI2CRead(fd_i2c);
        if (*p < 0) return 1;
        lenth--;
        p++;
    }
    return 0;
}
uint8_t duo_i2cwrite(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint16_t lenth = len;
    uint8_t *p = buf;
    int err;
    err = wiringXI2CWriteReg8(fd_i2c, reg, *p);
    if (err != 0) return 1;
    lenth--;
    p++;

    while(lenth > 0)
    {
        err = wiringXI2CWrite(fd_i2c, *p);
        if (err != 0) return 1;
        lenth--;
        p++;
    }
    return 0;
}
void duo_delayms(uint32_t ms)
{
    delayMicroseconds(ms * 1000);
}

uint8_t duo_spiinit(void)   //用不到，暂时不实现
{
    return 1;
}
uint8_t duo_spideinit(void) //用不到，暂时不实现
{
    return 1;
}
uint8_t duo_spiread(uint8_t reg, uint8_t *buf, uint16_t len)    //用不到，暂时不实现
{
    return 1;
}
uint8_t duo_spiwrite(uint8_t reg, uint8_t *buf, uint16_t len)   //用不到，暂时不实现
{
    return 1;
}
void duo_rec_cb(uint8_t type)  //用不到，暂时不实现
{
}
