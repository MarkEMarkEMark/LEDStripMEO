#include <LEDStripG35String.h>
#include "SPI.h"
#include "LEDStrip8806.h"

// Declare the number of pixels in strand
const int numPixels = 160;

// Instantiate LED strip;
// On Mega, data(green) = pin 51, clock(yellow) = pin 52.
LEDStrip8806 strip = LEDStrip8806(numPixels);

LEDStripG35String::LEDStripG35String(uint8_t light_count)
    : LEDStripG35()
{
    light_count_ = light_count;
	strip.begin();
}

void LEDStripG35String::set_color(uint8_t bulb, color_t color)
{
	strip.setPixelColor(bulb, color); //strip.Color(r,g,b));
}

void LEDStripG35String::show(void)
{
	noInterrupts();
	strip.show();   // write all the pixels out
	interrupts();
}