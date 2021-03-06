/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright � 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_LEDStrip_DITHER_H
#define INCLUDE_G35_PROGRAMS_LEDStrip_DITHER_H

#include <LEDStripLightProgram.h>

class LEDStripDither : public LEDStripLightProgram
{
public:
    LEDStripDither(LEDStripG35& g35, uint8_t pattern);
    uint32_t Do();
	uint32_t Wheel(uint16_t WheelPos);
    uint32_t LineRG(uint16_t WheelPos);
    uint32_t LineGB(uint16_t WheelPos);
    uint32_t LineBR(uint16_t WheelPos);

private:
    uint8_t pattern_;
	uint16_t wait_;
	uint16_t dithStep_;
	uint16_t step_;
};

#endif