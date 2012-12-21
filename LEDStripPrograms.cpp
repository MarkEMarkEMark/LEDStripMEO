/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#include <LEDStripPrograms.h>

LEDStripLightProgram* LEDStripProgramGroup::CreateProgram(LEDStripG35& lights,
        uint8_t program_index, uint8_t pattern)
{
    if (program_index == 255)
    {
        return new LEDStripSwitchOff(lights);
    }
    else
    {
        switch (program_index % ProgramCount)
        {
        case 0:
            return new LEDStripWhites(lights, pattern);
        case 1:
            return new LEDStripRainbow(lights, pattern);
        case 2:
            return new LEDStripRandomStrobe(lights, pattern);
        case 3:
            return new LEDStripSimplexNoise(lights, pattern);
        case 4:
            return new LEDStripSineWave(lights, pattern);
        case 5:
            return new LEDStripChasing(lights, pattern);
        case 6:
            return new LEDStripColorPhasing(lights, pattern);
		case 7:
            return new LEDStripDither(lights, pattern);
        }
    }
    // not reached
    return NULL;
}