/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.
  and Mark Ortiz

  The 1st 13 patterns are obvious primary/secondary colour combos
  14/15 are my own attempts at pleasing colours schemes
  16+ are attempts to use colour theory to form triads and tetrads of colour (see http://colorschemedesigner.com/)
  I hope to programmatically create triads and tetrads in a future version, so I can rotate them around the colour wheel
  I've ordered the colours in AccentedAnalogic, so that if the sequence size is 4 you get the full primary, secondaries and complimentary
  , but 3 removes complimentary, and 2 removes primary

  See README for complete attributions.
*/

#include <LEDStripChasing.h>

LEDStripChasing::LEDStripChasing(LEDStripG35& g35, uint8_t pattern)
    : LEDStripLightProgram(g35, pattern), count_(1), sequence_(0), wait_(10), pattern_(pattern) //, cR1_(0), cG1_(0), cB1_(0), cR2_(0), cG2_(0), cB2_(0), cR3_(0), cG3_(0), cB3_(0), cR4_(0), cG4_(0), cB4_(0), firstTime_(true))
{
    Serial.print("LEDStripChasing Pattern: ");
    Serial.println(pattern);
}

uint32_t LEDStripChasing::Do()
{
	wait_ = 25; //default
    switch (pattern_ % 26)
    {
    case 0:
		wait_ = 66;
        g35_.fill_sequence(0, count_, sequence_, 1, RealWheel);
        break;
    case 1:
        g35_.fill_sequence(0, count_, sequence_, 5, RedAccentedAlalogic);
        break;
    case 2:
		g35_.fill_sequence(0, count_, sequence_, 5, GreenAccentedAlalogic);
        break;
    case 3:
		g35_.fill_sequence(0, count_, sequence_, 5, BlueAccentedAlalogic);
        break;
    case 4:
        g35_.fill_sequence(0, count_, sequence_, 3, Valentines);
        break;
    case 5:
        g35_.fill_sequence(0, count_, sequence_, 3, BlueTriad);
        break;
    case 6:
        g35_.fill_sequence(0, count_, sequence_, 3, BlueTetrad);
        break;
    case 7:
        g35_.fill_sequence(0, count_, sequence_, 3, PurpleTetrad);
        break;
    case 8:
        g35_.fill_sequence(0, count_, sequence_, 3, GreenTetrad);
        break;
    case 9:
        g35_.fill_sequence(0, count_, sequence_, 5, RGBY);
        break;
    case 10:
        g35_.fill_sequence(0, count_, sequence_, 10, RWB);
        break;
    case 11:
        g35_.fill_sequence(0, count_, sequence_, 5, RC);
        break;
    case 12:
        g35_.fill_sequence(0, count_, sequence_, 5, GM);
        break;
    case 13:
        g35_.fill_sequence(0, count_, sequence_, 5, BY);
        break;
    case 14:
        g35_.fill_sequence(0, count_, sequence_, 2, RCGMBY);
		wait_ = 30;
        break;
    case 15:
        g35_.fill_sequence(0, count_, sequence_, 5, RG);
        break;
    case 16:
        g35_.fill_sequence(0, count_, sequence_, 5, GB);
        break;
    case 17:
        g35_.fill_sequence(0, count_, sequence_, 5, BR);
        break;
    case 18:
        g35_.fill_sequence(0, count_, sequence_, 5, CM);
        break;
    case 19:
        g35_.fill_sequence(0, count_, sequence_, 5, MY);
        break;
    case 20:
        g35_.fill_sequence(0, count_, sequence_, 5, YC);
        break;
    case 21:
        g35_.fill_sequence(0, count_, sequence_, 5, RGB);
        break;
    case 22:
        g35_.fill_sequence(0, count_, sequence_, 5, CYM);
        break;
    case 23:
        g35_.fill_sequence(0, count_, sequence_, 4, PastelRGB);
        break;
	case 24:
        g35_.fill_sequence(0, count_, sequence_, 3, RWG);
        break;
    case 25:
        g35_.fill_sequence(0, count_, sequence_, 3, PurplyBlue);
		break;
    }
    if (count_ < light_count_)
    {
        ++count_;
    }
    else
    {
        ++sequence_;
    }

	g35_.show();

    delay(wait_);
    return bulb_frame_;
}

// static

color_t LEDStripChasing::RedAccentedAlalogic(uint16_t sequence) 
{
    sequence = sequence % 3;  //accent removed - % 4 for accent
    if (sequence == 0)
    {
        return COLOR(0x78, 0x00, 0x48);
    }
    if (sequence == 1)
    {
        return COLOR(0x78, 0x38, 0x00);
    }
    if (sequence == 2)
    {
        return COLOR(0x78, 0x00, 0x00);
    }
	return COLOR(0x00, 0x78, 0x00);
}

color_t LEDStripChasing::GreenAccentedAlalogic(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR(0x50, 0x78, 0x00);
    }
    if (sequence == 1)
    {
        return COLOR(0x00, 0x78, 0x78);
    }
    if (sequence == 2)
    {
        return COLOR(0x00, 0x78, 0x00);
    }
	return COLOR(0x78, 0x00, 0x00);
}

