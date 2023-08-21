// --------------WT32-SC01 setup start--------------
#define USER_SETUP_LOADED

#define ST7796_DRIVER

#define TFT_WIDTH  480
#define TFT_HEIGHT 320

#define TFT_BACKLIGHT_ON HIGH

#define USE_HSPI_PORT

#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC   21
#define TFT_RST  22
#define TFT_BL   23


#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT

// SPI frequency for TFT writes
#define SPI_FREQUENCY  27000000

// Optional reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY  20000000

// --------------WT32-SC01 setup end--------------
#include <TFT_eSPI.h>
#include <SPI.h>

#include "FT6336U.h"

#define TOUCH_I2C_SDA 18
#define TOUCH_I2C_SCL 19
#define TOUCH_RST_PIN -1
#define TOUCH_INT_PIN -1

Touch ctp = Touch(TFT_HEIGHT, TFT_WIDTH, TOUCH_I2C_SDA, TOUCH_I2C_SCL, TOUCH_RST_PIN, TOUCH_INT_PIN);

#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

TFT_eSPI tft = TFT_eSPI();

void setup(){
    Serial.begin(115200);
    ctp.begin();
    tft.init();
	  tft.setRotation(1);

	  tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, TFT_RED);
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, TFT_YELLOW);
    tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, TFT_GREEN);
    tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, TFT_CYAN);
    tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, TFT_BLUE);
    tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, TFT_MAGENTA);
    tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
    
    // select the current color 'red'
    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
    currentcolor = TFT_RED;
}

void loop(){
    if(!ctp.touched()){
        return;
    }
    TS_Point p = ctp.getPoint();
  
    // Adjust the touch screen values to match the tft lcd.
    p.rotation();
    p.flipY();
    
    if(p.y < BOXSIZE){
        oldcolor = currentcolor;

        if(p.x < BOXSIZE){ 
            currentcolor = TFT_RED; 
            tft.drawRect(0, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
        } else if(p.x < BOXSIZE*2){
            currentcolor = TFT_YELLOW;
            tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
        } else if(p.x < BOXSIZE*3){
            currentcolor = TFT_GREEN;
            tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
        } else if(p.x < BOXSIZE*4){
            currentcolor = TFT_CYAN;
            tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
        } else if(p.x < BOXSIZE*5){
            currentcolor = TFT_BLUE;
            tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
        } else if(p.x <= BOXSIZE*6){
            currentcolor = TFT_MAGENTA;
            tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
        } else if(p.x <= BOXSIZE*7){
            currentcolor = TFT_WHITE;
            tft.drawRect(BOXSIZE*7, 0, BOXSIZE, BOXSIZE, TFT_CYAN);
        }

        if(oldcolor != currentcolor){
            if(oldcolor == TFT_RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, TFT_RED);
            if(oldcolor == TFT_YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, TFT_YELLOW);
            if(oldcolor == TFT_GREEN) tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, TFT_GREEN);
            if(oldcolor == TFT_CYAN) tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, TFT_CYAN);
            if(oldcolor == TFT_BLUE) tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, TFT_BLUE);
            if(oldcolor == TFT_MAGENTA) tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, TFT_MAGENTA);
            if(oldcolor == TFT_WHITE) tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, TFT_WHITE);
        }
    }
    if(((p.y-PENRADIUS) > BOXSIZE) && ((p.y+PENRADIUS) < tft.height())){
        tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
    }
}
