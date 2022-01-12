/*
 * press to switch between the 5 modes
 * 1. led off
 * 2. blinking at 1s
 * 3. blinking at 0.5s
 * 4. blinking at 0.1s
 * 5. led on
 */

#define led 2
#define sw 9
#include <pthread.h>

int ledmode = LOW;
int unsigned state = 0;

void * swcheck(void * arg){
  while (1){
    if (digitalRead(sw) == LOW && state != 4)
    {
      state ++;
      delay(250);
    }
    else if (digitalRead(sw) == LOW && state == 4)
    {
      state = 0;
      delay(250);
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
  pinMode(sw, INPUT);
  pthread_t thread_1;
  pthread_t thread_2; 
  pthread_create(&thread_1, NULL, swcheck, NULL);
  pthread_create(&thread_2, NULL, ledop, NULL);
}

void loop() {
}
