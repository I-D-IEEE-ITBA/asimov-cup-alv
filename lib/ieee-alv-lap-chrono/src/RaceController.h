#ifndef RACECONTROLLER_H
#define RACECONTROLLER_H

#include <Arduino.h>
#include "LapChrono.h"
#include "ALVLeds.h"


enum RaceState
{
    RaceInactive,
    RaceStarting,
    RaceRunning,
    RaceFinished,
};

class RaceController
{
public:
    RaceController();
    ~RaceController();

    void setupRace(uint8_t laps, unsigned int lapDistance = 1);

    void startRace();

    void lap(uint8_t id);

    bool active();
    bool finished();

    void showResults();
    void showWinnerStats(int &winID, unsigned long& winTime);

    int winner();

    // Stop all (chronometers & animations)
    void stop()
    {
        raceState = RaceInactive;
        chrono[0].finish();
        chrono[1].finish();
    }

    void run();
    
    unsigned long getTime();

private:

    LapChrono chrono[2];
    
    uint8_t raceState = RaceInactive;

    unsigned int lapDistance;
    uint8_t maxLaps = 0;

    int8_t winnerID = -1;

    unsigned long startTimestamp_ms = 0;
};

inline bool RaceController::active()
{
    return (raceState == RaceRunning) || (raceState == RaceStarting);
}

inline bool RaceController::finished()
{
    return (raceState == RaceFinished);
}

inline void RaceController::lap(uint8_t id)
{
    chrono[id].lap();    
}

#endif