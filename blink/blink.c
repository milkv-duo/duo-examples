#include <stdio.h>
#include <unistd.h>

#include <wiringx.h>

int main() {
    // Duo/Duo256M: LED = 25
    // DuoS:        LED =  0
    int DUO_LED = 25;

    // Duo:     milkv_duo
    // Duo256M: milkv_duo256m
    // DuoS:    milkv_duos
    if(wiringXSetup("milkv_duo", NULL) == -1) {
        wiringXGC();
        return 1;
    }

    if(wiringXValidGPIO(DUO_LED) != 0) {
        printf("Invalid GPIO %d\n", DUO_LED);
    }

    pinMode(DUO_LED, PINMODE_OUTPUT);

    while(1) {
        printf("Duo LED GPIO (wiringX) %d: High\n", DUO_LED);
        digitalWrite(DUO_LED, HIGH);
        sleep(1);
        printf("Duo LED GPIO (wiringX) %d: Low\n", DUO_LED);
        digitalWrite(DUO_LED, LOW);
        sleep(1);
    }

    return 0;
}
