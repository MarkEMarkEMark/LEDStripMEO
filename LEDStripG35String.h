#ifndef INCLUDE_LEDStripG35_STRING_H
#define INCLUDE_LEDStripG35_STRING_H

#include <LEDStripG35.h>

// A G35String knows how to talk to a real GE Color Effects light string.
// In particular, it implements the set_color() method of the G35 interface.
//
// These strings need enumerate() to be called before anything else, so that
// each bulb has an individual address. In many cases, your lights will work
// as expected even if you forget to call enumerate(), because most programs
// happen to do the same thing as enumerate() -- namely, they send commands
// to all bulbs starting with bulb #0 and ending with bulb #N-1. If your
// light programs look right but fractured, it's because you forgot to call
// enumerate().
class LEDStripG35String : public LEDStripG35
{
public:
    LEDStripG35String(uint8_t light_count);

    // Implementation of G35 interface.
    virtual uint16_t get_light_count()
    {
        return light_count_;
    }
    void set_color(uint8_t led, color_t color);

	void show(void);
};

#endif  // INCLUDE_LEDStripG35_STRING_H