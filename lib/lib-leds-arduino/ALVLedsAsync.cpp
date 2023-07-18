#include "ALVLedsAsync.h"

void ALVLedsAsync::begin()
{
    Adafruit_NeoPixel::begin(); // Initialize the objects
    Adafruit_NeoPixel::setBrightness(255);
    Adafruit_NeoPixel::show(); // Initialize all pixels to 'off'
}

void ALVLedsAsync::initRace()
{
    this->initRaceAnimation();
}

void ALVLedsAsync::run()
{
}

void ALVLedsAsync::initRaceAnimation()
{
    for (uint8_t i = 0; i < 7; i++)
    {
        // turn on leds with a time spacing of 142 ms
        setPixelColor(i, Color(255, 0, 0));
        show();
        delay(142);
    }
    
    for (uint8_t i = 0; i < 7; i++)
    {
        // turn on leds with a time spacing of 142 ms
        setPixelColor(i, Color(0, 255, 0));
        setPixelColor(i + 7, Color(0, 255, 0));
        show();
        delay(142);
    }

    for (uint8_t i = 0; i < 7; i++)
    {
        // turn on leds with a time spacing of 142 ms
        setPixelColor(i, Color(0, 0, 255));
        setPixelColor(i + 7, Color(0, 0, 255));
        setPixelColor(i + 14, Color(0, 0, 255));
        show();
        delay(142);
    }
}