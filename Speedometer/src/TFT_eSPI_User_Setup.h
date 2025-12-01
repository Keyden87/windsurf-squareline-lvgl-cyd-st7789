// TFT_eSPI User Configuration for CYD 2432S204R
// This file overrides the default settings in TFT_eSPI/User_Setup_Select.h

#define USER_SETUP_LOADED

// Display driver
#define ST7789_DRIVER

// Display dimensions
#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// CYD 2432S204R Pinout (adjust if different)
#define TFT_CS   15  // Chip select
#define TFT_DC   2   // Data/Command
#define TFT_RST  -1  // Set to -1 if not connected

// Backlight control
#define TFT_BL   27  // Backlight control pin
#define TFT_BACKLIGHT_ON HIGH  // Backlight active high

// SPI Configuration
#define SPI_FREQUENCY  40000000  // 40MHz - reduce if you see noise
// #define SPI_FREQUENCY  20000000  // Try this if 40MHz is too fast

// Optional: Reduce SPI frequency during transfers to improve stability
// #define SPI_READ_FREQUENCY 20000000
// #define SPI_TOUCH_FREQUENCY 2500000

// TFT SPI Mode (try different modes if you see noise)
#define TFT_SPI_MODE SPI_MODE0

// Optional: Try uncommenting these if you see noise
// #define TFT_MOSI 23
// #define TFT_MISO 19
// #define TFT_SCLK 18

// Optional: Try uncommenting if you see noise
// #define SPI_BUSY_CHECK

// Touch controller (XPT2046)
#define TOUCH_CS 5     // Touch chip select
#define TOUCH_IRQ 36   // Optional, set to -1 if not used

// Optional: Add a small delay after CS goes low to improve stability
// #define TFT_CS_LOW_DELAY 1

// Optional: Reduce flicker during updates
// #define SUPPORT_TRANSACTIONS
// #define TFT_INVERSION_OFF

// Optional: If colors are inverted, uncomment this
// #define TFT_INVERSION_ON

// Optional: If your display has a BGR color filter (if colors look wrong)
// #define TFT_RGB_ORDER TFT_BGR

// Optional: If your display has a mirror or flip issue
// #define TFT_MIRROR_X
// #define TFT_MIRROR_Y
// #define TFT_INVERT_ROTATION

// Optional: If you need to swap the X and Y coordinates
// #define TFT_SWAP_XY

// Optional: If your touch coordinates are swapped or flipped
// #define TOUCH_SWAP_XY
// #define TOUCH_INVERT_X
// #define TOUCH_INVERT_Y

// Optional: Touch calibration values (you'll need to determine these)
// #define XPT2046_X_CALIBRATION  -3611
// #define XPT2046_Y_CALIBRATION  -360
// #define XPT2046_X_OFFSET       250
// #define XPT2046_Y_OFFSET       360
