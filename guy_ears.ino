#include <Adafruit_NeoPixel.h>
#include "FastLED.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define DATA_PIN    6
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    2
CRGB leds[NUM_LEDS];

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  
FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  

  
}

void fadeInAndOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {

  for(uint8_t b=0; b <255; b++) {
     for(uint8_t i=0; i < 1; i++) {
        strip.setPixelColor(i, red*b/255, green*b/255, blue*b/255);
     }
     strip.show();
     delay(wait);
  }

  for(uint8_t b=255; b > 0; b--) {
     for(uint8_t i=0; i < 1; i++) {
        strip.setPixelColor(i, red*b/255, green*b/255, blue*b/255);
     }
     strip.show();
     delay(wait);
  }
  for(uint8_t b=0; b <255; b++) {
     for(uint8_t i=0; i < 2; i++) {
        strip.setPixelColor(1, red*b/255, green*b/255, blue*b/255);
     }
     strip.show();
     delay(wait);
  }

  for(uint8_t b=255; b > 0; b--) {
     for(uint8_t i=0; i < 2; i++) {
        strip.setPixelColor(1, red*b/255, green*b/255, blue*b/255);
     }
     strip.show();
     delay(wait);
  }
}


void ekg(uint8_t wait ){
  for (int i = 0; i < 20; i++){
    fadeInAndOut(255, 0, 0, wait); // Red
  }
 for (int i = 0; i < 20; i++){
    fadeInAndOut(0, 225, 0, wait); // Green
  }
  for (int i = 0; i < 20; i++){
    fadeInAndOut(0, 0, 255, wait); // Blue
  }
   for (int i = 0; i < 20; i++){
    fadeInAndOut(128, 0, 128, wait); // purple
 }
   for (int i = 0; i < 20; i++){
    fadeInAndOut(255, 165, 0, wait); // orange
 }
}


void loop() {
 ekg(1);
}