color_t LEDStripChasing::BlueAccentedAlalogic(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR(0x00, 0x48, 0x78); //30 degrees anti-clockwise of Primary
    }
    if (sequence == 1)
    {
        return COLOR(0x38, 0x00, 0x78); //30 degrees clockwise of Primary
    }
    if (sequence == 2)   //Primary
    {
        return COLOR(0x00, 0x00, 0x78);
    }
	return COLOR(0x78, 0x60, 0x00); //180 degrees - Complimentary
}

color_t LEDStripChasing::Valentines(uint16_t sequence)
{
    sequence = sequence % 10;
    if (sequence == 0)
    {
        return COLOR(0x63,0,0);
    }
    if (sequence == 1)
    {
        return COLOR(0x5E,0x08,0x08);
    }
    if (sequence == 2)
    {
        return COLOR(0x5A,0x10,0x10);
    }
    if (sequence == 3)
    {
        return COLOR(0x56,0x18,0x18);
    }
    if (sequence == 4)
    {
        return COLOR(0x52,0x20,0x20);
    }
    if (sequence == 5)
    {
        return COLOR(0x48,0x48,0x48);
    }
    if (sequence == 6)
    {
        return COLOR(0x52,0x20,0x20);
    }
    if (sequence == 7)
    {
        return COLOR(0x56,0x18,0x18);
    }
    if (sequence == 8)
    {
        return COLOR(0x5A,0x10,0x10);
    }
    return COLOR(0x5E,0x08,0x08); //5
}


color_t LEDStripChasing::PastelRGB(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR(0x78, 0x10, 0x08);
    }
    if (sequence == 1)
    {
        return COLOR(0x40, 0x78, 0x10);
    }
    return COLOR(0x58, 0x28, 0x78);
}

color_t LEDStripChasing::RGBY(uint16_t sequence)
{
    sequence = sequence % 4;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    if (sequence == 1)
    {
        return COLOR_GREEN;
    }
    if (sequence == 2)
    {
        return COLOR_BLUE;
    }
    return COLOR_YELLOW;
}

color_t LEDStripChasing::RWB(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    if (sequence == 1)
    {
        return COLOR_WHITE;
    }
    return COLOR_BLUE;
}

color_t LEDStripChasing::RWG(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    if (sequence == 1)
    {
        return COLOR_WHITE;
    }
    return COLOR_GREEN;
}

color_t LEDStripChasing::RC(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    return COLOR_CYAN;
}

color_t LEDStripChasing::GM(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_GREEN;
    }
    return COLOR_MAGENTA;
}

color_t LEDStripChasing::BY(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_BLUE;
    }
    return COLOR_YELLOW;
}

color_t LEDStripChasing::RG(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    return COLOR_GREEN;
}

color_t LEDStripChasing::GB(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_GREEN;
    }
    return COLOR_BLUE;
}

color_t LEDStripChasing::BR(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_BLUE;
    }
    return COLOR_RED;
}

color_t LEDStripChasing::CM(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_CYAN;
    }
    return COLOR_MAGENTA;
}

color_t LEDStripChasing::MY(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_MAGENTA;
    }
    return COLOR_YELLOW;
}

color_t LEDStripChasing::YC(uint16_t sequence)
{
    sequence = sequence % 2;
    if (sequence == 0)
    {
        return COLOR_YELLOW;
    }
    return COLOR_CYAN;
}

color_t LEDStripChasing::RGB(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    if (sequence == 1)
    {
        return COLOR_GREEN;
    }
    return COLOR_BLUE;
}

color_t LEDStripChasing::CYM(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR_CYAN;
    }
    if (sequence == 1)
    {
        return COLOR_YELLOW;
    }
    return COLOR_MAGENTA;
}

color_t LEDStripChasing::RCGMBY(uint16_t sequence)
{
    sequence = sequence % 6;
    if (sequence == 0)
    {
        return COLOR_RED;
    }
    if (sequence == 1)
    {
        return COLOR_YELLOW;
    }
    if (sequence == 2)
    {
        return COLOR_GREEN;
    }
    if (sequence == 3)
    {
        return COLOR_CYAN;
    }
    if (sequence == 4)
    {
        return COLOR_BLUE;
    }
    return COLOR_MAGENTA;
}

