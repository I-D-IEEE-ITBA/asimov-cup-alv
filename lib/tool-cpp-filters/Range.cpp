#include "Range.h"

template<typename T> 
void Range<T>::write(T val)
{
    dataBuffer[pos++] = val;
    if(pos == bufSize)
        pos = 0;

    T max = dataBuffer[0];
    T min = dataBuffer[0];
    
    for(int i=1; i < bufSize; i++)
    {
        if(dataBuffer[i] > max)
            max = dataBuffer[i];
        if(dataBuffer[i] < min)
            min = dataBuffer[i];
    }
    value = (max - min);
}

template class Range<float>;
template class Range<double>;
template class Range<int>;
template class Range<signed char>;
template class Range<unsigned char>;
