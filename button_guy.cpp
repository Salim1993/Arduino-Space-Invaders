//I wanna be the button guy!

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>

// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.
#define SD_CS    5  // Chip select line for SD card
#define TFT_CS   6  // Chip select line for TFT display
#define TFT_DC   7  // Data/command line for TFT
#define TFT_RST  8  // Reset line for TFT (or connect to +5V)
#define VERT 0 //analog vertical port
#define HOR 1  //analog horizontal port
#define BUTTON 9 //button port

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


int16_t OFFSET_H( int16_t joystick_h, int16_t horizontal_pos, int16_t original_h);

void setup(void) {

  pinMode(BUTTON,INPUT);
  digitalWrite(BUTTON,HIGH);

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);

  int16_t OFFSET = 30;
  int16_t hOld = 0;
  int16_t vOld = 0;
  int16_t original_v = analogRead(VERT);
  int16_t original_h = analogRead(HOR);
  int16_t v = 143;
  int16_t h = 64;

  while (1){
    //  v = OFFSET_V(analogRead(VERT), v, original_v);
    h = OFFSET_H(analogRead(HOR), h, original_h);

    if(hOld != h){
      for(int y = -1; y < 2; y++){
	for(int x = -2; x < 4; x++){
	  //Erase dot at old cursor postion

	  tft.drawPixel(hOld+x, vOld+y, ST7735_BLACK);
	}
      }
      delay(10);
    }

    for(int y = -1; y < 2; y++){
      for(int x = -2; x < 4; x++){

	//Draw dot a new cursor postion

	tft.drawPixel(h+x,v+y,ST7735_WHITE);
      }
    }

    if (digitalRead(BUTTON) == LOW){
      Serial.begin(9600);
      Serial.print("OK");
      int blah = -2;
      int bullet = v;

	//Draw dot a new cursor postion
      for(int blah = -2; bullet + blah > -2; blah--){

	tft.drawPixel(h, bullet + blah + 1, ST7735_BLACK);
	tft.drawPixel(h, bullet + blah, ST7735_WHITE); 
	tft.drawPixel(h, bullet + blah-1, ST7735_WHITE); 
	tft.drawPixel(h, bullet + blah-2, ST7735_WHITE); 
      }     
    }

    //Update the cursor position

    vOld = v;
    hOld = h;
  }
}

void loop() {
}

int16_t OFFSET_H(int16_t joystick_h, int16_t h, int16_t original_h){

  if (joystick_h > (30 + original_h)){

    h = h + 1;
  }

  if (joystick_h < (original_h - 30)){

    h = h - 1;
  }
  if (h <0){

    h = 0;
  }
  if (h > 127){

    h = 127;
  }
      
  return h;
}
