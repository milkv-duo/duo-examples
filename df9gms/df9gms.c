#include <stdio.h>
#include <unistd.h>

#include <wiringx.h>

/*
    Duo
    ------------------------------------------
    PWM 操作在定频时钟100MHz, 写 Period 单位为 ns

    DF9GMS 360度 PWM Duty
    ------------------------------------------
    0.4ms - 1.4ms  顺时针减速
    1.5ms          停止
    1.6ms - 3ms    逆时针加速
*/

static int PWM_PIN = 4; // PWM5@GP4

int main()
{
    long i;

    // Duo:     milkv_duo
    // Duo256M: milkv_duo256m
    // DuoS:    milkv_duos
    if(wiringXSetup("milkv_duo", NULL) == -1) {
        wiringXGC();
        return -1;
    }

    wiringXPWMSetPeriod(PWM_PIN, 20000000);  // 20ms
    wiringXPWMSetDuty(PWM_PIN, 1500000);     // 1.5ms stop
    wiringXPWMSetPolarity(PWM_PIN, 0);       // 0-normal, 1-inversed
    wiringXPWMEnable(PWM_PIN, 1);            // 1-enable, 0-disable

    delayMicroseconds(1000000); // 1s

    for (i = 10000; i< 3000000; i += 10000) // 10 us 步进
    {
        wiringXPWMSetDuty(PWM_PIN, i);
        printf("Duty: %ld\n", i);
        delayMicroseconds(50000); // 50ms
    }

    wiringXPWMSetDuty(PWM_PIN, 1500000);    // 1.5ms stop

    return 0;
}
