/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  By Mike Tsao <http://github.com/sowbug>.

  and Mark Ortiz

  See README for complete attributions.
*/

#include <LEDStripRandomStrobe.h>

LEDStripRandomStrobe::LEDStripRandomStrobe(LEDStripG35& g35, uint8_t pattern) : LEDStripLightProgram(g35, pattern), preFill_(false), strobe_(true), wait_(25), noAtATime_(1), colorMain_(COLOR(0,0,4)), colorFlash_(COLOR(15,15,15)), rainbowFlash_(false), rainbowMain_(false), rainbowFrame_(false), step_(0), myBulb_(0), pattern_(pattern)
{
}

//ToDo: reduce brightness of rainbowMain_ colour to increase contrast

uint32_t LEDStripRandomStrobe::Do()
{
    switch (pattern_ % 11)
    {
    case 0: //Black - white flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR_BLACK;
        colorFlash_ = COLOR_WHITE;
		noAtATime_ = 2;
		wait_ = 25;
        break;
    case 1: //Blue - white flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0,0,0x20);
        colorFlash_ = COLOR_WHITE;
		noAtATime_ = 2;
		wait_ = 25;
        break;
    case 2: //Red - white flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0x20,0,0);
        colorFlash_ = COLOR_WHITE;
		noAtATime_ = 2;
		wait_ = 25;
        break;
    case 3: //Green - white flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0,0x20,0);
        colorFlash_ = COLOR_WHITE;
		noAtATime_ = 2;
		wait_ = 25;
        break;
    case 4: //Black - rainbow flash - all bulbs of single colour before change
        rainbowMain_ = false;
        rainbowFlash_ = true;
        rainbowFrame_ = true;
        colorMain_ = COLOR(0,0,0);
		noAtATime_ = 8;
		wait_ = 25;
        break;
    case 5: //Black - rainbow flash - colour changes with each bulb flash
        rainbowMain_ = false;
        rainbowFlash_ = true;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0,0,0);
		noAtATime_ = 8;
		wait_ = 25;
        break;
    case 6:  //Rainbow backround - white flash
        rainbowMain_ = true;
        rainbowFlash_ = false;
        rainbowFrame_ = true;
        colorFlash_ = COLOR_WHITE;
		noAtATime_ = 8;
		wait_ = 25;
        break;
    case 7: //Multi-coloured background - white flash
        rainbowMain_ = true;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorFlash_ = COLOR_WHITE;
		noAtATime_ = 8;
		wait_ = 25;
        break;
    case 8:  //red backround - blue flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0x40,0,0);
        colorFlash_ = COLOR(0,0,0x7F);
		noAtATime_ = 5;
		wait_ = 25;
        break;
    case 9: //blue backround - red flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR(0,0,0x40);
        colorFlash_ = COLOR(0x7F,0,0);
		noAtATime_ = 5;
		wait_ = 25;
		break;
	case 10: //warm white background - white flash
        rainbowMain_ = false;
        rainbowFlash_ = false;
        rainbowFrame_ = false;
        colorMain_ = COLOR_WARMWHITE;
        colorFlash_ = COLOR_WHITE;
		noAtATime_ = 16;
		wait_ = 60;
    }


    ////// This commented out code works, but ideally needs to be outside this class and passed in, because as is the random sequence changes so it's no longer non-repeating
    ////// I've no idea how to do that, so I'm replacing with pre-generated random arrays
    ////// and a choice between 50 / 100 bulbs
    //int myBulbs[light_count_];
    //int myBulb;
    //myBulb = 0;
    //// Initialise myBulbs[] to an ordered range - i.e. myBulbs[0] = 0, myBulbs[1] = 1 etc...
    //for (int range = 0; range < light_count_; range++)
    //{
    //	myBulbs[range] = range;
    //}
    //// Random shuffle (note this will always be the same - maybe can re-seed with last number of shuffle?)
    //// so, myBulbs[0]=38, myBulbs[1]=13.. etc.. for example
    //for (int shuffle = 0; shuffle < light_count_ - 1; shuffle++)
    //{
    //	int myrand = shuffle + (rand() % (light_count_ - shuffle));
    //	int save = myBulbs[shuffle];
    //	myBulbs[shuffle] = myBulbs[myrand];
    //	myBulbs[myrand] = save;
    //}
    //srand(myBulbs[0]); //re-seed for next time
    ////// <<<

    ///// Replacement pre-defined random sequence of bulbs - comment this out, if uncommenting above
    // If you have different amounts of bulbs, you'll have to create your own non-repeating random sequences.
    //int myBulbs050[100]= {3, 15, 49, 0, 41, 26, 5, 48, 29, 46, 34, 24, 18, 43, 28, 2, 9, 44, 39, 19, 16, 35, 42, 36, 38, 37, 20, 14, 32, 10, 47, 11, 8, 31, 13, 25, 7, 22, 6, 30, 23, 4, 12, 17, 33, 27, 40, 45, 1, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //int myBulbs100[100]= {85, 53, 88, 71, 6, 32, 91, 79, 15, 62, 80, 7, 28, 66, 27, 16, 23, 19, 54, 95, 0, 47, 40, 44, 2, 36, 31, 51, 48, 38, 87, 11, 70, 33, 56, 34, 92, 30, 5, 1, 78, 86, 84, 98, 12, 69, 77, 43, 97, 8, 94, 58, 55, 74, 4, 82, 99, 72, 20, 63, 29, 60, 89, 93, 45, 75, 13, 83, 67, 25, 21, 42, 52, 9, 49, 17, 41, 37, 50, 81, 96, 39, 46, 14, 35, 18, 76, 73, 24, 64, 10, 61, 3, 65, 57, 68, 26, 22, 59, 90};
    int myBulbs160[160] = {105, 63, 31, 53, 94, 21, 77, 13, 41, 84, 44, 110, 158, 132, 1, 15, 93, 91, 30, 92, 40, 98, 27, 56, 7, 123, 75, 90, 100, 14, 70, 72, 101, 136, 43, 3, 137, 28, 22, 42, 149, 6, 157, 0, 111, 24, 64, 114, 128, 155, 51, 76, 88, 127, 78, 69, 120, 35, 49, 74, 26, 87, 154, 134, 2, 32, 4, 131, 57, 23, 54, 80, 73, 71, 50, 85, 68, 89, 33, 82, 147, 146, 145, 144, 67, 109, 79, 66, 25, 121, 46, 99, 17, 60, 86, 55, 102, 152, 108, 62, 112, 153, 59, 116, 83, 36, 34, 115, 140, 142, 135, 107, 8, 61, 156, 138, 45, 143, 118, 39, 11, 124, 130, 47, 52, 148, 106, 5, 96, 29, 126, 58, 122, 104, 159, 141, 10, 150, 117, 48, 12, 129, 81, 125, 18, 95, 119, 113, 103, 9, 133, 20, 139, 151, 37, 97, 38, 16, 19, 65};
	int myBulbs[160];
    //int myBulb;
    memcpy(myBulbs, myBulbs160, sizeof(myBulbs));
    ////// <<<


    // pre-fill with background colour if flag set, and first step in
    if (preFill_)
    {
        preFill_ = false;
        if (rainbowMain_)
        {
            g35_.fill_color(0, light_count_, LEDStripRandomStrobe::Wheel((step_ + 192) % 384));
        }
        else
        {
            g35_.fill_color(0, light_count_, colorMain_);
        }
		g35_.show();

    }

    //turn on (set to colorFlash) and off (set to colorMain) the random bulbs
    int simultan = 0;
    do
    {
        if (rainbowFlash_)
        {
            g35_.fill_color(myBulbs[myBulb_], 1, LEDStripRandomStrobe::Wheel(step_ % 384));
        }
        else
        {
            g35_.fill_color(myBulbs[myBulb_], 1, colorFlash_);
        }
		g35_.show();
        
		myBulb_++;
        simultan++;
    }
    while (simultan < noAtATime_);
    delay(wait_);

    if (strobe_) //whether to keep the bulbs on or turn off
    {
        myBulb_ = myBulb_ - noAtATime_; //put back to where was before last do loop
        simultan = 0;
        do
        {
            if (rainbowMain_)
            {
                g35_.fill_color(myBulbs[myBulb_], 1, LEDStripRandomStrobe::Wheel((step_ + 192) % 384));
            }
            else
            {
                g35_.fill_color(myBulbs[myBulb_], 1, colorMain_);
            }
			g35_.show();
            myBulb_++;
            simultan++;
        }
        while (simultan < noAtATime_);
    }

    if (rainbowFrame_) // change colour each frame - i.e. after all bulbs have been flashed
    {
        if (myBulb_ == light_count_)
        {
            myBulb_ = 0;
            step_++;step_++;step_++;step_++;
            if (step_ == 384) // all colors in the wheel
            {
                step_ = 0;
            }
        }
    }
    else     // change colour after each individual flash
    {
        step_++;
        if (step_ == 384) // all colors in the wheel
        {
            step_ = 0;
        }
        if (myBulb_ == light_count_)
        {
            myBulb_ = 0;
        }
    }

    return bulb_frame_;
}

// repeated from rainbow programs: To Do: learn how to just define once...
uint32_t LEDStripRandomStrobe::Wheel(uint16_t WheelPos)
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