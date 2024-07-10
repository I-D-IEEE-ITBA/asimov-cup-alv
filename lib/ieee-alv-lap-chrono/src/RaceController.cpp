#include "RaceController.h"

RaceController::RaceController()
{
}

RaceController::~RaceController()
{
}

void RaceController::setupRace(uint8_t laps, unsigned int lapDistance)
{
    maxLaps = laps;
    this->lapDistance = lapDistance;
    chrono[0].setMaxLaps(laps);
    chrono[1].setMaxLaps(laps);
}

void RaceController::prepareRace()
{
    winnerID = -1;
    raceState = RaceStarting;
}

void RaceController::startRace()
{
    chrono[0].start();
    chrono[1].start();
    startTimestamp_ms = millis();
    raceState = RaceRunning;
}

void RaceController::run()
{
    bool raceFinishedFlag = false;
    for (uint8_t i = 0; i < 2; i++)
    {
        raceFinishedFlag |= chrono[i].finished();
        if (chrono[i].finished() && (winnerID == -1))
        {
            winnerID = i;
        }
    }

    if (raceFinishedFlag)
    {
        chrono[0].finish();
        chrono[1].finish();
        raceState = RaceFinished;
    }
}

unsigned long RaceController::getTime()
{
    if (!active() || raceState == RaceStarting)
        return 0;

    return (millis() - startTimestamp_ms);
}


int RaceController::winner()
{
    if (winnerID == -1)
    {
        return 404;
    }
    return winnerID + 1; // start with 1
}

void RaceController::showResults()
{
    Serial.println(F("LAP\tP1\tP2"));
    for (uint8_t i = 0; i < maxLaps+1; i++)
    {
        Serial.print(i);
        Serial.print('\t');
        Serial.print((chrono[0].getLapTimestampMS(i) - startTimestamp_ms) / 1000.0f, 3);
        Serial.print('\t');
        Serial.println((chrono[1].getLapTimestampMS(i) - startTimestamp_ms) / 1000.0f, 3);
    }
}

void RaceController::showWinnerStats(int &winID, unsigned long& winTime)
{
    if (winnerID != -1)
    {
        Serial.print(F("Winner is: Player"));
        Serial.println(winnerID + 1);
        winID = winnerID + 1;

        Serial.print(F("\tmean time per lap: "));
        unsigned long totalTime = chrono[winnerID].getLapTimestampMS(maxLaps) - startTimestamp_ms;
        winTime = totalTime/10UL;
        Serial.print(totalTime / (1000.0f * maxLaps), 3);
        Serial.println(F(" s"));

        Serial.print(F("\tmean speed: "));
        Serial.print(((maxLaps * 1000UL) * lapDistance) / totalTime);
        Serial.println(F(" cm / s"));
    }
}