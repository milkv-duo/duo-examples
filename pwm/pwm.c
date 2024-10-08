/**
 * Copyright (c) 2023 Milk-V
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#include <stdio.h>
#include <unistd.h>

#include <wiringx.h>

 /* Duo 相关芯片的 PWM 示例代码。
    Sample code for PWM in Chip Duo.

    注意：确保设备在3.3伏而不是5伏的电压下使用。Duo GPIO 不能在5伏电平下使用。
    NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Duo
    GPIO cannot be used at 5v.

    如果你想在5伏的电压下使用该模块，需要额外加装电平转换器转换电平。
    You will need to use a level shifter on the lines if you want to run the
    board at 5v.

    请将示波器、逻辑分析仪或是任何能使用 PWM 控制的元件接到任意支持 PWM 的引脚上。
    Please connect an oscilloscope, logic analyzer, or any component that 
    can use PWM control to any PWM-supported pin.

    运行程序前请确保引脚复用在正确的功能上。
    Please make sure the pins are multiplexed to the correct functions before 
    running the program.

    运行程序后请按提示输入 [引脚号]:[占空比] 以设置对应引脚上的 PWM 信号，比如 3:500 。
    After running the program, please follow the prompts to enter the 
    [pin number]:[duty] cycle to set the PWM signal on the corresponding pin, 
    such as 3:500.
 */

int main() {
    int pwm_pin = 3;
    int duty = 0;

    // Duo:     milkv_duo
    // Duo256M: milkv_duo256m
    // DuoS:    milkv_duos
    if(wiringXSetup("milkv_duo", NULL) == -1) {
        wiringXGC();
        return 1;
    }

    if(wiringXValidGPIO(pwm_pin) != 0) {
        printf("Invalid GPIO %d\n", pwm_pin);
    }

    printf("PWM Period fixed to 1000ns, please set Duty in range of 0-1000.\n");
    printf("Enter -> Pin:Duty\n");
    scanf("%d:%d",&pwm_pin,&duty);

    if(duty < 0) duty = 0;
    if(duty > 1000) duty = 1000;

    //设置 PWM 周期为 1000 ns; Set PWM Period 1000 ns long.
    wiringXPWMSetPeriod(pwm_pin, 1000);

    //设置 PWM 占空比; Set PWM Duty.
    wiringXPWMSetDuty(pwm_pin, duty);

    //设置 PWM 极性并使能; Set PWM Polarity and enable.
    wiringXPWMSetPolarity(pwm_pin, 0);
    wiringXPWMEnable(pwm_pin, 1);

    printf("pin %d -> duty %d\n",pwm_pin ,duty);

    return 0;
}
