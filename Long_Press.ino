/*
 * press once to turn on/off the led
 * long press to activate or deactivate blinking mode
 */

#define led 2
#define sw 9
int normalt = 1;
int ledmode = LOW;
int store = LOW;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sw, INPUT);

}

void loop() {
  int longt = 1;
  int start1 = millis();
  while (millis() - start1 < 2000) 
  {
    if (digitalRead(sw) == HIGH)
    {
      longt = 0;
      break;
    }
  }
  // into long pressed mode
  if (longt == 1)
  {
    // when pressing after 2.5, starts flashing, still pressing
    while (digitalRead(sw) == LOW)
    {
      ledmode = (ledmode == HIGH) ? LOW: HIGH;
      digitalWrite(led, ledmode);
      delay(125);
    }
    // when stop pressing, but still in longpress mode
    while (digitalRead(sw) == HIGH)
    {
      // keeps flashing
      ledmode = (ledmode == HIGH) ? LOW: HIGH;
      digitalWrite(led, ledmode);
      delay(125);
      if (digitalRead(sw) == LOW)
      {
        normalt = 1;
        int start2 = millis();
        while (millis() - start2 < 2000)
        {
          // if pressing not long enough
          if (digitalRead(sw) == HIGH)
          {
            normalt = 0;
            break;
          }
          // still flashing while pending
          ledmode = (ledmode == HIGH) ? LOW: HIGH;
          digitalWrite(led, ledmode);
          delay(125);
        }
        // if been pressing for 2.5 sec, exit longpress mode
        if (normalt == 1)
        {
          while (digitalRead(sw) == LOW)
          {
            digitalWrite(led, store);
          }
          break;
        }
      }
    }
  }
  delay(10);
  if (digitalRead(sw) == LOW)
  {
    delay(10);  
    int contshort = 0;
    int start3 = millis();
    while (millis() - start3 < 1000)
    {
      if (digitalRead(sw) == HIGH)
      {
        contshort = 1 ;
        break;
      }
    }
    if (contshort == 1)
    {
      store = (store == HIGH) ? LOW: HIGH;
      digitalWrite(led, store); 
    }
  }
}
