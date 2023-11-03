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

    if(wiringXSetup("duo", NULL) == -1) {
        wiringXGC();
        return -1;
    }

    wiringXSetPWMPeriod(PWM_PIN, 20000000);  // 20ms
    wiringXSetPWMDuty(PWM_PIN, 1500000);     // 1.5ms stop
    wiringXSetPWMPolarity(PWM_PIN, 0);       // 0-normal, 1-inversed
    wiringXPWMEnable(PWM_PIN, 1);            // 1-enable, 0-disable

    delayMicroseconds(1000000); // 1s

    for (i = 10000; i< 3000000; i += 10000) // 10 us 步进
    {
        wiringXSetPWMDuty(PWM_PIN, i);
        printf("Duty: %ld\n", i);
        delayMicroseconds(50000); // 50ms
    }

    wiringXSetPWMDuty(PWM_PIN, 1500000);    // 1.5ms stop

    return 0;
}
