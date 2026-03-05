/* This code is for the Electrium F25 EBike display */
/* I probably should check if this can compile after I did code cleanup and created the extra */
/* header and cpp files, but im 90% confident it will function no problemo. Nothing has been changed from what */
/* the display physically shows in bay. */
/* If anybody is viewing this code as an example, I would recommend being more organized with variables, variable names, etc. */
/* Especialy when working with a display and pixel values, having named constants can be very helpful. */
/* It's always great practice to be properly keeping track of variables and having clean, easy to read code. */
/* Personally, at the time of creating this, I was a lot more focused on learning the principles and understanding the */
/* connections, so I wasnt as organized. */

// Include libraries
#include <Arduino.h> // Basic Arduino library, includes math functions

// Used for LCD display functions. TFT_eSPI.h uses SPI.h internally, must include
#include <TFT_eSPI.h> // Pin definitions in user setup file v important!, see README for doccumentation
#include <SPI.h>

#include "VescUart.h"
#include "datatypes.h"

// Files pertaining to custom images displayed on LCD
#include "electrium_logo.h"
#include "battery.h"
#include "vesc_values.h" // contains values to be grabbed by VESC UART library

// Initializing objects
HardwareSerial VescSerial(0); // Define VescSerial to be the Serial0 line
VescUart UART; // Define VescUart 
// TFT_eSPI tft = TFT_eSPI() is called in a seperate header file which initializes screen display

void setup() {

	/* ------------------------------------ INITIALIZATIONS ------------------------------------ */

	//Initialize VESC UART along Serial0 to communicate through RX 22 and TX 21
	VescSerial.begin(115200, SERIAL_8N1, 22, 21);
	delay(200); //short buffer

	// Initialize pinmode for LCD and write high to the backlight
	pinMode(LCD_LED, OUTPUT);
	digitalWrite(LCD_LED, HIGH); // without writing high to backlight, no image!
	
	// Initialize TFT object for LCD display
	tft.init();
	tft.setRotation(2); // set vertical rotation for display 
	tft.fillScreen(TFT_BLACK);
	tft.setCursor(0,0);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(6);
  tft.setTextFont(1);

	/* ------------------------------------ STARTUP SCREEN ------------------------------------ */

	// VERT green lines on either side of creen
	tft.drawLine(0,0,0,480,TFT_GREEN);
	tft.drawLine(319,0,319,480,TFT_GREEN);
 
	// HORIZ green lines on top and bottom of screen
	tft.drawLine(0,0,319,0,TFT_GREEN);
	tft.drawLine(0,479,319,479,TFT_GREEN);

	// Draw electrium mobility logo from progmem (electrium_logo is defined in included header file)
	drawImageFromProgmem(xpos, ypos, WIDTH, HEIGHT, electrium_logo);

	tft.setTextDatum(MC_DATUM);
  tft.drawString("WELCOME", 160, 170);
	tft.setTextSize(2);
  tft.drawString("You are using", 160, 230);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
	tft.drawString("Electrium Mobility's", 160, 250);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("F25 Electric Bike :)", 160, 270);
	tft.setTextSize(1);
	tft.drawString("Building Sustainable, Affordable Transportation", 160, 360);
	delay(3500);

	/* ------------------------------------------------------------------------------------------------ */

	// Wipe startup screen
	tft.fillScreen(TFT_BLACK);

	/* ------------------------------------ SETUP FOR VALUE DISPLAY ----------------------------------- */

	tft.setTextFont(1);
	tft.setTextSize(2);
	delay(300); //short buffer

	// Set Vesc Serial0 for uart communication
	UART.setSerialPort(&VescSerial);

	// Vertical green lines on each side of screen 
	tft.drawLine(0,0,0,480,TFT_GREEN);
	tft.drawLine(319,0,319,480,TFT_GREEN);

	// Horizontal green lines on each side of screen
	tft.drawLine(0,0,319,0,TFT_GREEN);
	tft.drawLine(0,479,319,479,TFT_GREEN);
	
	// Electrium Logo from progmem
	drawImageFromProgmem(42, 440, WIDTH, HEIGHT, electrium_logo);

	// Battery image from progmem
	drawImageFromProgmem(batteryxpos, batteryypos, 24, 24, battery);
	

	tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

	// All display locations for each value we are reading
	tft.drawString("Input Voltage", 160, textypos - 55);
	tft.drawString("Battery Percentage", 160, textypos + 60);
	tft.drawString("Speed of Motor", 160, textypos + 185);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.setTextSize(3);
	delay(100);

 /* -------------------------------------------------------------------------------------------------- */

}

/* ------------------------------------------ MAIN LOOP BELOW ----------------------------------------*/

void loop() {

	// grabbing values from VESC UART communication line
	// UART.getVescValues() fills the UART.data struct and returns t/f if success or unsuccess.
	if (UART.getVescValues()) {
  	inpVoltage = UART.data.inpVoltage;
		// This is a completely innacurate battery calculation, but it is used for ease.
		// Generally, you wouldnt see a linear charge to discharge curve. So be careful with this!
		batteryval = (int)floor(((inpVoltage - 30.0f) / (36.0f - 30.0f)) * 100.0f); 
		speed = (int)floor(0.00446 * UART.data.rpm);
	}

	// updating input voltage on lcd display only if change is registered, see function
	update_inpVoltage();

	// updating battery value & battery image from progmem
	update_battery();

	// updating speed on display
	update_erpm();

	// updating last values
	last_inpVoltage = inpVoltage;
	last_batteryval = batteryval;
	last_speed = speed;

	// delay
	delayMicroseconds(10); // x0.01 of a millisecond
}

/* -------------------------------------------------------------------------------------------------*/



