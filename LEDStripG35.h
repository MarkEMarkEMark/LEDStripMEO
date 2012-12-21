/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  Original version by Paul Martis (http://www.digitalmisery.com). See
  README for complete attributions.
*/

#ifndef INCLUDE_LEDStripG35_ARDUINO_H
#define INCLUDE_LEDStripG35_ARDUINO_H

#include <Arduino.h>

#define color_t uint32_t
#define CHANNEL_MAX           (0x7F)   // Each color channel is 7-bit

// Color is 21-bit (7-bit each G, R, B) - note! G R B
#define COLOR(r, g, b)        (0x808080 | ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b) //((r) + ((g) << 8) + ((b) << 16)) & 0x7f7f7f
#define COLOR_WHITE           COLOR(CHANNEL_MAX, CHANNEL_MAX, CHANNEL_MAX)
#define COLOR_BLACK           COLOR(0, 0, 0)
#define COLOR_RED             COLOR(CHANNEL_MAX, 0, 0)
#define COLOR_GREEN           COLOR(0, CHANNEL_MAX, 0)
#define COLOR_BLUE            COLOR(0, 0, CHANNEL_MAX)
#define COLOR_CYAN            COLOR(0,CHANNEL_MAX, CHANNEL_MAX)
#define COLOR_MAGENTA         COLOR(CHANNEL_MAX, 0,CHANNEL_MAX)
#define COLOR_YELLOW          COLOR(CHANNEL_MAX,CHANNEL_MAX, 0)
#define COLOR_PURPLE          COLOR(0x50, 0x18, 0x68)
#define COLOR_ORANGE          COLOR(0x78, 0x08, 0x00)
#define COLOR_PALE_ORANGE     COLOR(0x40, 0x08, 0x00)
#define COLOR_WARMWHITE       COLOR(0x78, 0x40, 0x10)
#define COLOR_INDIGO          COLOR(0x30, 0x00, 0x78)
#define COLOR_VIOLET          COLOR(0x40, 0x00, 0x78)

//a real color wheel, 15 degrees increments, fully saturated
#define COLOR_000			COLOR(0x7F,0x00,0x00)
#define COLOR_015			COLOR(0x7F,0x24,0x00)
#define COLOR_030			COLOR(0x7F,0x3A,0x00)
#define COLOR_045			COLOR(0x7F,0x49,0x00)
#define COLOR_060			COLOR(0x7F,0x55,0x00)
#define COLOR_075			COLOR(0x7F,0x5F,0x00)
#define COLOR_090			COLOR(0x7F,0x69,0x00)
#define COLOR_105			COLOR(0x7F,0x74,0x00)
#define COLOR_120			COLOR(0x7F,0x7F,0x00)
#define COLOR_135			COLOR(0x69,0x7F,0x00)
#define COLOR_150			COLOR(0x55,0x7F,0x00)
#define COLOR_165			COLOR(0x3A,0x7F,0x00)
#define COLOR_180			COLOR(0x00,0x7F,0x00)
#define COLOR_195			COLOR(0x00,0x7F,0x49)
#define COLOR_210			COLOR(0x00,0x7F,0x7F)
#define COLOR_225			COLOR(0x00,0x48,0x7F)
#define COLOR_240			COLOR(0x00,0x26,0x7F)
#define COLOR_255			COLOR(0x00,0x00,0x7F)
#define COLOR_270			COLOR(0x1E,0x00,0x7F)
#define COLOR_285			COLOR(0x36,0x00,0x7F)
#define COLOR_300			COLOR(0x52,0x00,0x7F)
#define COLOR_315			COLOR(0x7F,0x00,0x7F)
#define COLOR_330			COLOR(0x7F,0x00,0x48)
#define COLOR_345			COLOR(0x7F,0x00,0x26)

// G35 is an abstract class representing a string of G35 lights of arbitrary
// length. LightPrograms talk to this interface.
class LEDStripG35
{
public:
    LEDStripG35();

    enum
    {
        RB_RED = 0,
        RB_ORANGE,
        RB_YELLOW,
        RB_GREEN,
        RB_BLUE,
        RB_INDIGO,
        RB_VIOLET
    };

    enum
    {
        RB_FIRST = RB_RED,
        RB_LAST = RB_VIOLET,
        RB_COUNT = RB_LAST + 1
    };

    virtual uint16_t get_light_count() = 0;
    virtual uint16_t get_last_light()
    {
        return get_light_count() - 1;
    }
    virtual uint16_t get_halfway_point()
    {
        return get_light_count() / 2;
    }

    // One bulb's share of a second, in milliseconds
    virtual uint8_t get_bulb_frame()
    {
        return 1000 / get_light_count();
    }

    // Turn on a specific LED with a color and brightness
    virtual void set_color(uint8_t bulb, color_t color) = 0;

	virtual void show();

    // Color data type
    static color_t color(uint8_t r, uint8_t g, uint8_t b);

    // Make all LEDs the same color starting at specified beginning LED
    virtual void fill_color(uint8_t begin, uint8_t count, color_t color);

    virtual void fill_sequence(uint16_t sequence, uint8_t span_size,
                               color_t (*sequence_func)(uint16_t sequence));
    virtual void fill_sequence(uint8_t begin, uint8_t count, uint16_t sequence,
                               uint8_t span_size, color_t (*sequence_func)(uint16_t sequence));
    virtual void fill_sequence(uint8_t begin, uint8_t count, uint16_t sequence,
                               uint8_t span_size,
                               bool (*sequence_func)(uint16_t sequence,
                                       color_t& color));

protected:
    uint16_t light_count_;
};

#endif  // INCLUDE_LEDStripG35_ARDUINO_H