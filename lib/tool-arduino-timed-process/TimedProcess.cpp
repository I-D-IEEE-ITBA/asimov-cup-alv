#include "TimedProcess.h"

void TimedProcess::set(unsigned long interval, void (*c)(void))
{
    if(c != NULL)
    {
        callback = c;
        this->interval = interval;
    }
}