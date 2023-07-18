#include "ALVLedsAsync.h"

void ALVLedsAsync::begin()
{
    Adafruit_NeoPixel::begin(); // Initialize the objects
    Adafruit_NeoPixel::setBrightness(255);
    Adafruit_NeoPixel::show(); // Initialize all pixels to 'off'
    pinMode(BUZZER_PIN, OUTPUT); // Buzzer

}

void ALVLedsAsync::initRace()
{
    this->initRaceAnimation();
}

void ALVLedsAsync::run()
{
    // Intervalo
    if (millis() - lastMs >= 100)
    {
        if (led_idx >= 7)
        {
            led_idx = 0;
            clear();
        }

        setPixelColor(led_idx, Color(0, 0, 255));
        setPixelColor(led_idx + 7, Color(0, 0, 255));
        setPixelColor(led_idx + 14, Color(0, 0, 255));

        show();
        led_idx++;
        lastMs = millis();
    }
}

void ALVLedsAsync::initRaceAnimation()
{
    clear();
    digitalWrite(BUZZER_PIN, HIGH);
    for (uint8_t i = 0; i < 7; i++)
    {
        // turn on leds with a time spacing of 142 ms
        setPixelColor(i + 14, Color(255, 0, 0));
        show();
        delay(142);
        digitalWrite(BUZZER_PIN, LOW);
    }
    clear();
    digitalWrite(BUZZER_PIN, HIGH);

    for (uint8_t i = 0; i < 7; i++)
    {
        // turn on leds with a time spacing of 142 ms
        setPixelColor(i + 14, Color(255, 200, 0));
        setPixelColor(i + 7, Color(255, 200, 0));
        show();
        delay(142);
        digitalWrite(BUZZER_PIN, LOW);
    }
    clear();
    digitalWrite(BUZZER_PIN, HIGH);

    for (uint8_t i = 0; i < 7; i++)
    {
        // turn on leds with a time spacing of 142 ms
        setPixelColor(i, Color(0, 255, 0));
        setPixelColor(i + 7, Color(0, 255, 0));
        setPixelColor(i + 14, Color(0, 255, 0));
        show();
        delay(142);
        digitalWrite(BUZZER_PIN, LOW);
    }
    clear();
    show();

    digitalWrite(BUZZER_PIN, HIGH);
    delay(400);
    digitalWrite(BUZZER_PIN, LOW);

    led_idx = 0;
}