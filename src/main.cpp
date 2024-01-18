#include <Arduino.h>
#include <Adafruit_NeoPixel.h> 
#include <stdlib.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Define terminal baud rate
#define TERMBAUD 115200

// Define RGB Data PIN
#define DATA_PIN 48

// Define delay
#define DELAYVAL 1500

// Define RGB LED
#define NUM_COLORS 4

// Board RGB LED
#define BUILTIN_RGB_LED 0
#define RGB_LED 1

Adafruit_NeoPixel pixels(RGB_LED, DATA_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.printf("Setup device\n");
  Serial.printf("Setting Terminal Baud at: %d", TERMBAUD);
  Serial.begin(TERMBAUD);
  Serial.printf("CPU FRQ MHz %d\n", getCpuFrequencyMhz());
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  Serial.printf("Setting LED chip \n");
  pixels.begin();
}

void loop() {
  for(int i=0; i<NUM_COLORS; i++) {
    switch (i) {
      case (0):
      // RED
        pixels.clear();
        delay(DELAYVAL);
        Serial.printf("RED rgb LED, %d\n", i);
        pixels.setPixelColor(BUILTIN_RGB_LED, pixels.Color(150, 0, 0));
        break;
      case (1):
      // GREEN
        pixels.clear();
        delay(DELAYVAL);
        Serial.printf("GREEN rgb LED %d\n", i);
        pixels.setPixelColor(BUILTIN_RGB_LED, pixels.Color(0, 150, 0));
        break;
      case (2):
      // BLUE
        pixels.clear();
        delay(DELAYVAL);
        Serial.printf("BLUE rgb LED %d\n", i);
        pixels.setPixelColor(BUILTIN_RGB_LED, pixels.Color(0, 0, 150));
        break;
      default:
        pixels.clear();
        delay(DELAYVAL);
        Serial.printf("WHITE rgb LED %d\n", i);
        pixels.setPixelColor(BUILTIN_RGB_LED, pixels.Color(150, 150, 150));
        break;
    }
    pixels.show();
    delay(DELAYVAL);
  }
//  while(1);
 }

