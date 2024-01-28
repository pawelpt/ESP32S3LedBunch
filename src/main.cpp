#include <Arduino.h>
#include <Adafruit_NeoPixel.h> 
#include <stdlib.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Debug, see in platformio.ini

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

void rgbOff() {
  pixels.clear();
  pixels.setPixelColor(BUILTIN_RGB_LED, pixels.Color(0, 0, 0));
  pixels.show();
  pixels.clear();
}

void show_rgb () {
  for(int i=0; i<NUM_COLORS; i++) {
    switch (i) {
      case (0):
      // RED
        delay(DELAYVAL);
#ifdef DEBUG
        Serial.printf("RED rgb LED, %d\n", i);
#endif
        pixels.setPixelColor(BUILTIN_RGB_LED, pixels.Color(150, 0, 0));
        break;
      case (1):
      // GREEN
        delay(DELAYVAL);
#ifdef DEBUG
        Serial.printf("GREEN rgb LED %d\n", i);
#endif
        pixels.setPixelColor(BUILTIN_RGB_LED, pixels.Color(0, 150, 0));
        break;
      case (2):
      // BLUE
        delay(DELAYVAL);
#ifdef DEBUG
        Serial.printf("BLUE rgb LED %d\n", i);
#endif
        pixels.setPixelColor(BUILTIN_RGB_LED, pixels.Color(0, 0, 150));
        break;
      default:
      // WHITE
        delay(DELAYVAL);
#ifdef DEBUG
        Serial.printf("WHITE rgb LED %d\n", i);
#endif
        pixels.setPixelColor(BUILTIN_RGB_LED, pixels.Color(15, 15, 15));
        break;
    }
    pixels.show();
    delay(DELAYVAL);
    pixels.clear();
  }
}

void rainbow() {
  int mydelay = 25;
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<pixels.numPixels(); i++) { 
      int pixelHue = firstPixelHue + ((i * 65536L) / pixels.numPixels());
      pixels.setPixelColor(BUILTIN_RGB_LED, pixels.gamma32(pixels.ColorHSV(pixelHue)));
#ifdef DEBUG
      Serial.printf("PixelHue %d, GAMMA: %d, firstPixelHue: %d, numpixels %d\n", pixelHue, pixels.gamma32(pixels.ColorHSV(pixelHue)), firstPixelHue, pixels.numPixels());
#endif
      pixels.show();
    }
    delay(mydelay);
  }
}

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
#ifdef DEBUG
  Serial.printf("Start RGB switch\n");
#endif
  show_rgb();
#ifdef DEBUG
  Serial.printf("RGB mode OFF\n");
#endif
  rgbOff();
  delay(DELAYVAL);
  delay(DELAYVAL);
#ifdef DEBUG
  Serial.printf("Start RGB Rainbow %d\n", pixels.numPixels());
#endif
  rainbow();
#ifdef DEBUG
  Serial.printf("RGB mode OFF\n");
#endif
  rgbOff();
  while(1);
 }

