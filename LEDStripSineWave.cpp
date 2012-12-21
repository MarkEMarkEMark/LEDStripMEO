/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz
  and Adafruit

  See README for complete attributions.
*/

#include <LEDStripSineWave.h>

LEDStripSineWave::LEDStripSineWave(LEDStripG35& g35, uint8_t pattern) : LEDStripLightProgram(g35, pattern), preFill_(true), strobe_(true), wait_(0), colorMain_(COLOR(0x00,0x00,0x7F)), colorHi_(COLOR(0x7F,0x7F,0x7F)), colorLo_(COLOR(0x00,0x00,0x00)), wavesPerString_(3), rainbowMain_(true), step_(0), step2_(0), pattern_(pattern), graduated_(false)
{
}

#define PI 3.14159265

uint32_t LEDStripSineWave::Do()
{
    switch (pattern_ % 8)
    {
    case 0: //red - candy stripe
        rainbowMain_ = false;
        colorMain_ = COLOR(0x7F,0,0);
		graduated_ = false;
        break;
    case 1: //green
        rainbowMain_ = false;
        colorMain_ = COLOR(0,0x7F,0);
		graduated_ = false;
        break;
    case 2: //blue
        rainbowMain_ = false;
        colorMain_ = COLOR(0,0,0x7F);
		graduated_ = false;
        break;
    case 3: //yellow
        rainbowMain_ = false;
        colorMain_ = COLOR(0x5F,0x5F,0);
		graduated_ = false;
        break;
    case 4: //magenta
        rainbowMain_ = false;
        colorMain_ = COLOR(0x5F,0,0x5F);
		graduated_ = false;
        break;
    case 5: //cyan
        rainbowMain_ = false;
        colorMain_ = COLOR(0,0x5F,0x5F);
		graduated_ = false;
        break;
    case 6: //solid changing rainbow
        rainbowMain_ = true;
		graduated_ = false;
        break;
    case 7: //graduated rainbow
        rainbowMain_ = true;
		graduated_ = true;
        break;
    }

    float y;
    byte  rMain, gMain, bMain, rOut, gOut, bOut, rhi, ghi, bhi, rlo, glo, blo, rRainbow, gRainbow, bRainbow;

    // Need to decompose colors into their r, g, b elements
    bMain = (colorMain_ >> 16) & 0x7f;
    gMain = (colorMain_ >>  8) & 0x7f;
    rMain =  colorMain_        & 0x7f;

    bhi = (colorHi_ >> 16) & 0x7f;
    ghi = (colorHi_ >>  8) & 0x7f;
    rhi =  colorHi_        & 0x7f;

    blo = (colorLo_ >> 16) & 0x7f;
    glo = (colorLo_ >>  8) & 0x7f;
    rlo =  colorLo_        & 0x7f;

    uint32_t colorRainbow;
    colorRainbow = LEDStripSineWave::Wheel(step2_ % 384);

    bRainbow = (colorRainbow >> 16) & 0x7f;
    gRainbow = (colorRainbow >>  8) & 0x7f;
    rRainbow =  colorRainbow  & 0x7f;

    for(int i = 0; i < light_count_; i++)
    {

		if (graduated_)  //override solid rainbow with graduated one
		{
			colorRainbow = LEDStripSineWave::Wheel(((384 * i) / light_count_) + i);

			bRainbow = (colorRainbow >> 16) & 0x7f;
			gRainbow = (colorRainbow >>  8) & 0x7f;
			rRainbow =  colorRainbow  & 0x7f;
		}


        y = sin(PI * wavesPerString_ * (float)(step_ + i) / (float)light_count_);
        if(y >= 0.0)
        {
            // Peaks of sine wave are white
            y  = 1.0 - y; // Translate Y to 0.0 (top) to 1.0 (center)
            if (rainbowMain_)
            {
				rOut = rhi - (byte)((float)(rhi - rRainbow) * y);
				gOut = ghi - (byte)((float)(ghi - gRainbow) * y);
				bOut = bhi - (byte)((float)(bhi - bRainbow) * y);
            }
            else
            {
                rOut = rhi - (byte)((float)(rhi - rMain) * y);
                gOut = ghi - (byte)((float)(ghi - gMain) * y);
                bOut = bhi - (byte)((float)(bhi - bMain) * y);
            }
        }
        else
        {
            // Troughs of sine wave are black
            y += 1.0; // Translate Y to 0.0 (bottom) to 1.0 (center)
            if (rainbowMain_)
            {
                rOut = rlo + (byte)((float)(rRainbow) * y);
                gOut = glo + (byte)((float)(gRainbow) * y);
                bOut = blo + (byte)((float)(bRainbow) * y);
            }
            else
            {
                rOut = rlo + (byte)((float)(rMain) * y);
                gOut = glo + (byte)((float)(gMain) * y);
                bOut = blo + (byte)((float)(bMain) * y);
            }
        }
        g35_.fill_color(i, 1, COLOR(rOut, gOut, bOut));
    }

	g35_.show();
    step_++;
    step2_++;
    if (step2_ == 384) // all colors in the wheel
    {
        step2_ = 0;
    }

    delay(wait_);
    return bulb_frame_;
}

uint32_t LEDStripSineWave::Wheel(uint16_t WheelPos)
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