color_t LEDStripChasing::PurplyBlue(uint16_t sequence)
{
    sequence = sequence % 6;
    if (sequence == 0)
    {
        return COLOR(0x00,0x00,0x58);
    }
    if (sequence == 1)
    {
        return COLOR(0x18,0x00,0x50);
    }
    if (sequence == 2)
    {
        return COLOR(0x30,0x00,0x48);
    }
    if (sequence == 3)
    {
        return COLOR(0x40,0x00,0x40);
    }
    if (sequence == 4)
    {
        return COLOR(0x30,0x00,0x48);
    }
    return COLOR(0x18,0,0x50); //5
}



color_t LEDStripChasing::BlueBronze(uint16_t sequence)
{
    sequence = sequence % 3;
    if (sequence == 0)
    {
        return COLOR(0x00, 0x10, 0x28);
    }
    if (sequence == 1)
    {
        return COLOR(0x48, 0x40, 0x08);
    }
    return COLOR(0x48, 0x28, 0x08);
}


color_t LEDStripChasing::BlueTriad(uint16_t sequence)
{
    sequence = sequence % 6;
    if (sequence == 1)
    {
        return COLOR(0x78, 0x28, 0x00);
    }
    if (sequence == 5)
    {
        return COLOR(0x78, 0x60, 0x00);
    }
    return COLOR(0x00, 0x40, 0x78);
}

color_t LEDStripChasing::BlueTetrad(uint16_t sequence)
{
    sequence = sequence % 4;
    if (sequence == 0)
    {
        return COLOR(0x08, 0x20, 0x58);
    }
    if (sequence == 1)
    {
        return COLOR(0x20, 0x08, 0x58);
    }
    if (sequence == 2)
    {
        return COLOR(0x00, 0x50, 0x50);
    }
    return COLOR(0x78, 0x58, 0x00);
}

color_t LEDStripChasing::PurpleTetrad(uint16_t sequence)
{
    sequence = sequence % 4;
    if (sequence == 0)
    {
        return COLOR(0x78, 0x00, 0x48);
    }
    if (sequence == 1)
    {
        return COLOR(0x78, 0x00, 0x00);
    }
    if (sequence == 2)
    {
        return COLOR(0x50, 0x00, 0x78);
    }
    return COLOR(0x58, 0x78, 0x00);
}

color_t LEDStripChasing::GreenTetrad(uint16_t sequence)
{
    sequence = sequence % 4;
    if (sequence == 0)
    {
        return COLOR(0x58, 0x78, 0x00);
    }
    if (sequence == 1)
    {
        return COLOR(0x18, 0x78, 0x00);
    }
    if (sequence == 2)
    {
        return COLOR(0x78, 0x78, 0x00);
    }
    return COLOR(0x78, 0x00, 0x50);
}

color_t LEDStripChasing::ColourCycle(uint16_t sequence)
{
	double cR1;
	double cG1;
	double cB1;
	double cR2;
	double cG2;
	double cB2;
	double cR3;
	double cG3;
	double cB3;
	double cR4;
	double cG4;
	double cB4;

	double hue;
	double sat;
	double lum;

	cR1 = (double) 0x00;
	cG1 = (double) 0x48;
	cB1 = (double) 0x78;
	cR2 = (double) 0x7;
	cG2 = (double) 0x00;
	cB2 = (double) 0x78;
	cR3 = (double) 0x00;
	cG3 = (double) 0x00;
	cB3 = (double) 0x78;
	cR4 = (double) 0x78;
	cG4 = (double) 0xC;

	uint8_t hueShift;
	hueShift = sequence % 16;

    sequence = sequence % 4;
    if (sequence == 0)
    {
		//LEDStripChasing::RGB_to_HSL(cR1, cG1, cB1, *hue, *sat, *lum);
		//lum = (double)(((uint8_t)lum + hueShift) % 16);
		//LEDStripChasing::HSL_to_RGB(hue, sat, lum, *cR1, *cG1, *cB1);
        return COLOR((int)cR1, (int)cG1, (int)cB1); //30 degrees anti-clockwise of Primary
    }
    if (sequence == 1)
    {
		//LEDStripChasing::RGB_to_HSL(cR2, cG2, cB2, *hue, *sat, *lum);
		//lum = (double)(((uint8_t)lum + hueShift) % 16);
		//LEDStripChasing::HSL_to_RGB(hue, sat, lum, *cR2, *cG2, *cB2);
        return COLOR((int)cR2, (int)cG2, (int)cB2); //30 degrees clockwise of Primary
    }
    if (sequence == 2)   //Primary
    {
		//LEDStripChasing::RGB_to_HSL(cR3, cG3, cB3, *hue, *sat, *lum);
		//lum = (double)(((uint8_t)lum + hueShift) % 16);
		//LEDStripChasing::HSL_to_RGB(hue, sat, lum, *cR3, *cG3, *cB3);
        return COLOR((int)cR3, (int)cG3, (int)cB3);
    }
	if (sequence == 3) //180 degrees - Complimentary
    {
		//LEDStripChasing::RGB_to_HSL(cR4, cG4, cB4, *hue, *sat, *lum);
		//lum = (double)(((uint8_t)lum + hueShift) % 16);
		//LEDStripChasing::HSL_to_RGB(hue, sat, lum, *cR4, *cG4, *cB4);
		return COLOR((int)cR4, (int)cG4, (int)cB4);
    }
}


