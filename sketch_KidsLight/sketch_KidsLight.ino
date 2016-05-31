#include <FastLED.h>

#define LED_PIN     13
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    150

#define BRIGHTNESS  30
#define FRAMES_PER_SECOND 3

CRGB leds[NUM_LEDS];

// 0..149
//
//    1                    43 
//145 +++++++++++++++++++++++ 44
//    +        42           +
//    + 30               27 +
//    +                     +
//    +        42           +
//115 +++++++++++++++++++++++ 71
//    114                  72
#define LINE_NUM_LEDS 44

byte llPair[LINE_NUM_LEDS][2]; //line to led Pair

void setupllPair() {
   llPair[0][0] = 115;
   llPair[0][1] = 145;
   llPair[LINE_NUM_LEDS-1][0] = 44;
   llPair[LINE_NUM_LEDS-1][1] = 71;
   for(int i=1; i<LINE_NUM_LEDS-1; i++) {
      llPair[i][0] = 114 - (i-1); 
      llPair[i][1] = i; 
   }
}

void setLedByllPair(int x, CRGB c) {
   if(llPair[x][0] < llPair[x][1]) {
      for(int i=llPair[x][0]; i <= llPair[x][1]; i++) {
        leds[i] = c;
      }
   } else {
      leds[llPair[x][0]] = c;
      leds[llPair[x][1]] = c;
   } 
}

void setLedFromCorner(int x, CRGB c) {
//    if(x == 0) {
//       leds[ llPair[0][0] ] = c;
//       leds[ llPair[0][1] ] = c;
//       leds[ llPair[LINE_NUM_LEDS][0] ] = c;
//       leds[ llPair[LINE_NUM_LEDS][1] ] = c;
//    } else {
       int offset = x;
       leds[ 1 + offset ] = c;
       leds[ llPair[0][1] - offset ] = c;
       leds[ llPair[0][0] + offset ] = c;
       leds[ llPair[0][0] - offset ] = c;
       
       leds[ llPair[LINE_NUM_LEDS-1][0] + offset ] = c;
       leds[ llPair[LINE_NUM_LEDS-1][0] - offset ] = c;
       leds[ llPair[LINE_NUM_LEDS-1][1] - offset ] = c;
       leds[ llPair[LINE_NUM_LEDS-1][1] + offset ] = c;
//    }    
}

// Fire2012 with programmable Color Palette
//
// This code is the same fire simulation as the original "Fire2012",
// but each heat cell's temperature is translated to color through a FastLED
// programmable color palette, instead of through the "HeatColor(...)" function.
//
// Four different static color palettes are provided here, plus one dynamic one.
// 
// The three static ones are: 
//   1. the FastLED built-in HeatColors_p -- this is the default, and it looks
//      pretty much exactly like the original Fire2012.
//
//  To use any of the other palettes below, just "uncomment" the corresponding code.
//
//   2. a gradient from black to red to yellow to white, which is
//      visually similar to the HeatColors_p, and helps to illustrate
//      what the 'heat colors' palette is actually doing,
//   3. a similar gradient, but in blue colors rather than red ones,
//      i.e. from black to blue to aqua to white, which results in
//      an "icy blue" fire effect,
//   4. a simplified three-step gradient, from black to red to white, just to show
//      that these gradients need not have four components; two or
//      three are possible, too, even if they don't look quite as nice for fire.
//
// The dynamic palette shows how you can change the basic 'hue' of the
// color palette every time through the loop, producing "rainbow fire".

CRGBPalette16 gPal;

// Keypad key matrix:
const byte rows = 4; 
const byte cols = 3; 
char keys[rows][cols] = 
{
   {'1','2','3'},
   {'4','5','6'},
   {'7','8','9'},
   {'*','0','#'}
};
 
// Keypad pin definitions
byte rowPins[rows] = {2, 3, 4, 5}; 
byte colPins[cols] = {6, 7, 8};  
 
// Instantiate the keypad
//Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  // This first palette is the basic 'black body radiation' colors,
  // which run from black to red to bright yellow to white.
  gPal = HeatColors_p;
  
  // These are other ways to set up the color palette for the 'fire'.
  // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
  
  // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);
  
  // Third, here's a simpler, three-step gradient, from black to red to white
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);
  
  setupllPair();

}

void loop()
{
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy( random());

  // Fourth, the most sophisticated: this one sets up a new palette every
  // time through the loop, based on a hue that changes every time.
  // The palette is a gradient from black, to a dark color based on the hue,
  // to a light color based on the hue, to white.
  //
  //   static uint8_t hue = 0;
  //   hue++;
  //   CRGB darkcolor  = CHSV(hue,255,192); // pure hue, three-quarters brightness
  //   CRGB lightcolor = CHSV(hue,128,255); // half 'whitened', full brightness
  //   gPal = CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);


  //Fire2012WithPalette(); // run simulation frame, using palette colors
  for (int i = 0; i < NUM_LEDS; i++ ) {
    leds[i].r = 255; leds[i].g = 147; leds[i].b = 41;
  }
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}


// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
//// 
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation, 
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking. 
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100 
#define COOLING  80

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 150

#define HEAT_SIZE 15
void Fire2012WithPalette()
{
// Array of temperature readings at each simulation cell
  static byte heat[HEAT_SIZE];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < HEAT_SIZE; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / HEAT_SIZE) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= HEAT_SIZE - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < HEAT_SIZE; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 240);
      setLedFromCorner(j, ColorFromPalette( gPal, colorindex));
    }
}

