#ifndef DRIVER_ADXL345_INTERFACE_H
#define DRIVER_ADXL345_INTERFACE_H

#include "stdint.h"

#ifdef __cplusplus
extern "C"{
#endif

uint8_t duo_i2cinit(void);
uint8_t duo_i2cdeinit(void);
uint8_t duo_i2cread(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);
uint8_t duo_i2cwrite(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);
void duo_delayms(uint32_t ms);

uint8_t duo_spiinit(void);
uint8_t duo_spideinit(void);
uint8_t duo_spiread(uint8_t reg, uint8_t *buf, uint16_t len);
uint8_t duo_spiwrite(uint8_t reg, uint8_t *buf, uint16_t len);
void duo_rec_cb(uint8_t type);

#ifdef __cplusplus
}
#endif

#endif