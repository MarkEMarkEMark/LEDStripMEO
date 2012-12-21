/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <LEDStripRainbow.h>

LEDStripRainbow::LEDStripRainbow(LEDStripG35& g35, uint8_t pattern) : LEDStripLightProgram(g35, pattern), wait_(0), pattern_(pattern), step_(0)
{
}

uint32_t LEDStripRainbow::Do()
{
    bool ThreeChannel; // 3 channel or 2 channel
	bool toggle;
	toggle = true;
    for (int i=0; i < light_count_; i++)
    {
        switch (pattern_ % 12)
        {
        case 0:
            ThreeChannel = false;
            g35_.fill_color(i, 1, LEDStripRainbow::LineRG((i + step_) % 256));
            break;
        case 1:
            ThreeChannel = false;
            g35_.fill_color(i, 1, LEDStripRainbow::LineGB((i + step_) % 256));
            break;
        case 2:
            ThreeChannel = false;
            g35_.fill_color(i, 1, LEDStripRainbow::LineBR((i + step_) % 256));
            break;
        case 3:
            ThreeChannel = true;
            g35_.fill_color(i, 1, LEDStripRainbow::Wheel((i + step_) % 384));
            break;
        case 4: //spread across all lights (the more lights, the more noticable)
            ThreeChannel = false;
            g35_.fill_color(i, 1, LEDStripRainbow::LineRG(((i * 256 / light_count_) + step_) % 256));
            break;
        case 5:
            ThreeChannel = false;
            g35_.fill_color(i, 1, LEDStripRainbow::LineGB(((i * 256 / light_count_) + step_) % 256));
			break;
        case 6:
            ThreeChannel = false;
            g35_.fill_color(i, 1, LEDStripRainbow::LineBR(((i * 256 / light_count_) + step_) % 256));
			break;
        case 7:
            ThreeChannel = true;
            g35_.fill_color(i, 1, LEDStripRainbow::Wheel(((i * 384 / light_count_) + step_) % 384));
            break;
        case 8: //interlaced
            ThreeChannel = false;
            if (toggle)
			{
				g35_.fill_color(i, 1, LEDStripRainbow::LineRG((i + 128 + step_) % 256));
				toggle = false;
			} else
			{
				g35_.fill_color(i, 1, LEDStripRainbow::LineRG((i + step_) % 256));
				toggle = true;
			}
            break;
        case 9:
            ThreeChannel = false;
		    if (toggle)
			{
				g35_.fill_color(i, 1, LEDStripRainbow::LineGB((i + 128 + step_) % 256));
				toggle = false;
			} else
			{
				g35_.fill_color(i, 1, LEDStripRainbow::LineGB((i + step_) % 256));
				toggle = true;
			}
            break;
        case 10:
            ThreeChannel = false;
            if (toggle)
			{
				g35_.fill_color(i, 1, LEDStripRainbow::LineBR((i + 128 + step_) % 256));
				toggle = false;
			} else
			{
				g35_.fill_color(i, 1, LEDStripRainbow::LineBR((i + step_) % 256));
				toggle = true;
			}
            break;
        case 11:
            ThreeChannel = true;
            if (toggle)
			{
				g35_.fill_color(i, 1, LEDStripRainbow::Wheel((i + 192 + step_) % 384));
				toggle = false;
			} else
			{
				g35_.fill_color(i, 1, LEDStripRainbow::Wheel((i + step_) % 384));
				toggle = true;
			}
            break;
        }
    }
	g35_.show();

    //reset at end of wheel or line
    step_++;

    //if (((step_ == 384) && ThreeChannel) || ((step_ == 256) && !ThreeChannel))
    //{
    //    step_ = 0;
    //}

    delay(wait_);

    return bulb_frame_;
}

uint32_t LEDStripRainbow::Wheel(uint16_t WheelPos)
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

uint32_t LEDStripRainbow::LineRG(uint16_t WheelPos)
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

uint32_t LEDStripRainbow::LineGB(uint16_t WheelPos)
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

uint32_t LEDStripRainbow::LineBR(uint16_t WheelPos)
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