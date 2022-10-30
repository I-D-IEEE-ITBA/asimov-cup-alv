#ifndef LAPCHRONO_H
#define LAPCHRONO_H

#include <stdint.h>
#include <stdlib.h>
#include <Arduino.h>

enum ChronometerState
{
    ChronoStop,
    ChronoRunning,
    ChronoFinished,
};

class LapChrono
{
public:
    LapChrono();
    ~LapChrono();

    void setMaxLaps(uint8_t laps);

    // chronometer control functions
    void stop();    // force stop
    void finish();  // force finish
    void start();   // start chronometer

    void lap();     // timestamp a lap

    bool isStop();
    bool isRacing();
    bool finished();

    uint8_t currentLap(); // Get number of current lap

    unsigned long getLapTimestampMS(uint8_t lap);

protected:
    
    uint8_t lapCount = 0;
    unsigned long* lapTimestamp = NULL;
    
    uint8_t chronoState = ChronoStop;

    uint8_t maxLaps = 0;
};

inline void LapChrono::lap()
{
    if(lapTimestamp == NULL)
    {
        return;
    }
    switch (chronoState)
    {
    case ChronoRunning:
        lapTimestamp[lapCount] = millis();
        lapCount++;
        if(lapCount >= maxLaps)
        {
            chronoState = ChronoFinished;
        }
        break;

    case ChronoFinished:
    case ChronoStop:
    default:
        break; // do nothing
    }
}


#endif