/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#include <LEDStripWhites.h>
#include <LEDStrip8806.h>

LEDStripWhites::LEDStripWhites(LEDStripG35& g35, uint8_t pattern)
    : LEDStripLightProgram(g35, pattern), intensity_(0), pattern_(pattern), count_(1), sequence_(0), wait_(50)
{
	uint8_t current = 0;
	//LEDStrip8806 myStrip;

    switch (pattern_ % 7)
    {
    case 0: //Warm White
        g35_.fill_color(0, light_count_, COLOR_WARMWHITE); //myStrip.Color(0x00,0x00,0xFF)); //COLOR_WARMWHITE
		break;
    case 1: //Cold White
        g35_.fill_color(0, light_count_, COLOR_WHITE); //myStrip.Color(0xFF,0x00,0x00)); //COLOUR_WHITE
        break;
    case 2: // Warm & Cold White
        for (int i = 0; i < light_count_; i++)
        {
            if ((i % 2) == 0)
            {
                g35_.fill_color(i, 1, COLOR_WHITE); //
            }
            else
            {
                g35_.fill_color(i, 1, COLOR_WARMWHITE); //
            }
        }
        break;
	case 3: //Hint of RGB
        for (int i = 0; i < light_count_; i++)
        {
			switch (current)
			{
				case 0:
					g35_.fill_color(i, 1, COLOR(0x7F, 0x60, 0x60));
					current = 1;
					break;
				case 1:
					g35_.fill_color(i, 1, COLOR(0x60, 0x7F, 0x60));
					current = 2;
					break;
				case 2:
					g35_.fill_color(i, 1, COLOR(0x60, 0x60, 0x7F));
					current = 0;
					break;
			}
        }
        break;
	case 4: //Hint of CYM
        for (int i = 0; i < light_count_; i++)
        {
			switch (current)
			{
				case 0:
					g35_.fill_color(i, 1, COLOR(0x60, 0x7F, 0x7F));
					current = 1;
					break;
				case 1:
					g35_.fill_color(i, 1, COLOR(0x7F, 0x7F, 0x60));
					current = 2;
					break;
				case 2:
					g35_.fill_color(i, 1, COLOR(0x7F, 0x60, 0x7F));
					current = 0;
					break;
			}
        }
        break;
    }
	g35_.show();
}

uint32_t LEDStripWhites::Do()
{
	switch (pattern_ % 7)
	{
	case 5: //Hint of RGB chase
        g35_.fill_sequence(0, count_, sequence_, 1, RGB);
		g35_.show();
        break;
    case 6:  //Hint of CYM chase
        g35_.fill_sequence(0, count_, sequence_, 1, CYM);
		g35_.show();
        break;
	default:
		return 1000;
	}

	if (count_ < light_count_)
    {
        ++count_;
    }
    else
    {
        ++sequence_;
    }
    delay(wait_);
	return bulb_frame_;
}

color_t LEDStripWhites::RGB(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR(0x7F, 0x60, 0x60);
    }
    if (sequence == 1)
    {
        return COLOR(0x60, 0x7F, 0x60);
    }
    return COLOR(0x60, 0x60, 0x7F);
}

color_t LEDStripWhites::CYM(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR(0x60, 0x7F, 0x7F);
    }
    if (sequence == 1)
    {
        return COLOR(0x7F, 0x7F, 0x60);
    }
    return COLOR(0x7F, 0x60, 0x7F);
}