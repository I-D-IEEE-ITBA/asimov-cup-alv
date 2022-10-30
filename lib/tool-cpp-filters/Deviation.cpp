#include "Deviation.h"
#include <math.h>

template<typename T> 
void Deviation<T>::write(T val)
{
    write(val, defaultMean());
}

template<typename T>
void Deviation<T>::write(T val, T mean)
{
    dataBuffer[pos++] = val;
    if(pos == bufSize)
        pos = 0;

    double sum = 0;
    double mean_d = (double)mean;
    
    for(unsigned int i=0; i < bufSize; i++)
    {
        double x = (double)dataBuffer[i];
        sum += (x - mean_d) * (x - mean_d);
    }
    
    value = (T)sqrt(sum / bufSize);
}

template <typename T>
T Deviation<T>::defaultMean()
{
    double mean = 0;
    for(unsigned int i=0; i < bufSize; i++)
        mean += (double)dataBuffer[i];

    return (T)(mean / bufSize);
}

template class Deviation<float>;
template class Deviation<double>;
template class Deviation<int>;
template class Deviation<signed char>;
template class Deviation<unsigned char>;
