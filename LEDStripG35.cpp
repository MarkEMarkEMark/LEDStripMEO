/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.

  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  Original version by Paul Martis (http://www.digitalmisery.com). See
  README for complete attributions.

  Special thanks to Richard <rkfoote@gmail.com> and "slinky" for the unrolled-
  loop protocol code that seems to work very well!
*/

#include <LEDStripG35.h>

LEDStripG35::LEDStripG35() : light_count_(0)
{
}

void LEDStripG35::show()
{
	show();
}

// Returns 21-bit color from red, green, and blue components
color_t LEDStripG35::color(uint8_t r, uint8_t g, uint8_t b)
{
	return 0x808080 | ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b;
}

void LEDStripG35::fill_color(uint8_t begin, uint8_t count, color_t color)
{
    while (count--)
    {
        set_color(begin++, color);
    }
}

void LEDStripG35::fill_sequence(uint8_t begin, uint8_t count,
                           uint16_t sequence, uint8_t span_size,
                           color_t (*sequence_func)(uint16_t sequence))
{
    while (count--)
    {
        set_color(begin + count, sequence_func(sequence++ / span_size));
    }
}

void LEDStripG35::fill_sequence(uint16_t sequence, uint8_t span_size,
                           color_t (*sequence_func)(uint16_t sequence))
{
    fill_sequence(0, light_count_, sequence, span_size, sequence_func);
}

void LEDStripG35::fill_sequence(uint8_t begin, uint8_t count,
                           uint16_t sequence, uint8_t span_size,
                           bool (*sequence_func)(uint16_t sequence, color_t& color))
{
    while (count--)
    {
        color_t color;
        sequence_func(sequence++ / span_size, color);
        set_color(begin + count, color);
    }
}