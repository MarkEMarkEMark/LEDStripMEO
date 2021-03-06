/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2012 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_PROGRAMS_LEDStrip_CHASING_H
#define INCLUDE_G35_PROGRAMS_LEDStrip_CHASING_H

#include <LEDStripLightProgram.h>

class LEDStripChasing : public LEDStripLightProgram
{
public:
    LEDStripChasing(LEDStripG35& g35, uint8_t pattern);
    uint32_t Do();
    static color_t PastelRGB(uint16_t sequence);
    static color_t RGBY(uint16_t sequence);
    static color_t RWB(uint16_t sequence);
    static color_t RC(uint16_t sequence);
    static color_t GM(uint16_t sequence);
    static color_t BY(uint16_t sequence);
    static color_t RG(uint16_t sequence);
    static color_t GB(uint16_t sequence);
    static color_t BR(uint16_t sequence);
    static color_t CM(uint16_t sequence);
    static color_t MY(uint16_t sequence);
    static color_t YC(uint16_t sequence);
    static color_t RGB(uint16_t sequence);
    static color_t CYM(uint16_t sequence);
    static color_t RCGMBY(uint16_t sequence);
    static color_t PurplyBlue(uint16_t sequence);
    static color_t Valentines(uint16_t sequence);
    static color_t BlueTriad(uint16_t sequence);
    static color_t BlueBronze(uint16_t sequence);
    static color_t BlueTetrad(uint16_t sequence);
    static color_t PurpleTetrad(uint16_t sequence);
    static color_t GreenTetrad(uint16_t sequence);
    static color_t GreenAccentedAlalogic(uint16_t sequence);
    static color_t RedAccentedAlalogic(uint16_t sequence);
    static color_t BlueAccentedAlalogic(uint16_t sequence);
	static color_t RWG(uint16_t sequence);
	static color_t ColourCycle(uint16_t sequence);
	void RGB_to_HSL	(double r, double g, double b, double *h, double *s, double *l);
	void HSL_to_RGB(double h, double sl, double l, double *r, double *g, double *b);
	static color_t RealWheel(uint16_t sequence);
	static color_t RealWheelSetColor(uint8_t wheelStep);

private:
    uint8_t count_;
    uint32_t sequence_;
    uint16_t wait_;
    uint8_t pattern_;
};

#endif