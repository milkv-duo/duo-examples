#ifndef _TCS34725_H_
#define _TCS34725_H_
 
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

 
#define TCS34725_ADDR             (0x29)    // 设备地址 Device address
#define TCS34725_COMMAND_BIT      (0x80)    // 命令字节 command byte
 
/* TCS34725传感器配置寄存器 TCS34725 sensor configuration register */
#define TCS34725_ENABLE           (0x00)    // 启用传感器 enable sensor
#define TCS34725_ATIME            (0x01)    // 集成时间 Integration time
#define TCS34725_WTIME            (0x03)    // R / W 等待时间 R/W waiting time
#define TCS34725_AILTL            (0x04)
#define TCS34725_AILTH            (0x05)
#define TCS34725_AIHTL            (0x06)
#define TCS34725_AIHTH            (0x07)
#define TCS34725_PERS             (0x0C)
#define TCS34725_CONFIG           (0x0C)
#define TCS34725_CONTROL          (0x0F)
#define TCS34725_ID               (0x12)    // 设备识别号 Device identification number 0x44 = TCS34721/TCS34725, 0x4D = TCS34723/TCS34727
#define TCS34725_STATUS           (0x13)    // 设备状态 Device status
#define TCS34725_CDATAL           (0x14)    // 光照强度 light intensity
#define TCS34725_CDATAH           (0x15)
#define TCS34725_RDATAL           (0x16)    // 红色数据 Data of Red
#define TCS34725_RDATAH           (0x17)
#define TCS34725_GDATAL           (0x18)    // 绿色数据 Data of Green
#define TCS34725_GDATAH           (0x19)
#define TCS34725_BDATAL           (0x1A)    // 蓝色数据 Data of Blue
#define TCS34725_BDATAH           (0x1B)
 
/* 启动传感器 Start sensor */
#define TCS34725_ENABLE_AIEN      (0x10)    // RGBC中断使能 RGBC interrupt enable
#define TCS34725_ENABLE_WEN       (0x08)    // 等待计时器启用：写1激活 Wait timer enable: write 1 to activate
#define TCS34725_ENABLE_AEN       (0x02)    // RGBC启用：写1激活 RGBC enable: write 1 to activate
#define TCS34725_ENABLE_PON       (0x01)    // 内部振荡器：写入1激活 Internal oscillator: activated by writing 1

/* 集成时间配置参数 Integration time configuration parameters
 * 最大RGBC计数 Maximum RGBC count = (256 - cycles) × 1024 
 * 集成时间 Integration time ≈ (256 - cycles) × 2.4ms */
typedef enum
{
    TCS34725_INTEGRATIONTIME_2_4MS  = 0xFF,   // 2.4ms - 1 cycles   - Max Count: 1024
    TCS34725_INTEGRATIONTIME_24MS   = 0xF6,   // 24ms  - 10 cycles  - Max Count: 10240
    TCS34725_INTEGRATIONTIME_50MS   = 0xEC,   // 50ms  - 20 cycles  - Max Count: 20480
    TCS34725_INTEGRATIONTIME_101MS  = 0xD5,   // 101ms - 42 cycles  - Max Count: 43008
    TCS34725_INTEGRATIONTIME_154MS  = 0xC0,   // 154ms - 64 cycles  - Max Count: 65535
    TCS34725_INTEGRATIONTIME_700MS  = 0x00    // 700ms - 256 cycles - Max Count: 65535
}
tcs34725_integration_time_t;
 
/* 增益倍数 Gain multiple */
typedef enum
{
    TCS34725_GAIN_1X                = 0x00,   // 1X
    TCS34725_GAIN_4X                = 0x01,   // 4X
    TCS34725_GAIN_16X               = 0x02,   // 16X
    TCS34725_GAIN_60X               = 0x03    // 60X
}
tcs34725_gain_t;
 
struct tcs34725_config
{
	char name[20];
    bool interrupt_start;
    tcs34725_integration_time_t integration_time;
    tcs34725_gain_t gain;
}tcs34725_config_t;
 
uint8_t tcs34725_start(bool interrupt_start);
uint8_t tcs34725_stop(void);
uint8_t get_tcs34725_type(void);
uint8_t set_tcs34725_integration_time(tcs34725_integration_time_t integration_time);
uint8_t set_tcs34725_gain(tcs34725_gain_t gain);
uint8_t get_tcs34725_rgbc(uint16_t *colour_r, uint16_t *colour_g, uint16_t *colour_b, uint16_t *colour_c);
tcs34725_integration_time_t get_tcs34725_integration_time(void);
tcs34725_gain_t get_tcs34725_gain(void);
 
#ifdef __cplusplus
} /* extern "C" */
#endif
 
#endif /* _TCS34725_H_ */