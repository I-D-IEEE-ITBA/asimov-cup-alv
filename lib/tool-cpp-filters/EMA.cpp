#include "EMA.h"

template<typename T> 
void EMA<T>::write(T newval)
{
    value = value + alpha * (((double)newval) - value);
}

template class EMA<float>;
template class EMA<double>;
template class EMA<int>;
template class EMA<unsigned char>;
template class EMA<char>;
