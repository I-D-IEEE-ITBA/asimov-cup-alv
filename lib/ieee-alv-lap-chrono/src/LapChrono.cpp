#include "LapChrono.h"

LapChrono::LapChrono()
{
}

LapChrono::~LapChrono()
{
    delete[] lapTimestamp;
}

void LapChrono::setMaxLaps(uint8_t laps)
{
    maxLaps = laps + 1;
    if(lapTimestamp)
        delete[] lapTimestamp;

    lapTimestamp = new unsigned long [laps + 1];

    for(int i=0; i< laps+1 ; i++)
        lapTimestamp[i] = 0;
    
    lapCount = 0;
    stop();
}

// chronometer control functions
void LapChrono::stop() // force stop
{
    chronoState = ChronoStop;
}

bool LapChrono::isStop()
{ 
    return chronoState == ChronoStop;
}

void LapChrono::finish()
{
    chronoState = ChronoFinished;
}

void LapChrono::start()
{
    chronoState = ChronoRunning;
    lapCount = 0;    
}


bool LapChrono::isRacing() 
{ 
    return (chronoState == ChronoRunning); 
}

bool LapChrono::finished() 
{ 
    return (chronoState == ChronoFinished); 
}

uint8_t LapChrono::currentLap()
{ 
    return lapCount;
}

unsigned long LapChrono::getLapTimestampMS(uint8_t lap)
{
    if(lapTimestamp != NULL && lap < lapCount)
    {
        return lapTimestamp[lap];
    }
    return 999999999UL;
}