#ifndef ALVLEDSASYNC
#define ALVLEDSASYNC

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define BUZZER_PIN 9

class ALVLedsAsync : public Adafruit_NeoPixel
{
public:
    ALVLedsAsync(uint8_t numLeds, uint8_t dataPin) : Adafruit_NeoPixel(numLeds, dataPin, NEO_GRB + NEO_KHZ800){}
    ~ALVLedsAsync(){}

    void begin();
    void run();
    void initRace();

private:

    void initRaceAnimation();

    unsigned long lastMs = 0;
    uint8_t led_idx = 0;
};

#endif // ALVLEDSASYNC