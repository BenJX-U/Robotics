#define ONBOARD_LED 2

void setup() {
   Serial.begin(115200); 
   pinMode(ONBOARD_LED, OUTPUT);
   delay(1000);
   Serial.print("\nEnter a blinking rate:");
}

void loop() {
   if(Serial.available() > 0) { 
      String rate_read = Serial.readString();
      float rate = rate_read.toFloat(); 
      Serial.print("\nThe rate is ");
      Serial.println(rate);
      Serial.print("Press restart to enter a new rate.");
      while (1 == 1) {
        digitalWrite(ONBOARD_LED, HIGH);
        delay(rate);
        digitalWrite(ONBOARD_LED, LOW);
        delay(rate);
      }
   }
}

// rate = 15, continious with glicthes (human eyes, phone cam, phone vid)
// rate = 10, continious (human eyes), continious with glicthes (phone cam, phone vid)
// rate = 7.5, continious (human eyes, phone vid 30fps), continious with glicthes (phone cam, phone vid 60fps)
// rate = 5, continious (human eyes, phone cam, phone vid 30fps), continious with glicthes (phone vid 60fps)
// rate = 1, continious (human eyes, phone cam, phone vid)
