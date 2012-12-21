/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <LEDStripSwitchOff.h>

LEDStripSwitchOff::LEDStripSwitchOff(LEDStripG35& g35)
    : LEDStripLightProgram(g35, 0)
{
    g35_.fill_color(0, light_count_, COLOR(0x00,0x00,0x00));
	g35_.show();
}

uint32_t LEDStripSwitchOff::Do()
{
    return bulb_frame_;
}