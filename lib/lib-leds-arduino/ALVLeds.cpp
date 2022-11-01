#include "ALVLeds.h"

unsigned long previousMillisStartRace = 0; // last time update
unsigned long intervalRed = 2000;          // interval at which to do something (milliseconds)
unsigned long intervalYellow = 4000;
unsigned long intervalGreen = 6000;


/**
 * @brief Construct a new ALVLeds::ALVLeds object
 *
 * @param numPixel Number of pixels of the led's
 * @param pin Number of the Digital Pin where the led's are conected
 */
ALVLeds::ALVLeds(int numPixel, int pin)
{
    pinMode(PIN, INPUT_PULLUP);

    pixels = new Adafruit_NeoPixel(numPixel, pin, NEO_GRB + NEO_KHZ800);

}

ALVLeds::~ALVLeds()
{
    delete pixels;
}

void ALVLeds::begin()
{
    pixels->begin(); // Initialize the objects
    pixels->setBrightness(200);
    pixels->show(); // Initialize all pixels to 'off'

    ledsBegin(leds);
}

/**
 * @brief function to turn off a number of led or all leds
 *
 * @param led: argument of the number of led to bright
 *          led = 0 : all led's
 *          led = 1 , 2 , 3 : numer of the led to bright
 */
void ALVLeds::ledOff(int led = 0)
{
    if (led == 0) // All led to off
    {
        pixels->clear();
        pixels->show();
    }
    else
    {
        for (int i = 6 * (led - 1); i < 6 * led; i++)
        {
            pixels->setPixelColor(i, pixels->Color(0, 0, 0));
            pixels->show();
        }
    }
}

/**
 * @brief function to take control of the color of the led's
 *
 * @param led: argument of the number of led to bright
 *          led = 0 : all led's
 *          led = 1 , 2 , 3 : numer of the led to bright
 */
void ALVLeds::ledToColor(int led, Color_t color)
{
    if (led == 0) // All led to the color
    {
        for (int i = 0; i < TOTALNUMPIXEL; i++)
        {
            pixels->setPixelColor(i, pixels->Color(color.red, color.green, color.blue));
        }
        pixels->show();
    }
    else
    {
        for (int i = 7 * (led - 1); i < 7 * led; i++)
        {
            pixels->setPixelColor(i, pixels->Color(color.red, color.green, color.blue));
        }
        pixels->show();
    }
}

/**
 * @brief Setea un pixel del led de un color en especifico
 * 
 * @param pixel: numero del led a cambiar de color
 * @param color: Recibe el uint32_t del color (usar funcion Color dentro del objeto pixels)
 *                  color = pixels->Color(r , g b);
 */
void ALVLeds::setPixelColor(int pixel, uint32_t color)
{
    pixels->setPixelColor(pixel, color);
    pixels->show();
}

/**
 * @brief Empieza a la animacion de rotacion de los leds
 * 
 * @param led: Numero del led a prender
 * @param color: Color en formato uint32 (Mediante funcion Color(r, g, b) del objeto pixels)
 * @param interval: Intervalo en ms de prendido y apagado de los led's
 * 
 * @return int: Si la animacion termino devuelve 0
 */
int ALVLeds::runSurround(int led, uint32_t color, unsigned long interval)
{
    unsigned long currentMillis = millis();

    if (currentMillis - leds[led - 1].previousMillis > interval && leds[led - 1].startCounter < 7 * led)
    {
        pixels->setPixelColor(leds[led - 1].startCounter++, color);
        pixels->show();

        leds[led - 1].previousMillis = currentMillis;

        return (int)0;
    }
    if (leds[led - 1].startCounter == 7 * led)
    {
        return (int)1;
    }

}

/**
 * @brief Comienza la animacion del semaforo
 * 
 * @return int: Devuelve 0 si la animacion termino
 */
int ALVLeds::startRace()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillisStartRace > intervalRed)
    {
        runSurround(1, pixels->Color(255, 0, 0), 250 );

        if (currentMillis - previousMillisStartRace > intervalYellow)
        {

            runSurround(1, pixels->Color(255, 255, 0), 250);
            runSurround(2, pixels->Color(255, 255, 0), 250);

            if (currentMillis - previousMillisStartRace > intervalGreen)
            {

                runSurround(1, pixels->Color(0, 255, 0), 250);
                runSurround(2, pixels->Color(0, 255, 0), 250);
                runSurround(3, pixels->Color(0, 255, 0), 250);
            }
        }
    }
    if (leds[2].startCounter != 21)
    {
        return (int)1;
    }
    else
    {
        ledOff(0);
        previousMillisStartRace = 0;

        return (int)0;
    }
}

/**
 * @brief Inicializa los leds. Coloca los contadores en cero para cada led
 * 
 * @param leds 
 */
void ALVLeds::ledsBegin(Led_t *leds)
{
    leds[0].iD = 1;
    leds[0].previousMillis = 0;
    leds[0].startCounter = 0;
    leds[0].finishCounter = 7;

    leds[1].iD = 2;
    leds[1].startCounter = 7;
    leds[1].previousMillis = 0;
    leds[2].finishCounter = 14;

    leds[2].iD = 3;
    leds[2].startCounter = 14;
    leds[2].previousMillis = 0;
    leds[0].finishCounter = 21;
}


/**
 * @brief Animacion de loop de los leds
 * Esta animacion se va a reproducir en forma de loop hasta que se llame a la 
 * funcion stopWaiting() el cual desactiva la animacion 
 * 
 * @return int 
 */
void ALVLeds::waiting()
{
    if(wait == true)
    {
        int w1 = runSurround(1, pixels->Color(0, 0, 255), 750);
        int w2 = runSurround(2, pixels->Color(0, 0, 255), 750);
        int w3 = runSurround(3, pixels->Color(0, 0, 255), 750);

        Serial.print(w1);

        if(w2 == 1 || w3 == 1)
        {
            ledsBegin(leds);
            ledOff(0);
        }
    }
    else
    {
        ledOff(0);
    }
}

void ALVLeds::stopWaiting()
{
    wait = false;
}
