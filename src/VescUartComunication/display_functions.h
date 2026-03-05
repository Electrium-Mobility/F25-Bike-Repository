#pragma once

#define LCD_LED 27 // led pin definition
#define MAX_IMAGE_WIDTH 238 // maximum width for Electrium Logo
#define WIDTH 238 // constant width value used for some image drawing, couldve done better here lol
#define HEIGHT 30 // constant height value used for same

TFT_eSPI tft = TFT_eSPI();

// Constants pertaining to value display values. 
// Very messy, I'd recommend being more organized with these kinds of things
int16_t xpos = 42;
int16_t ypos = 70;
int16_t textxpos = 140;
int16_t textypos = 130;
int16_t batteryxpos = textxpos - 25;
int16_t batteryypos = textypos + 78;

// Function that draws image at position x and y
// through an array of hex values in progmem, defined by the image value
void drawImageFromProgmem(int x, int y, int width, int height, const uint16_t* image);

// Updating inpVoltage on screen only if a change is registered
void update_inpVoltage();

// Updating battery % on screen only if a change is registered
void update_battery();

// Updating ERPM only if a change is registered
// IMPORTANT: ERPM only tracks motor rotations, not genuine RPM. implementing 
// other accurate detection like a hall sensor would be important to calculating genuine rpm.
void update_erpm();