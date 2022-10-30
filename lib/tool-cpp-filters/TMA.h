#ifndef TMA_H
#define TMA_H

// Triangular Moving Average (TMA) Filter
#include "SMA.h"

template <typename T>
class TMA
{
public:
    TMA(unsigned int firstWindowSize, unsigned int secondWindowSize)
    {
        filter1 = new SMA<T>(firstWindowSize);
        filter2 = new SMA<T>(secondWindowSize);
    }
    ~TMA()
    {
        delete filter1;
        delete filter2;
    }

    void write(T val);
    T read();

private:
    SMA<T>* filter1;    
    SMA<T>* filter2;
};

#endif