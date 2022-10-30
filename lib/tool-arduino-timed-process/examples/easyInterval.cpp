#include <Arduino.h>

#include "TimedProcess.h"

TimedProcessMillis blinkLoop;
TimedProcessMillis loop_1s;
bool ledState = false;

void loopEverySec();

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);

    blinkLoop.set(300, [](){
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState);
    });

    loop_1s.set(1000, loopEverySec);
}

void loop()
{
    // Non-blocking (async) intervals
    blinkLoop.run();
    loop_1s.run();
}


void loopEverySec()
{
    Serial.println(F("Loop!"));
}