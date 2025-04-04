// See SetupX_Template.h for all options available
#define USER_SETUP_ID 42

#define ST7789_2_DRIVER 

//#define TFT_MISO 7  //Originally 19 (leave TFT SDO disconnected if other SPI devices share MISO)
#define TFT_MOSI 11  //Originally 23
#define TFT_SCLK 12  //Originally 18
#define TFT_CS   10  // Chip select control pin
#define TFT_DC    14  // Data Command control pin
#define TFT_BL    6  //Display backlight
#define TFT_RST   5  // Reset pin

// Optional touch screen chip select
//#define TOUCH_CS 5 // Chip select pin (T_CS) of touch screen

#define LOAD_GLCD    // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2   // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4   // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6   // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7   // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8   // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF   // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT

//IMPORTANT TO USE HSPI PORT
#define USE_HSPI_PORT 

//Try RGB color order
#define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue

// For ST7789, ST7735, ILI9163 and GC9A01 ONLY, define the pixel width and height in portrait orientation
#define TFT_WIDTH  240 // ST7789 240 x 240 and 240 x 320
#define TFT_HEIGHT 280

// TFT SPI clock frequency
//Trying to use lower SPI frequency, was 40000000 originally.
 #define SPI_FREQUENCY  20000000
// #define SPI_FREQUENCY  27000000
//#define SPI_FREQUENCY  40000000
// #define SPI_FREQUENCY  80000000

// Optional reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY  16000000

// SPI clock frequency for touch controller
#define SPI_TOUCH_FREQUENCY  2500000

