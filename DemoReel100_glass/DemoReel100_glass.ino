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

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

  
#define DATA_PIN_T   15
#define DATA_PIN_B   14
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS_T    24
#define NUM_LEDS_B    16

CRGB leds_t[NUM_LEDS_T];
CRGB leds_b[NUM_LEDS_B];

#define BRIGHTNESS          10
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN_T,COLOR_ORDER>(leds_t, NUM_LEDS_T).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,DATA_PIN_B,COLOR_ORDER>(leds_b, NUM_LEDS_B).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { /*police, rainbow,*/ rainbowWithGlitter, confetti, sinelon/*, juggle, bpm*/ };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint8_t gPolice = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_MILLISECONDS( 70 ) { gPolice = (gPolice + 1) % 30; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 20 ) { nextPattern();  } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  //fadeToBlackBy( leds_t, NUM_LEDS_T, 256);
  //fadeToBlackBy( leds_b, NUM_LEDS_B, 256);
  fill_solid(leds_t, NUM_LEDS_T, CRGB::Black);
  fill_solid(leds_b, NUM_LEDS_B, CRGB::Black);
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds_t, NUM_LEDS_T, gHue, 7);
  fill_rainbow( leds_b, NUM_LEDS_B, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(20);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds_t[ random16(NUM_LEDS_T) ] += CRGB::White;
    leds_b[ random16(NUM_LEDS_B) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds_t, NUM_LEDS_T, 5);
  fadeToBlackBy( leds_b, NUM_LEDS_B, 5);
  int pos = random16(NUM_LEDS_T);
  leds_t[pos] += CHSV( gHue + random8(64), 200, 255);
  pos = random16(NUM_LEDS_B);
  leds_b[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds_t, NUM_LEDS_T, 20);
  fadeToBlackBy( leds_b, NUM_LEDS_B, 20);
  int pos = beatsin16(13,0,NUM_LEDS_T);
  leds_t[pos] += CHSV( gHue, 255, 192);
  if (pos <= NUM_LEDS_B + 6 && pos > 6) leds_b[pos-7] += CHSV( gHue, 255, 192);
}

void police() {
  fill_solid(leds_t, NUM_LEDS_T, CRGB::Black);
  
  if ( gPolice == 4 || gPolice == 5 || gPolice == 8 || gPolice == 9 || gPolice == 20 || gPolice == 22 || gPolice == 24 || gPolice == 26 ) {
    fill_solid(leds_t, NUM_LEDS_T/2, CRGB::Blue);
  }
  if ( gPolice == 6 || gPolice == 7 || gPolice == 10 || gPolice == 11 || gPolice == 20 || gPolice == 22 || gPolice == 24 || gPolice == 26) {
    fill_solid(&(leds_t[NUM_LEDS_T/2]), NUM_LEDS_T/2, CRGB::Blue);
  }
  //fill_solid(&(leds_t[numPix/2]), numPix/2, step ? CRGB::Red : CRGB::Blue);
  //step = (step+1) % 2;
}

//void bpm()
//{
//  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
//  uint8_t BeatsPerMinute = 62;
//  CRGBPalette16 palette = PartyColors_p;
//  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
//  for( int i = 0; i < NUM_LEDS; i++) { //9948
//    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
//  }
//}
//
//void juggle() {
//  // eight colored dots, weaving in and out of sync with each other
//  fadeToBlackBy( leds, NUM_LEDS, 20);
//  byte dothue = 0;
//  for( int i = 0; i < 8; i++) {
//    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
//    dothue += 32;
//  }
//}

