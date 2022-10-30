#include "SMA.h"

template<typename T> 
void SMA<T>::write(T val)
{
    dataBuffer[pos++] = val;
    if(pos == bufSize)
        pos = 0;

    double sum = 0;
    for(int i=0; i < bufSize; i++)
    {
        sum += (double)dataBuffer[i];
    }
    value = (T)(sum / bufSize);
}

template class SMA<float>;
template class SMA<double>;
template class SMA<int>;
template class SMA<signed char>;
template class SMA<unsigned char>;