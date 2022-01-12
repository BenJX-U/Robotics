#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define I2C_SDA 19
#define I2C_SCL 18
#define PEXP_I2CADDR 0x23
#define OLED_I2CAADR 0x3C
#define NEO_PIXEL 5

uint8_t expanderData;

Adafruit_NeoPixel strip(3, NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void IOexpanderWrite(byte address, byte _data) {
    Wire.beginTransmission(address);
    Wire.write(_data);
    Wire.endTransmission(); 
}

uint8_t IOexpanderRead(int address) {
    uint8_t _data;
    Wire.requestFrom(address, 1);
    if(Wire.available()) {
        _data = Wire.read();
    }
    return _data;
}

void setup() {
    Wire.begin(I2C_SDA, I2C_SCL);
    IOexpanderWrite(PEXP_I2CADDR, 0xff);
    strip.begin();           
    strip.show();            
    strip.setBrightness(15); 
}

void loop() {
    expanderData = IOexpanderRead(PEXP_I2CADDR);
    strip.setPixelColor(0, strip.Color((bitRead(expanderData, 5) == 0) ? 255 : 0, 0, 0));
    strip.setPixelColor(1, strip.Color(0, (bitRead(expanderData, 6) == 0) ? 255 : 0, 0));
    strip.setPixelColor(2, strip.Color(0, 0, (bitRead(expanderData, 7) == 0) ? 255 : 0));
    strip.show(); 
    delay(5);
}
