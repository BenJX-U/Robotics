/*
 * press any of the 3 endstop switches between the 5 modes
 * 1. led off
 * 2. blinking at 1s
 * 3. blinking at 0.5s
 * 4. blinking at 0.1s
 * 5. led on
 * 
 * the problem is that it triggers a watchdog for multithreading, which I tried fixing but failed
 */

#define led 2
#include <Wire.h>
#include <pthread.h>
#define SDA 19
#define SCL 18
#define I2C 0x23

int ledmode = LOW;
int unsigned state = 0;

void slave_write(byte adress, byte dat){
  Wire.beginTransmission(adress);
  Wire.write(dat);
  Wire.endTransmission();
}

uint8_t slave_read(int adress){
  uint8_t dat;
  Wire.requestFrom(adress, 1);
  if (Wire.available())
  {
    dat = Wire.read();
  }
  return dat;
}


void * swcheck(void * arg){
  while (1){
    uint8_t dat = slave_read(I2C);
    if (bitRead(dat, 7) == 0 || bitRead(dat, 6) == 0 || bitRead(dat, 5) == 0)
    {
      if (state == 4)
      {
        state = 0;
        delay(500);
      }
      else if (state < 4)
      {
        state ++;
        delay(500);
      }
    }
  }
  return NULL;
}

void * ledop(void * arg){
  while (1){
    digitalWrite(led, ledmode);
    switch (state)
    {
      case 0:
        ledmode = LOW;
        break;
      case 1:
        ledmode = (ledmode == HIGH) ? LOW: HIGH;
        delay(1000);
        break;
      case 2:
        ledmode = (ledmode == HIGH) ? LOW: HIGH;
        delay(500);
        break;
      case 3:
        ledmode = (ledmode == HIGH) ? LOW: HIGH;
        delay(100);
        break;
      case 4:
        ledmode = HIGH;
        break;
    }
  }
  return NULL;
}

void setup() {
  pinMode(led, OUTPUT);
  Wire.begin(SDA, SCL);
  
  slave_write(I2C, 0xff);
  pthread_t thread_1;
  pthread_t thread_2; 
  pthread_create(&thread_1, NULL, swcheck, NULL);
  pthread_create(&thread_2, NULL, ledop, NULL);
}

void loop() {
}
