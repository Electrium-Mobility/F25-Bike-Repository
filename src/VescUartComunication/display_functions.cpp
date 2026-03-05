#include "display_functions.h"
#include "vesc_values.h"

// Function that draws image through an array of hex values in progmem
void drawImageFromProgmem(int x, int y, int width, int height, const uint16_t* image) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            // Calculate index in the array
            int index = row * width + col;
            // Read 16-bit pixel from PROGMEM
            uint16_t color = pgm_read_word(&image[index]);
            // Draw pixel
            tft.drawPixel(x + col, y + row, color);
        }
    }
}

void update_inpVoltage() {
	if(last_inpVoltage != inpVoltage) {
		tft.setCursor(textxpos - 10, textypos - 40);
		tft.print("        "); // used to clear previous values
		tft.setCursor(textxpos - 10, textypos - 40);
		tft.print(inpVoltage, 2);
		tft.setTextSize(1);
		tft.setCursor(tft.getCursorX(), tft.getCursorY() + 14);
    tft.print("V");
		tft.setTextSize(3);
	}
}

void update_battery() {
	if(last_batteryval != batteryval) {
		tft.setCursor(textxpos, textypos + 80);
		tft.print("        ");
		tft.setCursor(textxpos, textypos + 80);
		tft.print(batteryval);
  	tft.print("%");
		// this is complete garbage to look at, but its just printing rectangles within the
		// progmem battery image to indicate changes in battery percentage.
		if(batteryval > 80 && batteryval <= 100 && last_fill != 5) {
			tft.fillRect(batteryxpos + 8, batteryypos + 5, 8, 18, TFT_GREEN);
			last_fill = 5;
		} else if(batteryval > 60 && batteryval <= 80 && last_fill != 4) {
			tft.fillRect(batteryxpos + 8, batteryypos + 5, 8, 18, TFT_BLACK);
			tft.fillRect(batteryxpos + 8, batteryypos + 8, 8, 15, TFT_GREEN);
			last_fill = 4;
		} else if(batteryval > 40 && batteryval <= 60 && last_fill != 3) {
			tft.fillRect(batteryxpos + 8, batteryypos + 5, 8, 18, TFT_BLACK);
			tft.fillRect(batteryxpos + 8, batteryypos + 11, 8, 12, TFT_GREEN);
			last_fill = 3;
		} else if(batteryval > 20 && batteryval <= 40 && last_fill != 2) {
			tft.fillRect(batteryxpos + 8, batteryypos + 5, 8, 18, TFT_BLACK);
			tft.fillRect(batteryxpos + 8, batteryypos + 14, 8, 9, TFT_GREEN);
			last_fill = 2;
		} else if(batteryval > 5 && batteryval <= 20 && last_fill != 1) {
			tft.fillRect(batteryxpos + 8, batteryypos + 5, 8, 18, TFT_BLACK);
			tft.fillRect(batteryxpos + 8, batteryypos + 17, 8, 6, TFT_YELLOW);
			last_fill = 1;
		} else if(batteryval > 0 && batteryval <= 5 && last_fill != 0){
			tft.fillRect(batteryxpos + 8, batteryypos + 5, 8, 18, TFT_BLACK);
			tft.fillRect(batteryxpos + 8, batteryypos + 21, 8, 2, TFT_RED);
			last_fill = 0;
		} else if(batteryval <= 0 && last_fill != -1) {
			tft.fillRect(batteryxpos + 8, batteryypos + 5, 8, 18, TFT_BLACK);
			last_fill = -1;
		}
	}
}

void update_erpm() {
	if(last_speed != speed) {
		tft.setCursor(textxpos + 5, textypos + 200);
		tft.print("        ");
		tft.setCursor(textxpos, textypos + 200);
		tft.print(speed);
		tft.setTextSize(1);
		tft.setCursor(tft.getCursorX(), tft.getCursorY() + 14);
  	tft.print("km/h");
		tft.setTextSize(3);
	}
}
