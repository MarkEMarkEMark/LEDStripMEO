/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_LEDStrip_SWITCHOFF_H
#define INCLUDE_G35_PROGRAMS_LEDStrip_SWITCHOFF_H

#include <LEDStripLightProgram.h>

class LEDStripSwitchOff : public LEDStripLightProgram
{
public:
    LEDStripSwitchOff(LEDStripG35& g35);
    uint32_t Do();
};

#endif