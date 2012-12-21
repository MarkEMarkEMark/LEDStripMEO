/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <LEDStripDither.h>

LEDStripDither::LEDStripDither(LEDStripG35& g35, uint8_t pattern)
    : LEDStripLightProgram(g35, pattern), pattern_(pattern), wait_(0), dithStep_(0), step_(0)
{
}

uint32_t LEDStripDither::Do()
{
	bool ThreeChannel;
	uint8_t stepCount;

	// Determine highest bit needed to represent pixel index
	int hiBit = 0;
	int n = light_count_ - 1;
	for(int bit = 1; bit < 0x8000; bit <<= 1) {
		if(n & bit) hiBit = bit;
	}

	int bit, reverse;

	reverse = 0;
	for(bit = 1; bit <= hiBit; bit <<= 1) {
		reverse <<= 1;
		if(dithStep_ & bit) reverse |= 1;
	}

    switch (pattern_ % 8)
    {
	case 0: // Red to Green to Red
        ThreeChannel = false;
		stepCount = 24;
        g35_.fill_color(reverse, 1, LEDStripDither::LineRG(step_ % 256));
        break;
    case 1: // Green to Blue to Green
        ThreeChannel = false;
		stepCount = 24;
        g35_.fill_color(reverse, 1, LEDStripDither::LineGB(step_ % 256));
        break;
    case 2: //Blue to Red to Blue
        ThreeChannel = false;
		stepCount = 24;
        g35_.fill_color(reverse, 1, LEDStripDither::LineBR(step_ % 256));
        break;
    case 3: // Colour wheel smooth
        ThreeChannel = true;
		stepCount = 32;
        g35_.fill_color(reverse, 1, LEDStripDither::Wheel(step_ % 384));
        break;
    case 4: //Colour wheel jump
        ThreeChannel = true;
		stepCount = random(384);
        g35_.fill_color(reverse, 1, LEDStripDither::Wheel(step_ % 384));
        break;
    case 5: //Always changing - narrow
        ThreeChannel = true;
		stepCount = 0;
        g35_.fill_color(reverse, 1, LEDStripDither::Wheel((step_ / 4) % 384));
		step_++;// step_++;
        break;
    case 6: //Always changing - medium
        ThreeChannel = true;
		stepCount = 0;
        g35_.fill_color(reverse, 1, LEDStripDither::Wheel(step_ % 384));
		step_++;// step_++;
        break;
    case 7: //Always changing - wide
        ThreeChannel = true;
		stepCount = 0;
        g35_.fill_color(reverse, 1, LEDStripDither::Wheel((step_ * random(8)) % 384));
		step_++;// step_++;
        break;
    }

	g35_.show();
	delay(wait_);

	dithStep_++;
	if (dithStep_ == (hiBit << 1))
	{
		dithStep_ = 0;

		//reset at end of wheel or line
		step_ = step_ + stepCount;
		//if (((step_ >= 384) && ThreeChannel) || ((step_ >= 256) && !ThreeChannel))
		//{
		//	step_ = 0;
		//}
	}
	return bulb_frame_;
}

uint32_t LEDStripDither::Wheel(uint16_t WheelPos)
{
    byte r, g, b;
    switch(WheelPos / 128)
    {
    case 0:
        r = 127 - WheelPos % 128; // red down
        g = WheelPos % 128;       // green up
        b = 0;                    // blue off
        break;
    case 1:
        g = 127 - WheelPos % 128; // green down
        b = WheelPos % 128;       // blue up
        r = 0;                    // red off
        break;
    case 2:
        b = 127 - WheelPos % 128; // blue down
        r = WheelPos % 128;       // red up
        g = 0;                    // green off
        break;
    }
    return(COLOR(r,g,b));
}

uint32_t LEDStripDither::LineRG(uint16_t WheelPos)
{
    byte r, g, b;
    switch(WheelPos / 128)
    {
    case 0:
        r = 127 - WheelPos % 128; // red down
        g = WheelPos % 128;       // green up
        b = 0;					// blue off
        break;
    case 1:
        r = WheelPos % 128;       // red up
        g = 127 - WheelPos % 128; // green down
        b = 0;					// blue off
        break;
    }
    return(COLOR(r,g,b));
}

uint32_t LEDStripDither::LineGB(uint16_t WheelPos)
{
    byte r, g, b;
    switch(WheelPos / 128)
    {
    case 0:
        r = 0;                    // red off
        g = 127 - WheelPos % 128; // green down
        b = WheelPos % 128;       // blue up
        break;
    case 1:
        r = 0;                    // red off
        g = WheelPos % 128;       // green up
        b = 127 - WheelPos % 128; // blue down
        break;
    }
    return(COLOR(r,g,b));
}

uint32_t LEDStripDither::LineBR(uint16_t WheelPos)
{
    byte r, g, b;
    switch(WheelPos / 128)
    {
    case 0:
        r = WheelPos % 128;       // red up
        g = 0;                    // green off
        b = 127 - WheelPos % 128; // blue down
        break;
    case 1:
        r = 127 - WheelPos % 128; // red down
        g = 0;                    // green off
        b = WheelPos % 128;       // blue up
        break;
    }
    return(COLOR(r,g,b));
}