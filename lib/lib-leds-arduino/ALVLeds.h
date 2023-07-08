/*
    Library for de LED's Rgb 5050 Ws2812 Neopixel
    Requeriments:
        Adafruit_NeoPixel: https://github.com/adafruit/Adafruit_NeoPixel
*/
#ifndef ALVLEDS
#define ALVLEDS


#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 8               // Pin of the board
#define NUMLEDS 3
#define TOTALNUMPIXEL NUMLEDS*7 // Total numers of leds

#define COLOR(r , g , b) leds->pixels->Color(r,g,b)

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




class ALVLeds
{
private:
    // Vars


public:
    ALVLeds(int numPixel, int pin);
    ~ALVLeds();

    Adafruit_NeoPixel *pixels;

    //Led's Data
    Led_t leds[NUMLEDS];

    void begin();

    //Auxiliar Functions
    int runSurround(int led, uint32_t color, unsigned long interval); // led go from 1 to 3 // led = 0 -> (all leds)
    void setPixelColor(int pixel, uint32_t color);
    void ledOff(int led);
    void ledToColor(int led, Color_t color);
    void ledsBegin(Led_t* leds);

    //ALV Functions
    int startRace();
    void waiting();
    void stopWaiting();

};

#endif

