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

#define DATA_PIN    13
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    20
//CRGBArray <NUM_LEDS> leds;
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          100
#define FRAMES_PER_SECOND  120

int glitters = 1;

void setup() {
  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { /*cristmassTree,*/ rainbow, rainbowWithGlitter, /* confetti , sinelon, juggle, bpm*/ };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();
  setTreeBranch();
  // send the 'leds' array out to the actual LED strip
  //EVERY_N_MILLISECONDS( 100 ) {
    //fill_solid(leds, 2, CRGB::White);
  //}
  //fill_solid(leds, 3, CRGB::White);
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;   // slowly cycle the "base color" through the rainbow
  }
  EVERY_N_SECONDS( 30 ) {
    nextPattern();  // change patterns periodically
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow(leds, NUM_LEDS, gHue, 7);
  //leds(NUM_LEDS - 9, NUM_LEDS/2) = leds(8, NUM_LEDS / 2);
}

void rainbowWithGlitter()
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(20);
}

void cristmassTree() {
  for ( int i = 7; i < NUM_LEDS - 8; i++ ) {
    leds[i] = CRGB::DarkGreen;
    leds[NUM_LEDS - i] = CRGB::DarkGreen;
  }
  addGlitter(20);
}

void setTreeBranch()
{
  return;
  //leds(0,8) = leds(NUM_LEDS - 9 , NUM_LEDS - 1] = CRGB::Brown;
  for ( int i = 0; i < 8; i++ ) {
    leds[i] = leds[NUM_LEDS - i - 1] = CRGB::Brown;
  }
  leds[NUM_LEDS - 1] = CRGB::Brown;
}

void addGlitter( fract8 chanceOfGlitter)
{
  if ( random8() < chanceOfGlitter) { //chanceOfGlitter) {
    for (int i = 0; i < glitters; i ++) {
      leds[ random16(NUM_LEDS - 16) + 7 ] += CRGB::White;
    }
    //glitters = (glitters % NUM_LEDS) + 1;
  }
}

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  //fadeToBlackBy( leds, NUM_LEDS, 5);
  CRGB gr = CRGB(CRGB::DarkGreen);
  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i].lerp8(gr, 10);
  }
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(13, 0, NUM_LEDS);
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for ( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    leds[beatsin16(i + 7, 0, NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

