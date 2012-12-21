/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#ifndef INCLUDE_G35_LEDStrip_PROGRAMS_H
#define INCLUDE_G35_LEDStrip_PROGRAMS_H

#include <LEDStripSwitchOff.h>
#include <LEDStripLightProgram.h>
#include <LEDStripRainbow.h>
#include <LEDStripWhites.h>
#include <LEDStripRandomStrobe.h>
#include <LEDStripSineWave.h>
#include <LEDStripSimplexNoise.h>
#include <LEDStripChasing.h>
#include <LEDStripColorPhasing.h>
#include <LEDStripDither.h>
//#include <LEDStripOscillate.h>

class LEDStripProgramGroup : public LEDStripLightProgramGroup
{
public:
    enum {ProgramCount = 8};

    virtual LEDStripLightProgram* CreateProgram(LEDStripG35& lights, uint8_t program_index, uint8_t pattern);
};

#endif  // INCLUDE_G35_LEDStrip_PROGRAMS_H