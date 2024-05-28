// Ref: https://github.com/technion/lol_dht22/blob/master/dht22.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <wiringx.h>

#define MAXTIMINGS 85
#define DHTTYPE 22

static int DHTPIN = 16;
static int dht22_dat[5] = {0, 0, 0, 0, 0};

static uint8_t sizecvt(const int read) {
    /* digitalRead() and friends from wiringpi are defined as returning a value
    < 256. However, they are returned as int() types. This is a safety function */

    if (read > 255 || read < 0) {
        printf("Invalid data from wiringPi library\n");
        exit(EXIT_FAILURE);
    }
    return (uint8_t)read;
}

static int read_dht22_dat() {
    uint8_t laststate = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;

    dht22_dat[0] = dht22_dat[1] = dht22_dat[2] = dht22_dat[3] = dht22_dat[4] = 0;

    // pull pin down for 18 milliseconds
    pinMode(DHTPIN, PINMODE_OUTPUT);
    digitalWrite(DHTPIN, HIGH);
    // delay(500);
    delayMicroseconds(500000);
    digitalWrite(DHTPIN, LOW);
    // delay(20);
    delayMicroseconds(20000);
    // prepare to read the pin
    pinMode(DHTPIN, PINMODE_INPUT);

    // detect change and read data
    for (i = 0; i < MAXTIMINGS; i++) {
        counter = 0;
        while (sizecvt(digitalRead(DHTPIN)) == laststate) {
            counter++;
            delayMicroseconds(2);
            if (counter == 255) {
                break;
            }
        }
        laststate = sizecvt(digitalRead(DHTPIN));

        if (counter == 255)
            break;

        // ignore first 3 transitions
        if ((i >= 4) && (i % 2 == 0)) {
            // shove each bit into the storage bytes
            dht22_dat[j / 8] <<= 1;
            if (counter > 16)
                dht22_dat[j / 8] |= 1;
            j++;
        }
    }

    // check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
    // print it out if data is good
    if(DHTTYPE == 11){
        if ((j >= 40) && (dht22_dat[4] == ((dht22_dat[0] + dht22_dat[1] + dht22_dat[2] + dht22_dat[3]) & 0xFF))) {
            float t, h;
            h = (float)dht22_dat[0];
            t = (float)dht22_dat[2];
            if ((dht22_dat[3] & 0x80) != 0){
                t = -(float)(dht22_dat[3] & 0x7F);
            }
            printf("Humidity = %.2f %% Temperature = %.2f *C \n", h, t);
            return 1;
        } else {
            printf("Data not good, skip\n");
            return 0;
        }
    }
    else if (DHTTYPE == 22){
        if ((j >= 40) && (dht22_dat[4] == ((dht22_dat[0] + dht22_dat[1] + dht22_dat[2] + dht22_dat[3]) & 0xFF))) {
            float t, h;
            h = (float)dht22_dat[0] * 256 + (float)dht22_dat[1];
            h /= 10;
            t = (float)(dht22_dat[2] & 0x7F) * 256 + (float)dht22_dat[3];
            t /= 10.0;
            if ((dht22_dat[2] & 0x80) != 0)
                t *= -1;

            printf("Humidity = %.2f %% Temperature = %.2f *C \n", h, t);
            return 1;
        } else {
            printf("Data not good, skip\n");
            return 0;
        }
    } else{
	printf("Wrong DHT type/model. Change in line 11.\n");
	}
}

int main() {
    // Duo:     milkv_duo
    // Duo256M: milkv_duo256m
    // DuoS:    milkv_duos
    if (wiringXSetup("milkv_duo", NULL) == -1) {
        wiringXGC();
        return -1;
    }

    if (wiringXValidGPIO(DHTPIN) != 0) {
        printf("Invalid GPIO %d\n", DHTPIN);
    }

    while (1) {
        read_dht22_dat();
        delayMicroseconds(1500000);
    }

    return 0;
}
