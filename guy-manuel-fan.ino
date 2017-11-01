#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    6
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    24
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void guy_colors(int i){
  //for ( int i = 0; i <= NUM_LEDS; i++) {  
  if ( i <= 2) {
  leds[i] = CRGB(0x800080);   
  }
  else if ( i <= 5 and i > 2) {
  leds[i] = CRGB(0x0000FF);
  }  
  else if ( i <= 8 and i > 5) {
  leds[i] = CRGB(0x87ceeb);
  }
  else if ( i <= 11 and i > 8) {
  leds[i] = CRGB(0x20b2aa);
  }
  else if ( i <= 14 and i > 11) {
  leds[i] = CRGB(0x006400);
  }
  else if ( i <= 17 and i > 14) {
  leds[i] = CRGB(0xffff00);
  }
  else if ( i <= 20 and i > 17) {
  leds[i] = CRGB(0xffa500);
  }
  else if ( i <= 23 and i > 20) {
  leds[i] = CRGB(0xff0000);
  }
}

static int group_by(int i){
   //for ( int i = 0; i <= NUM_LEDS; i++) {  

  int group; 
  if ( i <= 2) {
  group=1;   
  }
  else if ( i <= 5 and i > 2) {
  group=2; 
  }  
  else if ( i <= 8 and i > 5) {
  group=3;
  }
  else if ( i <= 11 and i > 8) {
  group=4;
  }
  else if ( i <= 14 and i > 11) {
  group=5;
  }
  else if ( i <= 17 and i > 14) {
  group=6;
  }
  else if ( i <= 20 and i > 17) {
  group=7;
  }
  else if ( i <= 23 and i > 20) {
  group=8;
  }
  return group;
}



void sinelon()
{
  for ( int i = 0; i <= 10000; i++){
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS,50);
  int pos = beatsin16(32,0,NUM_LEDS);
  guy_colors(pos);
 FastLED.show();
}
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  for (int i = 0; i <= 10000; i++){
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(70);
  delay(20);
  FastLED.show();
  }
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  for (int i = 0; i <= 10000; i++){
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = random16(NUM_LEDS);
  guy_colors(pos);//leds[pos] += CHSV( gHue + random8(64), 200, 255);
   FastLED.show();
}
}



//void stacking()
//{
//int a[] = {2,5,8,11,14,17,20,23};
//int delay_time =100;
//
////fadeToBlackBy( leds, NUM_LEDS,1);
//for (int i = 0; i <= NUM_LEDS-1; i++){
//  guy_colors(i);
//   int y = 0;
//   if ( i == a[y] ){
//     for (int b = NUM_LEDS-1;b !=a[y]; b--){
//     leds[b] = CRGB::Black; 
//     y++;  
//     } 
//}
//FastLED.show();
//delay(delay_time);
//}
//}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 10);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
    FastLED.show();
  }
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}



void guy_rev()
{
int a[] = {2,5,8,11,14,17,20,23};
int delay_time =100;
int y=7;

//loop set pixel colors
for (int i = NUM_LEDS; i > -3; i--)
{
  guy_colors(i);
  if (i == a[y])
  {
    y--;
    FastLED.show();
    delay(delay_time);
    }
    fadeToBlackBy( leds, NUM_LEDS,30);
    FastLED.show();    
  }
}
void guy_fw()
{
int a[] = {2,5,8,11,14,17,20,23};
int delay_time =100;
int y=0;

//loop set pixel colors
for (int i = 0; i <= NUM_LEDS-1; i++)
{
  guy_colors(i);
  if (i == a[y])
  {
    y++;
    FastLED.show();
    delay(delay_time);
    }
    fadeToBlackBy( leds, NUM_LEDS,30);
    FastLED.show();    
  }
}

void fw_rev(){
  for (int i = 0; i <= 20; i++){
  guy_fw();
  guy_rev();
}
}

void loop() {
  // put your main code here, to run repeatedly:
  confetti();
  fw_rev();
  rainbowWithGlitter();
  sinelon();
}
