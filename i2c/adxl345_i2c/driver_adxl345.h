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
 * @file      driver_adxl345.h
 * @brief     driver adxl345 header file
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

#ifndef DRIVER_ADXL345_H
#define DRIVER_ADXL345_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup adxl345_driver adxl345 driver function
 * @brief    adxl345 driver modules
 * @{
 */

/**
 * @addtogroup adxl345_basic_driver
 * @{
 */

/**
 * @brief adxl345 interface enumeration definition
 */
typedef enum
{
    ADXL345_INTERFACE_IIC = 0x00,        /**< iic interface function */
    ADXL345_INTERFACE_SPI = 0x01,        /**< spi interface function */
} adxl345_interface_t;

/**
 * @brief adxl345 address enumeration definition
 */
typedef enum
{
    ADXL345_ADDRESS_ALT_0 = 0xA6,        /**< addr pin connected to the GND */
    ADXL345_ADDRESS_ALT_1 = 0x3A,        /**< addr pin connected to the VCC */
} adxl345_address_t;

/**
 * @brief adxl345 bool enumeration definition
 */
typedef enum
{
    ADXL345_BOOL_FALSE = 0x00,        /**< false */
    ADXL345_BOOL_TRUE  = 0x01,        /**< true */
} adxl345_bool_t;

/**
 * @brief adxl345 coupled enumeration definition
 */
typedef enum
{
    ADXL345_COUPLED_DC = 0x00,        /**< DC coupled */
    ADXL345_COUPLED_AC = 0x01,        /**< AC coupled */
} adxl345_coupled_t;

/**
 * @brief adxl345 action inaction enumeration definition
 */
typedef enum
{
    ADXL345_ACTION_X   = 0x06,        /**< x axis action */
    ADXL345_ACTION_Y   = 0x05,        /**< y axis action */
    ADXL345_ACTION_Z   = 0x04,        /**< z axis action */
    ADXL345_INACTION_X = 0x02,        /**< x axis inaction */
    ADXL345_INACTION_Y = 0x01,        /**< y axis inaction */
    ADXL345_INACTION_Z = 0x00,        /**< z axis inaction */
} adxl345_action_inaction_t;

/**
 * @brief adxl345 tap axis enumeration definition
 */
typedef enum
{
    ADXL345_TAP_AXIS_X = 0x02,        /**< x axis tap */
    ADXL345_TAP_AXIS_Y = 0x01,        /**< y axis tap */
    ADXL345_TAP_AXIS_Z = 0x00,        /**< z axis tap */
} adxl345_tap_axis_t;

/**
 * @brief adxl345 action tap status enumeration definition
 */
typedef enum
{
    ADXL345_ACTION_TAP_STATUS_ACT_X  = (1 << 6),        /**< x axis action status */
    ADXL345_ACTION_TAP_STATUS_ACT_Y  = (1 << 5),        /**< y axis action status */
    ADXL345_ACTION_TAP_STATUS_ACT_Z  = (1 << 4),        /**< z axis action status */
    ADXL345_ACTION_TAP_STATUS_ASLEEP = (1 << 3),        /**< asleep status */
    ADXL345_ACTION_TAP_STATUS_TAP_X  = (1 << 2),        /**< x axis tap status */
    ADXL345_ACTION_TAP_STATUS_TAP_Y  = (1 << 1),        /**< y axis tap status */
    ADXL345_ACTION_TAP_STATUS_TAP_Z  = (1 << 0),        /**< z axis tap status */
} adxl345_action_tap_status_t;

/**
 * @brief adxl345 rate enumeration definition
 */
typedef enum
{
    ADXL345_RATE_0P1            = 0x00,        /**< 0.1Hz */
    ADXL345_RATE_0P2            = 0x01,        /**< 0.2Hz */
    ADXL345_RATE_0P39           = 0x02,        /**< 0.39Hz */
    ADXL345_RATE_0P78           = 0x03,        /**< 0.78Hz */
    ADXL345_RATE_1P56           = 0x04,        /**< 1.56Hz */
    ADXL345_RATE_3P13           = 0x05,        /**< 3.13Hz */
    ADXL345_RATE_6P25           = 0x06,        /**< 6.25Hz */
    ADXL345_RATE_12P5           = 0x07,        /**< 12.5Hz */
    ADXL345_RATE_25             = 0x08,        /**< 25Hz */
    ADXL345_RATE_50             = 0x09,        /**< 50Hz */
    ADXL345_RATE_100            = 0x0A,        /**< 100Hz */
    ADXL345_RATE_200            = 0x0B,        /**< 200Hz */
    ADXL345_RATE_400            = 0x0C,        /**< 400Hz */
    ADXL345_RATE_800            = 0x0D,        /**< 800Hz */
    ADXL345_RATE_1600           = 0x0E,        /**< 1600Hz */
    ADXL345_RATE_3200           = 0x0F,        /**< 3200Hz */
    ADXL345_LOW_POWER_RATE_12P5 = 0x17,        /**< low power 12.5Hz */
    ADXL345_LOW_POWER_RATE_25   = 0x18,        /**< low power 25Hz */
    ADXL345_LOW_POWER_RATE_50   = 0x19,        /**< low power 50Hz */
    ADXL345_LOW_POWER_RATE_100  = 0x1A,        /**< low power 100Hz */
    ADXL345_LOW_POWER_RATE_200  = 0x1B,        /**< low power 200Hz */
    ADXL345_LOW_POWER_RATE_400  = 0x1C,        /**< low power 400Hz */
} adxl345_rate_t;

/**
 * @brief adxl345 spi wire enumeration definition
 */
typedef enum
{
    ADXL345_SPI_WIRE_4 = 0x00,        /**< wire 4 */
    ADXL345_SPI_WIRE_3 = 0x01,        /**< wire 3 */
} adxl345_spi_wire_t;

/**
 * @brief adxl345 justify enumeration definition
 */
typedef enum
{
    ADXL345_JUSTIFY_RIGHT = 0x00,        /**< right justify */
    ADXL345_JUSTIFY_LEFT  = 0x01,        /**< left justify */
} adxl345_justify_t;

/**
 * @brief adxl345 range enumeration definition
 */
typedef enum
{
    ADXL345_RANGE_2G  = 0x00,        /**< ±2G */
    ADXL345_RANGE_4G  = 0x01,        /**< ±4G */
    ADXL345_RANGE_8G  = 0x02,        /**< ±8G */
    ADXL345_RANGE_16G = 0x03,        /**< ±16G */
} adxl345_range_t;

/**
 * @brief adxl345 sleep frequency enumeration definition
 */
typedef enum
{
    ADXL345_SLEEP_FREQUENCY_8HZ = 0x00,        /**< sleep 8Hz */
    ADXL345_SLEEP_FREQUENCY_4HZ = 0x01,        /**< sleep 4Hz */
    ADXL345_SLEEP_FREQUENCY_2HZ = 0x02,        /**< sleep 2Hz */
    ADXL345_SLEEP_FREQUENCY_1HZ = 0x03,        /**< sleep 1Hz*/
} adxl345_sleep_frequency_t;

/**
 * @brief adxl345 mode enumeration definition
 */
typedef enum
{
    ADXL345_MODE_BYPASS  = 0x00,        /**< bypass mode */
    ADXL345_MODE_FIFO    = 0x01,        /**< fifo mode */
    ADXL345_MODE_STREAM  = 0x02,        /**< stream mode */
    ADXL345_MODE_TRIGGER = 0x03,        /**< trigger mode */
} adxl345_mode_t;

/**
 * @brief adxl345 trigger status enumeration definition
 */
typedef enum
{
    ADXL345_TRIGGER_NOT_OCCURRED = 0x00,        /**< not occurred */
    ADXL345_TRIGGER_OCCURRED     = 0x01,        /**< occurred */
} adxl345_trigger_status_t;

/**
 * @}
 */

/**
 * @addtogroup adxl345_interrupt_driver
 * @{
 */

/**
 * @brief adxl345 interrupt enumeration definition
 */
typedef enum
{
    ADXL345_INTERRUPT_DATA_READY = 0x07,        /**< data ready */
    ADXL345_INTERRUPT_SINGLE_TAP = 0x06,        /**< single tap */
    ADXL345_INTERRUPT_DOUBLE_TAP = 0x05,        /**< double tap */
    ADXL345_INTERRUPT_ACTIVITY   = 0x04,        /**< activity */
    ADXL345_INTERRUPT_INACTIVITY = 0x03,        /**< inactivity */
    ADXL345_INTERRUPT_FREE_FALL  = 0x02,        /**< free fall */
    ADXL345_INTERRUPT_WATERMARK  = 0x01,        /**< watermark */
    ADXL345_INTERRUPT_OVERRUN    = 0x00,        /**< overrun */
} adxl345_interrupt_t;

/**
 * @brief adxl345 interrupt pin enumeration definition
 */
typedef enum
{
    ADXL345_INTERRUPT_PIN1 = 0x00,        /**< interrupt pin 1 */
    ADXL345_INTERRUPT_PIN2 = 0x01,        /**< interrupt pin 2 */
} adxl345_interrupt_pin_t;

/**
 * @brief adxl345 interrupt active_level enumeration definition
 */
typedef enum
{
    ADXL345_INTERRUPT_ACTIVE_LEVEL_HIGH = 0x00,        /**< interrupt active level high */
    ADXL345_INTERRUPT_ACTIVE_LEVEL_LOW  = 0x01,        /**< interrupt active level low */
} adxl345_interrupt_active_level_t;

/**
 * @}
 */

/**
 * @addtogroup adxl345_basic_driver
 * @{
 */

/**
 * @brief adxl345 handle structure definition
 */
typedef struct adxl345_handle_s
{
    uint8_t iic_addr;                                                                   /**< iic address */
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    uint8_t (*spi_init)(void);                                                          /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                                        /**< point to a spi_deinit function address */
    uint8_t (*spi_read)(uint8_t reg, uint8_t *buf, uint16_t len);                       /**< point to a spi_read function address */
    uint8_t (*spi_write)(uint8_t reg, uint8_t *buf, uint16_t len);                      /**< point to a spi_write function address */
    void (*receive_callback)(uint8_t type);                                             /**< point to a receive_callback function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
    uint8_t iic_spi;                                                                    /**< iic spi interface type */
} adxl345_handle_t;

/**
 * @brief adxl345 information structure definition
 */
typedef struct adxl345_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} adxl345_info_t;

