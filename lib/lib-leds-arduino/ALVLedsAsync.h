#ifndef ALVLEDSASYNC
#define ALVLEDSASYNC

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 8               // Pin of the board
#define NUMLEDS 3
#define TOTALNUMPIXEL NUMLEDS*7 // Total numers of leds

typedef struct
{
    int red;
    int green;
    int blue;

} Color_t;

typedef struct
{
    int iD;
    int startCounter;
    int finishCounter;
    unsigned long previousMillis;
}Led_t;


enum {LEDS_OFF, LEDS_INIT_RACE, LEDS_RACING };

class ALVLedsAsync : public Adafruit_NeoPixel
{
public:
    ALVLedsAsync(uint8_t numLeds, uint8_t dataPin) : Adafruit_NeoPixel(numLeds, dataPin, NEO_GRB + NEO_KHZ800){}
    ~ALVLedsAsync(){}

    void begin();
    void run();
    void initRace();
    void stopRace();

private:

    void initRaceAnimation();

    uint8_t state = LEDS_OFF;

};


#endif // ALVLEDSASYNC