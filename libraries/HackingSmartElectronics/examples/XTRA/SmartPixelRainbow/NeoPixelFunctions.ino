// Note: These function come from the NeoPixel example sketches
// available on www.adafruit.com

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<LEDStrip.numPixels(); i++) {
    LEDStrip.setPixelColor(i, c);
    LEDStrip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<LEDStrip.numPixels(); i++) {
      LEDStrip.setPixelColor(i, Wheel((i+j) & 255));
    }
    LEDStrip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< LEDStrip.numPixels(); i++) {
      LEDStrip.setPixelColor(i, Wheel(((i * 256 / LEDStrip.numPixels()) + j) & 255));

    }
    LEDStrip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < LEDStrip.numPixels(); i=i+3) {
        LEDStrip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      LEDStrip.show();

      delay(wait);

      for (int i=0; i < LEDStrip.numPixels(); i=i+3) {
        LEDStrip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < LEDStrip.numPixels(); i=i+3) {
        LEDStrip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      LEDStrip.show();

      delay(wait);

      for (int i=0; i < LEDStrip.numPixels(); i=i+3) {
        LEDStrip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return LEDStrip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return LEDStrip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return LEDStrip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