/**
 * @}
 */

/**
 * @defgroup adxl345_link_driver adxl345 link driver function
 * @brief    adxl345 link driver modules
 * @ingroup  adxl345_driver
 * @{
 */

/**
 * @brief     initialize adxl345_handle_t structure
 * @param[in] HANDLE points to an adxl345 handle structure
 * @param[in] STRUCTURE is adxl345_handle_t
 * @note      none
 */
#define DRIVER_ADXL345_LINK_INIT(HANDLE, STRUCTURE)         memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an adxl345 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_ADXL345_LINK_IIC_INIT(HANDLE, FUC)          (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an adxl345 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_ADXL345_LINK_IIC_DEINIT(HANDLE, FUC)        (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to an adxl345 handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_ADXL345_LINK_IIC_READ(HANDLE, FUC)          (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to an adxl345 handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_ADXL345_LINK_IIC_WRITE(HANDLE, FUC)         (HANDLE)->iic_write = FUC

/**
 * @brief     link spi_init function
 * @param[in] HANDLE points to an adxl345 handle structure
 * @param[in] FUC points to a spi_init function address
 * @note      none
 */
#define DRIVER_ADXL345_LINK_SPI_INIT(HANDLE, FUC)          (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE points to an adxl345 handle structure
 * @param[in] FUC points to a spi_deinit function address
 * @note      none
 */
#define DRIVER_ADXL345_LINK_SPI_DEINIT(HANDLE, FUC)        (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_read function
 * @param[in] HANDLE points to an adxl345 handle structure
 * @param[in] FUC points to a spi_read function address
 * @note      none
 */
#define DRIVER_ADXL345_LINK_SPI_READ(HANDLE, FUC)          (HANDLE)->spi_read = FUC

/**
 * @brief     link spi_write function
 * @param[in] HANDLE points to an adxl345 handle structure
 * @param[in] FUC points to a spi_write function address
 * @note      none
 */
#define DRIVER_ADXL345_LINK_SPI_WRITE(HANDLE, FUC)         (HANDLE)->spi_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an adxl345 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_ADXL345_LINK_DELAY_MS(HANDLE, FUC)          (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an adxl345 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_ADXL345_LINK_DEBUG_PRINT(HANDLE, FUC)       (HANDLE)->debug_print = FUC

/**
 * @brief     link receive_callback function
 * @param[in] HANDLE points to an adxl345 handle structure
 * @param[in] FUC points to a receive_callback function address
 * @note      none
 */
#define DRIVER_ADXL345_LINK_RECEIVE_CALLBACK(HANDLE, FUC)  (HANDLE)->receive_callback = FUC

/**
 * @}
 */

/**
 * @defgroup adxl345_basic_driver adxl345 basic driver function
 * @brief    adxl345 basic driver modules
 * @ingroup  adxl345_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an adxl345 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t adxl345_info(adxl345_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an adxl345 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi or iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 id is invalid
 * @note      none
 */
uint8_t adxl345_init(adxl345_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an adxl345 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic or spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t adxl345_deinit(adxl345_handle_t *handle);

/**
 * @brief     set the chip interface
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] interface is the chip interface
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t adxl345_set_interface(adxl345_handle_t *handle, adxl345_interface_t interface);

/**
 * @brief      get the chip interface
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *interface points to a chip interface buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t adxl345_get_interface(adxl345_handle_t *handle, adxl345_interface_t *interface);

/**
 * @brief     set the iic address pin
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] addr_pin is the address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t adxl345_set_addr_pin(adxl345_handle_t *handle, adxl345_address_t addr_pin);

/**
 * @brief      get the iic address pin
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *addr_pin points to an address pin buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t adxl345_get_addr_pin(adxl345_handle_t *handle, adxl345_address_t *addr_pin);

/**
 * @brief         read the data
 * @param[in]     *handle points to an adxl345 handle structure
 * @param[out]    **raw points to a raw data buffer
 * @param[out]    **g points to a converted data buffer
 * @param[in,out] *len points to a length buffer
 * @return        status code
 *                - 0 success
 *                - 1 read failed
 *                - 2 handle is NULL
 *                - 3 handle is not initialized
 * @note          none
 */
uint8_t adxl345_read(adxl345_handle_t *handle, int16_t (*raw)[3], float (*g)[3], uint16_t *len);

/**
 * @brief     irq handler
 * @param[in] *handle points to an adxl345 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_irq_handler(adxl345_handle_t *handle);

/**
 * @brief     set the tap threshold
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] threshold is the tap threshold
 * @return    status code
 *            - 0 success
 *            - 1 set tap threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_tap_threshold(adxl345_handle_t *handle, uint8_t threshold);

/**
 * @brief      get the tap threshold
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *threshold points to a tap threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tap threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_tap_threshold(adxl345_handle_t *handle, uint8_t *threshold);

/**
 * @brief      convert the tap threshold to the register raw data
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  g is the tap threshold
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_tap_threshold_convert_to_register(adxl345_handle_t *handle, float g, uint8_t *reg);

/**
 * @brief      convert the register raw data to the tap threshold
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *g points to a tap threshold buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_tap_threshold_convert_to_data(adxl345_handle_t *handle, uint8_t reg, float *g);

/**
 * @brief     set the axis offset
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] x is the x axis offset
 * @param[in] y is the y axis offset
 * @param[in] z is the z axis offset
 * @return    status code
 *            - 0 success
 *            - 1 set offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_offset(adxl345_handle_t *handle, int8_t x, int8_t y, int8_t z);

/**
 * @brief      get the axis offset
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *x points to an x axis offset
 * @param[out] *y points to a y axis offset
 * @param[out] *z points to a z axis offset
 * @return     status code
 *             - 0 success
 *             - 1 get offset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_offset(adxl345_handle_t *handle, int8_t *x, int8_t *y, int8_t *z);

/**
 * @brief      convert the offset to the register raw data
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  g is the offset
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_offset_convert_to_register(adxl345_handle_t *handle, float g, int8_t *reg);

/**
 * @brief      convert the register raw data to the offset
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *g points to an offset buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_offset_convert_to_data(adxl345_handle_t *handle, int8_t reg, float *g);

/**
 * @brief     set the duration
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] t is the duration
 * @return    status code
 *            - 0 success
 *            - 1 set duration failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_duration(adxl345_handle_t *handle, uint8_t t);

/**
 * @brief      get the duration
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *t points to a duration buffer
 * @return     status code
 *             - 0 success
 *             - 1 get duration failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_duration(adxl345_handle_t *handle, uint8_t *t);

/**
 * @brief      convert the duration to the register raw data
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  us is the duration
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_duration_convert_to_register(adxl345_handle_t *handle, uint32_t us, uint8_t *reg);

/**
 * @brief      convert the register raw data to the duration
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *us points to a duration buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_duration_convert_to_data(adxl345_handle_t *handle, uint8_t reg, uint32_t *us);

/**
 * @brief     set the latent
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] t is the latent time
 * @return    status code
 *            - 0 success
 *            - 1 set latent failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_latent(adxl345_handle_t *handle, uint8_t t);

/**
 * @brief      get the latent
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *t points to a latent time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get latent failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_latent(adxl345_handle_t *handle, uint8_t *t);

/**
 * @brief      convert the latent to the register raw data
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  ms is the time
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_latent_convert_to_register(adxl345_handle_t *handle, float ms, uint8_t *reg);

/**
 * @brief      convert the register raw data to the latent
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *ms points to a latent buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_latent_convert_to_data(adxl345_handle_t *handle, uint8_t reg, float *ms);

/**
 * @brief     set the window
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] t is the window time
 * @return    status code
 *            - 0 success
 *            - 1 set window failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_window(adxl345_handle_t *handle, uint8_t t);

/**
 * @brief      get the window
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *t points to a window time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get window failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_window(adxl345_handle_t *handle, uint8_t *t);

/**
 * @brief      convert the window time to the register raw data
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  ms is the window time
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_window_convert_to_register(adxl345_handle_t *handle, float ms, uint8_t *reg);

/**
 * @brief      convert the register raw data to the window time
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *ms points to a window time buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_window_convert_to_data(adxl345_handle_t *handle, uint8_t reg, float *ms);

/**
 * @brief     set the action threshold
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] threshold is the action threshold
 * @return    status code
 *            - 0 success
 *            - 1 set action threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_action_threshold(adxl345_handle_t *handle, uint8_t threshold);

/**
 * @brief      get the action threshold
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *threshold points to an action threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get action threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_action_threshold(adxl345_handle_t *handle, uint8_t *threshold);

/**
 * @brief      convert the action threshold to the register raw data
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  g is the action threshold
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_action_threshold_convert_to_register(adxl345_handle_t *handle, float g, uint8_t *reg);

/**
 * @brief      convert the register raw data to the action threshold
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *g points to an action threshold buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_action_threshold_convert_to_data(adxl345_handle_t *handle, uint8_t reg, float *g);

/**
 * @brief     set the inaction threshold
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] threshold is the inaction threshold
 * @return    status code
 *            - 0 success
 *            - 1 set inaction threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_inaction_threshold(adxl345_handle_t *handle, uint8_t threshold);

/**
 * @brief      get the inaction threshold
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *threshold points to an inaction threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get inaction threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_inaction_threshold(adxl345_handle_t *handle, uint8_t *threshold);

/**
 * @brief      convert the inaction threshold to the register raw data
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  g is the inaction threshold
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_inaction_threshold_convert_to_register(adxl345_handle_t *handle, float g, uint8_t *reg);

/**
 * @brief      convert the register raw data to the inaction threshold
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *g points to an inaction threshold buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_inaction_threshold_convert_to_data(adxl345_handle_t *handle, uint8_t reg, float *g);

/**
 * @brief     set the inaction time
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] t is the inaction time
 * @return    status code
 *            - 0 success
 *            - 1 set inaction time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_inaction_time(adxl345_handle_t *handle, uint8_t t);

/**
 * @brief      get the inaction time
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *t points to an inaction time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get inaction time failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_inaction_time(adxl345_handle_t *handle, uint8_t *t);

/**
 * @brief      convert the inaction time to the register raw data
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  s is the inaction time
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_inaction_time_convert_to_register(adxl345_handle_t *handle, uint8_t s, uint8_t *reg);

/**
 * @brief      convert the register raw data to the inaction time
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *s points to an inaction time buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_inaction_time_convert_to_data(adxl345_handle_t *handle, uint8_t reg, uint8_t *s);

/**
 * @brief     enable or disable the action or inaction
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] type is the action or inaction type
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set action inaction failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_action_inaction(adxl345_handle_t *handle, adxl345_action_inaction_t type, adxl345_bool_t enable);

/**
 * @brief      get the action or inaction status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  type is the action or inaction type
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get action inaction failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_action_inaction(adxl345_handle_t *handle, adxl345_action_inaction_t type, adxl345_bool_t *enable);

/**
 * @brief     set the action coupled
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] coupled is the action coupled
 * @return    status code
 *            - 0 success
 *            - 1 set action coupled failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_action_coupled(adxl345_handle_t *handle, adxl345_coupled_t coupled);

/**
 * @brief      get the action coupled
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *coupled points to an action coupled buffer
 * @return     status code
 *             - 0 success
 *             - 1 get action coupled failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_action_coupled(adxl345_handle_t *handle, adxl345_coupled_t *coupled);

/**
 * @brief     set the inaction coupled
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] coupled is the inaction coupled
 * @return    status code
 *            - 0 success
 *            - 1 set inaction coupled failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_inaction_coupled(adxl345_handle_t *handle, adxl345_coupled_t coupled);

/**
 * @brief      get the inaction coupled
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *coupled points to an inaction coupled buffer
 * @return     status code
 *             - 0 success
 *             - 1 get inaction coupled failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_inaction_coupled(adxl345_handle_t *handle, adxl345_coupled_t *coupled);

/**
 * @brief     set the free fall threshold
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] threshold is the free fall threshold
 * @return    status code
 *            - 0 success
 *            - 1 set free fall threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_free_fall_threshold(adxl345_handle_t *handle, uint8_t threshold);

/**
 * @brief      get the free fall threshold
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *threshold points to a free fall threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get free fall threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_free_fall_threshold(adxl345_handle_t *handle, uint8_t *threshold);

/**
 * @brief      convert the free fall threshold to the register raw data
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  g is the free fall threshold
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_free_fall_threshold_convert_to_register(adxl345_handle_t *handle, float g, uint8_t *reg);

/**
 * @brief      convert the register raw data to the free fall threshold
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *g points to a free fall threshold buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_free_fall_threshold_convert_to_data(adxl345_handle_t *handle, uint8_t reg, float *g);

/**
 * @brief     set the free fall time
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] t is the free fall time
 * @return    status code
 *            - 0 success
 *            - 1 set free fall time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_free_fall_time(adxl345_handle_t *handle, uint8_t t);

/**
 * @brief      get the free fall time
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *t points to a free fall time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get free fall time failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_free_fall_time(adxl345_handle_t *handle, uint8_t *t);

/**
 * @brief      convert the free fall time to the register raw data
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  ms is the free fall time
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_free_fall_time_convert_to_register(adxl345_handle_t *handle, uint16_t ms, uint8_t *reg);

/**
 * @brief      convert the register raw data to the free fall time
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *ms points to a free fall time buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_free_fall_time_convert_to_data(adxl345_handle_t *handle, uint8_t reg, uint16_t *ms);

/**
 * @brief     enable or disable the tap axis
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] axis is the tap axis
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set tap axis failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_tap_axis(adxl345_handle_t *handle, adxl345_tap_axis_t axis, adxl345_bool_t enable);

/**
 * @brief      get the tap axis status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  axis is the tap axis
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tap axis failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_get_tap_axis(adxl345_handle_t *handle, adxl345_tap_axis_t axis, adxl345_bool_t *enable);

/**
 * @brief     enable or disable the tap suppress
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set tap suppress failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_tap_suppress(adxl345_handle_t *handle, adxl345_bool_t enable);

/**
 * @brief      get the tap suppress status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tap suppress failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_tap_suppress(adxl345_handle_t *handle, adxl345_bool_t *enable);

/**
 * @brief      get the tap status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *status points to a tap status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tap status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_tap_status(adxl345_handle_t *handle, uint8_t *status);

/**
 * @brief     set the sampling rate
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] rate is the sampling rate
 * @return    status code
 *            - 0 success
 *            - 1 set rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_rate(adxl345_handle_t *handle, adxl345_rate_t rate);

/**
 * @brief      get the sampling rate
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *rate points to a sampling rate buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rate failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_rate(adxl345_handle_t *handle, adxl345_rate_t *rate);

/**
 * @brief     enable or disable the self test
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set self test failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_self_test(adxl345_handle_t *handle, adxl345_bool_t enable);

/**
 * @brief      get the self test status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get self test failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_self_test(adxl345_handle_t *handle, adxl345_bool_t *enable);

/**
 * @brief     set the chip spi wire
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] wire is the spi wire
 * @return    status code
 *            - 0 success
 *            - 1 set spi wire failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_spi_wire(adxl345_handle_t *handle, adxl345_spi_wire_t wire);

/**
 * @brief      get the chip spi wire
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *wire points to a spi wire buffer
 * @return     status code
 *             - 0 success
 *             - 1 get spi wire failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_spi_wire(adxl345_handle_t *handle, adxl345_spi_wire_t *wire);

/**
 * @brief     enable or disable the full resolution
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set full resolution failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_full_resolution(adxl345_handle_t *handle, adxl345_bool_t enable);

/**
 * @brief      get the full resolution status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get full resolution failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_full_resolution(adxl345_handle_t *handle, adxl345_bool_t *enable);

/**
 * @brief     enable or disable the justify
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set justify failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_justify(adxl345_handle_t *handle, adxl345_justify_t enable);

/**
 * @brief      get the justify status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get justify failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_justify(adxl345_handle_t *handle, adxl345_justify_t *enable);

/**
 * @brief     set the chip range
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] range is the measurement range
 * @return    status code
 *            - 0 success
 *            - 1 set range failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_range(adxl345_handle_t *handle, adxl345_range_t range);

/**
 * @brief      get the chip range
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *range points to a measurement range buffer
 * @return     status code
 *             - 0 success
 *             - 1 get range failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_range(adxl345_handle_t *handle, adxl345_range_t *range);

/**
 * @brief     set the chip mode
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] mode is the chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_mode(adxl345_handle_t *handle, adxl345_mode_t mode);

/**
 * @brief      get the chip mode
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *mode points to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_mode(adxl345_handle_t *handle, adxl345_mode_t *mode);

/**
 * @brief     set the trigger pin
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] pin is the trigger pin
 * @return    status code
 *            - 0 success
 *            - 1 set trigger pin failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_trigger_pin(adxl345_handle_t *handle, adxl345_interrupt_pin_t pin);

/**
 * @brief      get the trigger pin
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *pin points to a trigger pin buffer
 * @return     status code
 *             - 0 success
 *             - 1 get trigger pin failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_trigger_pin(adxl345_handle_t *handle, adxl345_interrupt_pin_t *pin);

/**
 * @brief      get the trigger status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *status points to a trigger status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get trigger status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_trigger_status(adxl345_handle_t *handle, adxl345_trigger_status_t *status);

/**
 * @brief     enable or disable the activity and inactivity linking
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set link activity inactivity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_link_activity_inactivity(adxl345_handle_t *handle, adxl345_bool_t enable);

/**
 * @brief      get the activity and inactivity linking status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get link activity inactivity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_link_activity_inactivity(adxl345_handle_t *handle, adxl345_bool_t *enable);

/**
 * @brief     enable or disable the auto sleep
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set auto sleep failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_auto_sleep(adxl345_handle_t *handle, adxl345_bool_t enable);

/**
 * @brief      get the auto sleep status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get auto sleep failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_auto_sleep(adxl345_handle_t *handle, adxl345_bool_t *enable);

/**
 * @brief     enable or disable the measure
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set measure failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_measure(adxl345_handle_t *handle, adxl345_bool_t enable);

/**
 * @brief      get the measure status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get measure failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_measure(adxl345_handle_t *handle, adxl345_bool_t *enable);

/**
 * @brief     enable or disable the sleep mode
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set sleep failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_sleep(adxl345_handle_t *handle, adxl345_bool_t enable);

/**
 * @brief      get the sleep mode status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sleep failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_sleep(adxl345_handle_t *handle, adxl345_bool_t *enable);

/**
 * @brief     set the sleep frequency
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] sleep_frequency is the sleep frequency
 * @return    status code
 *            - 0 success
 *            - 1 set sleep frequency failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_sleep_frequency(adxl345_handle_t *handle, adxl345_sleep_frequency_t sleep_frequency);

/**
 * @brief     set the sleep frequency
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] sleep_frequency is the sleep frequency
 * @return    status code
 *            - 0 success
 *            - 1 set sleep frequency failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_sleep_frequency(adxl345_handle_t *handle, adxl345_sleep_frequency_t sleep_frequency);

/**
 * @brief      get the sleep frequency
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *sleep_frequency points to a sleep frequency buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sleep frequency failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_sleep_frequency(adxl345_handle_t *handle, adxl345_sleep_frequency_t *sleep_frequency);

/**
 * @}
 */

/**
 * @defgroup adxl345_interrupt_driver adxl345 interrupt driver function
 * @brief    adxl345 interrupt driver modules
 * @ingroup  adxl345_driver
 * @{
 */

/**
 * @brief     enable or disable the interrupt
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] type is the interrupt type
 * @param[in] enable is the bool value
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_interrupt(adxl345_handle_t *handle, adxl345_interrupt_t type, adxl345_bool_t enable);

/**
 * @brief      get the interrupt status
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  type is the interrupt type
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_interrupt(adxl345_handle_t *handle, adxl345_interrupt_t type, adxl345_bool_t *enable);

/**
 * @brief      get the interrupt source
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *source points to an interrupt source buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt source failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_interrupt_source(adxl345_handle_t *handle, uint8_t *source);

/**
 * @brief     set the interrupt map
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] type is the interrupt type
 * @param[in] pin is the interrupt pin
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt map failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_interrupt_map(adxl345_handle_t *handle, adxl345_interrupt_t type, adxl345_interrupt_pin_t pin);

/**
 * @brief      get the interrupt map
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  type is the interrupt type
 * @param[out] *pin points to an interrupt pin buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt map failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_interrupt_map(adxl345_handle_t *handle, adxl345_interrupt_t type, adxl345_interrupt_pin_t *pin);

/**
 * @brief     set the interrupt active level
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] active_level is the interrupt active level
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt active level failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_interrupt_active_level(adxl345_handle_t *handle, adxl345_interrupt_active_level_t active_level);

/**
 * @brief      get the interrupt active level
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *active_level points to an interrupt active level buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt active level failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_interrupt_active_level(adxl345_handle_t *handle, adxl345_interrupt_active_level_t *active_level);

/**
 * @}
 */

/**
 * @defgroup adxl345_fifo_driver adxl345 fifo driver function
 * @brief    adxl345 fifo driver modules
 * @ingroup  adxl345_driver
 * @{
 */

/**
 * @brief     set the fifo watermark
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] level is the watermark level
 * @return    status code
 *            - 0 success
 *            - 1 set watermark failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      level <= 0x1F
 */
uint8_t adxl345_set_watermark(adxl345_handle_t *handle, uint8_t level);

/**
 * @brief      get the fifo watermark
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *level points to a watermark level buffer
 * @return     status code
 *             - 0 success
 *             - 1 get watermark failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_watermark(adxl345_handle_t *handle, uint8_t *level);

/**
 * @brief      get the current fifo watermark level
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[out] *level points to a current watermark level buffer
 * @return     status code
 *             - 0 success
 *             - 1 get watermark level failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_watermark_level(adxl345_handle_t *handle, uint8_t *level);

/**
 * @}
 */

/**
 * @defgroup adxl345_extern_driver adxl345 extern driver function
 * @brief    adxl345 extern driver modules
 * @ingroup  adxl345_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to an adxl345 handle structure
 * @param[in] reg is the register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t adxl345_set_reg(adxl345_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an adxl345 handle structure
 * @param[in]  reg is the register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t adxl345_get_reg(adxl345_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
