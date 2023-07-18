#include "ALVLedsAsync.h"

void ALVLedsAsync::begin()
{
    Adafruit_NeoPixel::begin(); // Initialize the objects
    Adafruit_NeoPixel::setBrightness(255);
    Adafruit_NeoPixel::show(); // Initialize all pixels to 'off'
    pinMode(9, OUTPUT); // Buzzer

}

void ALVLedsAsync::initRace()
{
    this->initRaceAnimation();
}

void ALVLedsAsync::run()
{
    // Intervalo
    if (millis() - lastMs < 100)
    {
        if (led_idx >= 6)
        {
            led_idx = 0;
        }

        setPixelColor(i, Color(0, 0, 255));
        setPixelColor(i + 7, Color(0, 0, 255));
        setPixelColor(i + 14, Color(0, 0, 255));

        led_idx++;
        lastMs = millis();
    }
}

void ALVLedsAsync::initRaceAnimation()
{
    clear();
    digitalWrite(9, HIGH);
    for (uint8_t i = 0; i < 7; i++)
    {
        // turn on leds with a time spacing of 142 ms
        setPixelColor(i + 14, Color(255, 0, 0));
        show();
        delay(142);
        digitalWrite(9, LOW);
    }
    clear();
    digitalWrite(9, HIGH);

    for (uint8_t i = 0; i < 7; i++)
    {
        // turn on leds with a time spacing of 142 ms
        setPixelColor(i + 14, Color(255, 200, 0));
        setPixelColor(i + 7, Color(255, 200, 0));
        show();
        delay(142);
        digitalWrite(9, LOW);
    }
    clear();
    digitalWrite(9, HIGH);

    for (uint8_t i = 0; i < 7; i++)
    {
        // turn on leds with a time spacing of 142 ms
        setPixelColor(i, Color(0, 255, 0));
        setPixelColor(i + 7, Color(0, 255, 0));
        setPixelColor(i + 14, Color(0, 255, 0));
        show();
        delay(142);
        digitalWrite(9, LOW);
    }
    clear();
    show();

    digitalWrite(9, HIGH);
    delay(400);
    digitalWrite(9, LOW);
}