/*
A Fast HSL-to-RGB Transform
by Ken Fishkin
from "Graphics Gems", Academic Press, 1990
*/
    /*
     * RGB-HSL transforms.
     * Ken Fishkin, Pixar Inc., January 1989.
     */

    /*
    * given r,g,b on [0 ... 1],
    * return (h,s,l) on [0 ... 1]
    */
void LEDStripChasing::RGB_to_HSL	(double r, double g, double b, double *h, double *s, double *l)
//double 	r,g,b;
//double *h, *s, *l;
{
    double v;
    double m;
    double vm;
    double r2, g2, b2;

    v = max(r,g);
    v = max(v,b);
    m = min(r,g);
    m = min(m,b);

    if ((*l = (m + v) / 2.0) <= 0.0) return;
    if ((*s = vm = v - m) > 0.0) {
		*s /= (*l <= 0.5) ? (v + m ) :
			(2.0 - v - m) ;
    } else
	return;


    r2 = (v - r) / vm;
    g2 = (v - g) / vm;
    b2 = (v - b) / vm;

    if (r == v)
		*h = (g == m ? 5.0 + b2 : 1.0 - g2);
    else if (g == v)
		*h = (b == m ? 1.0 + r2 : 3.0 - b2);
    else
		*h = (r == m ? 3.0 + g2 : 5.0 - r2);

    	*h /= 6;
	}

    /*
     * given h,s,l on [0..1],
     * return r,g,b on [0..1]
     */

void LEDStripChasing::HSL_to_RGB(double h, double sl, double l, double *r, double *g, double *b)
//double 	h,sl,l;
//double 	*r, *g, *b;
{
    double v;

    v = (l <= 0.5) ? (l * (1.0 + sl)) : (l + sl - l * sl);
    if (v <= 0) {
		*r = *g = *b = 0.0;
    } else {
		double m;
		double sv;
		int sextant;
		double fract, vsf, mid1, mid2;

		m = l + l - v;
		sv = (v - m ) / v;
		h *= 6.0;
		sextant = h;	
		fract = h - sextant;
		vsf = v * sv * fract;
		mid1 = m + vsf;
		mid2 = v - vsf;
		switch (sextant) {
			case 0: *r = v; *g = mid1; *b = m; break;
			case 1: *r = mid2; *g = v; *b = m; break;
			case 2: *r = m; *g = v; *b = mid1; break;
			case 3: *r = m; *g = mid2; *b = v; break;
			case 4: *r = mid1; *g = m; *b = v; break;
			case 5: *r = v; *g = m; *b = mid2; break;
		}
    }
}

color_t LEDStripChasing::RealWheel(uint16_t sequence)
{
	uint16_t position;
	position = sequence / 80;
    sequence = sequence % 5;
    if (sequence == 0)
    {
        return RealWheelSetColor(position); // 45 anti-clockwise
    }
    if ((sequence == 1) || (sequence == 5))
    {
        return RealWheelSetColor(position + 6); // 45 clockwise
    }
    if ((sequence == 2) || (sequence == 4))
    {
        return RealWheelSetColor(position + 3); //0 degrees (main color)
    }
    //return RealWheelSetColor(position + 14); //180 degrees
}

color_t LEDStripChasing::RealWheelSetColor(uint8_t wheelStep)
{
	wheelStep = wheelStep % 24;
	switch (wheelStep)
	{
	case 0:
		return COLOR_000; break;
	case 1:
		return COLOR_015; break;
	case 2:
		return COLOR_030; break;
	case 3:
		return COLOR_045; break;
	case 4:
		return COLOR_060; break;
	case 5:
		return COLOR_075; break;
	case 6:
		return COLOR_090; break;
	case 7:
		return COLOR_105; break;
	case 8:
		return COLOR_120; break;
	case 9:
		return COLOR_135; break;
	case 10:
		return COLOR_150; break;
	case 11:
		return COLOR_165; break;
	case 12:
		return COLOR_180; break;
	case 13:
		return COLOR_195; break;
	case 14:
		return COLOR_210; break;
	case 15:
		return COLOR_225; break;
	case 16:
		return COLOR_240; break;
	case 17:
		return COLOR_255; break;
	case 18:
		return COLOR_270; break;
	case 19:
		return COLOR_285; break;
	case 20:
		return COLOR_300; break;
	case 21:
		return COLOR_315; break;
	case 22:
		return COLOR_330; break;
	case 23:
		return COLOR_345; break;
	}
}