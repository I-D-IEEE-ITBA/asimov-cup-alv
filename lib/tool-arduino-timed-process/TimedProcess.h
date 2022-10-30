#ifndef _INTERVAL_H_
#define _INTERVAL_H_

#include <Arduino.h>

/**
 * @brief TimedProcess base class, must define getTime method
 * 
 */
class TimedProcess
{
public:
    TimedProcess()
    {
        callback = NULL;
        lastTime = 0;
    }

    /**
     * @brief Set interval callback
     * 
     * @param c Void Callback function to be called every <interval> time 
     * @param interval time period to periodically call back
     */
    void set(unsigned long interval, void (*c)(void));

    /**
     * @brief Run the interval (non-blocking). Should be called inside real time loops
     * 
     */
    inline void run();

protected:
    virtual unsigned long getTime() = 0;

private:
    unsigned long lastTime;
    unsigned long interval;
    void (*callback)(void);
};

inline void TimedProcess::run()
{
    unsigned long time = getTime();
    if(time - lastTime >= interval)
    {
        if( callback != NULL)
            callback();
            
        lastTime = time;
    }
}


class TimedProcessMicros : public TimedProcess
{
public:
    TimedProcessMicros() {}
protected:
    virtual inline unsigned long getTime() { return micros(); }
};


class TimedProcessMillis : public TimedProcess
{
public:
    TimedProcessMillis() {}
protected:
    virtual inline unsigned long getTime() { return millis(); }
};

#endif