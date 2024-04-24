/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_adxl345_basic.h
 * @brief     driver adxl345 basic header file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-04-20
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/04/20  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/12/23  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_ADXL345_BASIC_H
#define DRIVER_ADXL345_BASIC_H

#include "adxl345_interface.h"
#include "driver_adxl345.h"

#ifdef __cplusplus
extern "C"{
#endif

#define I2C_DEV "/dev/i2c-1"

#define ADXL345_ADDR    0x53

/**
 * @defgroup adxl345_example_driver adxl345 example driver function
 * @brief    adxl345 example driver modules
 * @ingroup  adxl345_driver
 * @{
 */

/**
 * @brief adxl345 basic example default definition
 */
#define ADXL345_BASIC_DEFAULT_RATE                        ADXL345_RATE_100                      /**< rate 100Hz */
#define ADXL345_BASIC_DEFAULT_SPI_WIRE                    ADXL345_SPI_WIRE_4                    /**< spi wire 4 */
#define ADXL345_BASIC_DEFAULT_INTERRUPT_ACTIVE_LEVEL      ADXL345_INTERRUPT_ACTIVE_LEVEL_LOW    /**< interrupt pin low */
#define ADXL345_BASIC_DEFAULT_FULL_RESOLUTION             ADXL345_BOOL_TRUE                     /**< enable full resolution */
#define ADXL345_BASIC_DEFAULT_AUTO_SLEEP                  ADXL345_BOOL_FALSE                    /**< disable auto sleep */
#define ADXL345_BASIC_DEFAULT_SLEEP                       ADXL345_BOOL_FALSE                    /**< disable sleep */
#define ADXL345_BASIC_DEFAULT_SLEEP_FREQUENCY             ADXL345_SLEEP_FREQUENCY_1HZ           /**< sleep frequency 1Hz */
#define ADXL345_BASIC_DEFAULT_JUSTIFY                     ADXL345_JUSTIFY_RIGHT                 /**< justify right */
#define ADXL345_BASIC_DEFAULT_RANGE                       ADXL345_RANGE_2G                      /**< range 2g */
#define ADXL345_BASIC_DEFAULT_MODE                        ADXL345_MODE_BYPASS                   /**< bypass mode */
#define ADXL345_BASIC_DEFAULT_TRIGGER_PIN                 ADXL345_INTERRUPT_PIN2                /**< trigger pin map interrupt pin 2 */
#define ADXL345_BASIC_DEFAULT_TAP_SUPPRESS                ADXL345_BOOL_FALSE                    /**< disable tap suppress */
#define ADXL345_BASIC_DEFAULT_INTERRUPT_SINGLE_TAP_MAP    ADXL345_INTERRUPT_PIN1                /**< single tap map interrupt pin 1 */
#define ADXL345_BASIC_DEFAULT_INTERRUPT_DOUBLE_TAP_MAP    ADXL345_INTERRUPT_PIN1                /**< double tap map interrupt pin 1 */
#define ADXL345_BASIC_DEFAULT_INTERRUPT_ACTIVITY_MAP      ADXL345_INTERRUPT_PIN1                /**< activity map interrupt pin 1 */
#define ADXL345_BASIC_DEFAULT_INTERRUPT_INACTIVITY_MAP    ADXL345_INTERRUPT_PIN1                /**< inactivity map interrupt pin 1 */
#define ADXL345_BASIC_DEFAULT_INTERRUPT_FREE_FALL_MAP     ADXL345_INTERRUPT_PIN1                /**< free fall map interrupt pin 1 */
#define ADXL345_BASIC_DEFAULT_INTERRUPT_DATA_READY_MAP    ADXL345_INTERRUPT_PIN1                /**< data ready map interrupt pin 1 */
#define ADXL345_BASIC_DEFAULT_INTERRUPT_WATERMARK_MAP     ADXL345_INTERRUPT_PIN1                /**< watermark map interrupt pin 1 */
#define ADXL345_BASIC_DEFAULT_INTERRUPT_OVERRUN_MAP       ADXL345_INTERRUPT_PIN1                /**< overrun map interrupt pin 1 */
#define ADXL345_BASIC_DEFAULT_LINK_ACTIVITY_INACTIVITY    ADXL345_BOOL_TRUE                     /**< enable activity inactivity */
#define ADXL345_BASIC_DEFAULT_INTERRUPT_DATA_READY        ADXL345_BOOL_FALSE                    /**< disable data ready */
#define ADXL345_BASIC_DEFAULT_INTERRUPT_WATERMARK         ADXL345_BOOL_FALSE                    /**< disable watermark */
#define ADXL345_BASIC_DEFAULT_INTERRUPT_OVERRUN           ADXL345_BOOL_FALSE                    /**< disable overrun */
#define ADXL345_BASIC_DEFAULT_ACTION_COUPLED              ADXL345_COUPLED_AC                    /**< action ac coupled */
#define ADXL345_BASIC_DEFAULT_INACTION_COUPLED            ADXL345_COUPLED_DC                    /**< inaction dc coupled */
#define ADXL345_BASIC_DEFAULT_WATERMARK                   16                                    /**< watermark 16 level */
#define ADXL345_BASIC_DEFAULT_OFFSET                      0.0f                                  /**< 0 offset */
#define ADXL345_BASIC_DEFAULT_TAP_THRESHOLD               3.0f                                  /**< tap threshold 3.0g */
#define ADXL345_BASIC_DEFAULT_DURATION                    10 * 1000                             /**< duration 10 ms */
#define ADXL345_BASIC_DEFAULT_LATENT                      20.0f                                 /**< latent 20 ms */
#define ADXL345_BASIC_DEFAULT_WINDOW                      80.0f                                 /**< window 80 ms */
#define ADXL345_BASIC_DEFAULT_ACTION_THRESHOLD            2.0f                                  /**< action threshold 2g */
#define ADXL345_BASIC_DEFAULT_INACTION_THRESHOLD          1.0f                                  /**< inaction threshold 1g */
#define ADXL345_BASIC_DEFAULT_INACTION_TIME               3                                     /**< inaction 3s */
#define ADXL345_BASIC_DEFAULT_FREE_FALL_THRESHOLD         0.8f                                  /**< free fall threshold 0.8g */
#define ADXL345_BASIC_DEFAULT_FREE_FALL_TIME              10                                    /**< free fall time 10 ms */

/**
 * @brief     basic example init
 * @param[in] interface is the chip interface
 * @param[in] addr_pin is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t adxl345_basic_init(adxl345_interface_t interface, adxl345_address_t addr_pin);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t adxl345_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[out] *g points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t adxl345_basic_read(float g[3]);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif