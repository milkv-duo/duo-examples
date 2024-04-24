/**
  ******************************************************************************
  * @file       cvi_adxl345.c
  * @brief      cvi18xx系列芯片adxl345驱动API对接 cvi18xx series chip adxl345 driver API docking
  * @note       milkv@rjgawuie
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ******************************************************************************
  */

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include <wiringx.h>
#include "adxl345.h"

adxl345_handle_t adxl345_handle;

/**
 * @brief     basic example init
 * @param[in] interface is the chip interface
 * @param[in] addr_pin is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t adxl345_basic_init(adxl345_interface_t interface, adxl345_address_t addr_pin)
{
    uint8_t res;
    int8_t reg;
    
    /* link interface function */
    DRIVER_ADXL345_LINK_INIT(&adxl345_handle, adxl345_handle_t);
    DRIVER_ADXL345_LINK_IIC_INIT(&adxl345_handle, duo_i2cinit);
    DRIVER_ADXL345_LINK_IIC_DEINIT(&adxl345_handle, duo_i2cdeinit);
    DRIVER_ADXL345_LINK_IIC_READ(&adxl345_handle, duo_i2cread);
    DRIVER_ADXL345_LINK_IIC_WRITE(&adxl345_handle, duo_i2cwrite);
    DRIVER_ADXL345_LINK_SPI_INIT(&adxl345_handle, duo_spiinit);
    DRIVER_ADXL345_LINK_SPI_DEINIT(&adxl345_handle, duo_spideinit);
    DRIVER_ADXL345_LINK_SPI_READ(&adxl345_handle, duo_spiread);
    DRIVER_ADXL345_LINK_SPI_WRITE(&adxl345_handle, duo_spiwrite);
    DRIVER_ADXL345_LINK_DELAY_MS(&adxl345_handle, duo_delayms);
    DRIVER_ADXL345_LINK_DEBUG_PRINT(&adxl345_handle, printf);
    DRIVER_ADXL345_LINK_RECEIVE_CALLBACK(&adxl345_handle, duo_rec_cb);
    
    /* set the interface */
    res = adxl345_set_interface(&adxl345_handle, interface);
    if (res != 0)
    {
        printf("adxl345: set interface failed.\n");
       
        return 1;
    }
    
    /* set addr pin */
    res = adxl345_set_addr_pin(&adxl345_handle, addr_pin);
    if (res != 0)
    {
        printf("adxl345: set addr pin failed.\n");
       
        return 1;
    }
    
    /* adxl345 initialization */
    res = adxl345_init(&adxl345_handle);
    if (res != 0)
    {
        printf("adxl345: init failed.\n");
       
        return 1;
    }
    
    /* set default rate */
    res = adxl345_set_rate(&adxl345_handle, ADXL345_BASIC_DEFAULT_RATE);
    if (res != 0)
    {
        printf("adxl345: set rate failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default spi wire */
    res = adxl345_set_spi_wire(&adxl345_handle, ADXL345_BASIC_DEFAULT_SPI_WIRE);
    if (res != 0)
    {
        printf("adxl345: set spi wire failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set interrupt pin */
    res = adxl345_set_interrupt_active_level(&adxl345_handle, ADXL345_BASIC_DEFAULT_INTERRUPT_ACTIVE_LEVEL);
    if (res != 0)
    {
        printf("adxl345: set adxl345 set interrupt active level failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set full resolution */
    res = adxl345_set_full_resolution(&adxl345_handle, ADXL345_BASIC_DEFAULT_FULL_RESOLUTION);
    if (res != 0)
    {
        printf("adxl345: set full resolution failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set auto sleep */
    res = adxl345_set_auto_sleep(&adxl345_handle, ADXL345_BASIC_DEFAULT_AUTO_SLEEP);
    if (res != 0)
    {
        printf("adxl345: set auto sleep failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set sleep */
    res = adxl345_set_sleep(&adxl345_handle, ADXL345_BASIC_DEFAULT_SLEEP);
    if (res != 0)
    {
        printf("adxl345: set sleep failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set sleep frequency */
    res = adxl345_set_sleep_frequency(&adxl345_handle, ADXL345_BASIC_DEFAULT_SLEEP_FREQUENCY);
    if (res != 0)
    {
        printf("adxl345: set sleep frequency failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set justify */
    res = adxl345_set_justify(&adxl345_handle, ADXL345_BASIC_DEFAULT_JUSTIFY);
    if (res != 0)
    {
        printf("adxl345: set justify failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set range */
    res = adxl345_set_range(&adxl345_handle, ADXL345_BASIC_DEFAULT_RANGE);
    if (res != 0)
    {
        printf("adxl345: set range failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set mode */
    res = adxl345_set_mode(&adxl345_handle, ADXL345_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        printf("adxl345: set mode failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set trigger pin */
    res = adxl345_set_trigger_pin(&adxl345_handle, ADXL345_BASIC_DEFAULT_TRIGGER_PIN);
    if (res != 0)
    {
        printf("adxl345: set trigger pin failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set watermark level */
    res = adxl345_set_watermark(&adxl345_handle, ADXL345_BASIC_DEFAULT_WATERMARK);
    if (res != 0)
    {
        printf("adxl345: set watermark failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default offset */
    res = adxl345_offset_convert_to_register(&adxl345_handle, ADXL345_BASIC_DEFAULT_OFFSET, (int8_t *)&reg);
    if (res != 0)
    {
        printf("adxl345: offset convert to register failed.\n");
        (void)adxl345_deinit(&adxl345_handle); 
        
        return 1;
    }
    res = adxl345_set_offset(&adxl345_handle, reg, reg, reg);
    if (res != 0)
    {
        printf("adxl345: set offset failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default tap threshold */
    res = adxl345_tap_threshold_convert_to_register(&adxl345_handle, ADXL345_BASIC_DEFAULT_TAP_THRESHOLD, (uint8_t *)&reg);
    if (res != 0)
    {
        printf("adxl345: tap threshold convert to register failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_tap_threshold(&adxl345_handle, reg);
    if (res != 0)
    {
        printf("adxl345: set tap threshold failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default duration */
    res = adxl345_duration_convert_to_register(&adxl345_handle, ADXL345_BASIC_DEFAULT_DURATION, (uint8_t *)&reg);
    if (res != 0)
    {
        printf("adxl345: duration convert to register failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_duration(&adxl345_handle, reg);
    if (res != 0)
    {
        printf("adxl345: set duration failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set latent time */
    res = adxl345_latent_convert_to_register(&adxl345_handle, ADXL345_BASIC_DEFAULT_LATENT, (uint8_t *)&reg);
    if (res != 0)
    {
        printf("adxl345: latent convert to register failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_latent(&adxl345_handle, reg);
    if (res != 0)
    {
        printf("adxl345: set latent failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set window time */
    res = adxl345_window_convert_to_register(&adxl345_handle, ADXL345_BASIC_DEFAULT_WINDOW, (uint8_t *)&reg);
    if (res != 0)
    {
        printf("adxl345: window convert to register failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_window(&adxl345_handle, reg);
    if (res != 0)
    {
        printf("adxl345: set window failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* disable tap */
    res = adxl345_set_tap_axis(&adxl345_handle, ADXL345_TAP_AXIS_X, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set tap axis failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_tap_axis(&adxl345_handle, ADXL345_TAP_AXIS_Y, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set tap axis failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_tap_axis(&adxl345_handle, ADXL345_TAP_AXIS_Z, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set tap axis failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default suppress */
    res = adxl345_set_tap_suppress(&adxl345_handle, ADXL345_BASIC_DEFAULT_TAP_SUPPRESS);
    if (res != 0)
    {
        printf("adxl345: set tap suppress failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default single tap map */
    res = adxl345_set_interrupt_map(&adxl345_handle, ADXL345_INTERRUPT_SINGLE_TAP, ADXL345_BASIC_DEFAULT_INTERRUPT_SINGLE_TAP_MAP);
    if (res != 0)
    {
        printf("adxl345: set interrupt map failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* disable single tap */
    res = adxl345_set_interrupt(&adxl345_handle, ADXL345_INTERRUPT_SINGLE_TAP, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set interrupt failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default double tap map */
    res = adxl345_set_interrupt_map(&adxl345_handle, ADXL345_INTERRUPT_DOUBLE_TAP, ADXL345_BASIC_DEFAULT_INTERRUPT_DOUBLE_TAP_MAP);
    if (res != 0)
    {
        printf("adxl345: set interrupt map failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* disable double tap */
    res = adxl345_set_interrupt(&adxl345_handle, ADXL345_INTERRUPT_DOUBLE_TAP, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set interrupt failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default linking activity and inactivity */
    res = adxl345_set_link_activity_inactivity(&adxl345_handle, ADXL345_BASIC_DEFAULT_LINK_ACTIVITY_INACTIVITY);
    if (res != 0)
    {
        printf("adxl345: set link activity inactivity failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default action threshold */
    res = adxl345_action_threshold_convert_to_register(&adxl345_handle, ADXL345_BASIC_DEFAULT_ACTION_THRESHOLD, (uint8_t *)&reg);
    if (res != 0)
    {
        printf("adxl345: action threshold convert to register failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_action_threshold(&adxl345_handle, reg);
    if (res != 0)
    {
        printf("adxl345: set action threshold failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default inaction threshold */
    res = adxl345_inaction_threshold_convert_to_register(&adxl345_handle, ADXL345_BASIC_DEFAULT_INACTION_THRESHOLD, (uint8_t *)&reg);
    if (res != 0)
    {
        printf("adxl345: inaction threshold convert to register failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_inaction_threshold(&adxl345_handle, reg);
    if (res != 0)
    {
        printf("adxl345: set inaction threshold failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default inaction time */
    res = adxl345_inaction_time_convert_to_register(&adxl345_handle, ADXL345_BASIC_DEFAULT_INACTION_TIME, (uint8_t *)&reg);
    if (res != 0)
    {
        printf("adxl345: inaction time convert to register failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_inaction_time(&adxl345_handle, reg);
    if (res != 0)
    {
        printf("adxl345: set inaction time failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* disable action */
    res = adxl345_set_action_inaction(&adxl345_handle, ADXL345_ACTION_X, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set action inaction failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_action_inaction(&adxl345_handle, ADXL345_ACTION_Y, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set action inaction failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_action_inaction(&adxl345_handle, ADXL345_ACTION_Z, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set action inaction failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_action_inaction(&adxl345_handle, ADXL345_INACTION_X, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set action inaction failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_action_inaction(&adxl345_handle, ADXL345_INACTION_Y, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set action inaction failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_action_inaction(&adxl345_handle, ADXL345_INACTION_Z, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set action inaction failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default action coupled */
    res = adxl345_set_action_coupled(&adxl345_handle, ADXL345_BASIC_DEFAULT_ACTION_COUPLED);
    if (res != 0)
    {
        printf("adxl345: set action coupled failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default inaction coupled */
    res = adxl345_set_inaction_coupled(&adxl345_handle, ADXL345_BASIC_DEFAULT_INACTION_COUPLED);
    if (res != 0)
    {
        printf("adxl345: set inaction coupled failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default activity map */
    res = adxl345_set_interrupt_map(&adxl345_handle, ADXL345_INTERRUPT_ACTIVITY, ADXL345_BASIC_DEFAULT_INTERRUPT_ACTIVITY_MAP);
    if (res != 0)
    {
        printf("adxl345: set interrupt map failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* disable activity interrupt */
    res = adxl345_set_interrupt(&adxl345_handle, ADXL345_INTERRUPT_ACTIVITY, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set interrupt failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default inactivity map */
    res = adxl345_set_interrupt_map(&adxl345_handle, ADXL345_INTERRUPT_INACTIVITY, ADXL345_BASIC_DEFAULT_INTERRUPT_INACTIVITY_MAP);
    if (res != 0)
    {
        printf("adxl345: set interrupt map failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* disable inactivity interrupt */
    res = adxl345_set_interrupt(&adxl345_handle, ADXL345_INTERRUPT_INACTIVITY, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set interrupt failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set free fall threshold */
    res = adxl345_free_fall_threshold_convert_to_register(&adxl345_handle, ADXL345_BASIC_DEFAULT_FREE_FALL_THRESHOLD, (uint8_t *)&reg);
    if (res != 0)
    {
        printf("adxl345: free fall threshold convert to register failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_free_fall_threshold(&adxl345_handle, reg);
    if (res != 0)
    {
        printf("adxl345: set free fall threshold failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set free fall time */
    res = adxl345_free_fall_time_convert_to_register(&adxl345_handle, ADXL345_BASIC_DEFAULT_FREE_FALL_TIME, (uint8_t *)&reg);
    if (res != 0)
    {
        printf("adxl345: free fall time convert to register failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_free_fall_time(&adxl345_handle, reg);
    if (res != 0)
    {
        printf("adxl345: set free fall time failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default free fall map */
    res = adxl345_set_interrupt_map(&adxl345_handle, ADXL345_INTERRUPT_FREE_FALL, ADXL345_BASIC_DEFAULT_INTERRUPT_FREE_FALL_MAP);
    if (res != 0)
    {
        printf("adxl345: set interrupt map failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* disable free fall interrupt */
    res = adxl345_set_interrupt(&adxl345_handle, ADXL345_INTERRUPT_FREE_FALL, ADXL345_BOOL_FALSE);
    if (res != 0)
    {
        printf("adxl345: set interrupt failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default data ready map */
    res = adxl345_set_interrupt_map(&adxl345_handle, ADXL345_INTERRUPT_DATA_READY, ADXL345_BASIC_DEFAULT_INTERRUPT_DATA_READY_MAP);
    if (res != 0)
    {
        printf("adxl345: set interrupt map failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_interrupt(&adxl345_handle, ADXL345_INTERRUPT_DATA_READY, ADXL345_BASIC_DEFAULT_INTERRUPT_DATA_READY);
    if (res != 0)
    {
        printf("adxl345: set interrupt failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default watermark map */
    res = adxl345_set_interrupt_map(&adxl345_handle, ADXL345_INTERRUPT_WATERMARK, ADXL345_BASIC_DEFAULT_INTERRUPT_WATERMARK_MAP);
    if (res != 0)
    {
        printf("adxl345: set interrupt map failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_interrupt(&adxl345_handle, ADXL345_INTERRUPT_WATERMARK, ADXL345_BASIC_DEFAULT_INTERRUPT_WATERMARK);
    if (res != 0)
    {
        printf("adxl345: set interrupt failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* set default overrun map */
    res = adxl345_set_interrupt_map(&adxl345_handle, ADXL345_INTERRUPT_OVERRUN, ADXL345_BASIC_DEFAULT_INTERRUPT_OVERRUN_MAP);
    if (res != 0)
    {
        printf("adxl345: set interrupt map failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    res = adxl345_set_interrupt(&adxl345_handle, ADXL345_INTERRUPT_OVERRUN, ADXL345_BASIC_DEFAULT_INTERRUPT_OVERRUN);
    if (res != 0)
    {
        printf("adxl345: set interrupt failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    /* start measure */
    res = adxl345_set_measure(&adxl345_handle, ADXL345_BOOL_TRUE);
    if (res != 0)
    {
        printf("adxl345: set measure failed.\n");
        (void)adxl345_deinit(&adxl345_handle);
        
        return 1;
    }
    
    return 0;
}
/**
 * @brief      basic example read
 * @param[out] *g points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t adxl345_basic_read(float g[3])
{
    int16_t r[3];
    float g_out[3];
    uint16_t len;
    
    len = 1;
    
    /* read data */
    if (adxl345_read(&adxl345_handle, (int16_t (*)[3])&r, (float (*)[3])&g_out, (uint16_t *)&len) != 0)
    {
        return 1;
    }
    
    /* copy data */
    g[0] = g_out[0];
    g[1] = g_out[1];
    g[2] = g_out[2];

    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t adxl345_basic_deinit(void)
{
    if (adxl345_deinit(&adxl345_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
