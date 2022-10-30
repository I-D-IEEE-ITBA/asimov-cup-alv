#include "TMA.h"

template<typename T> 
void TMA<T>::write(T val)
{
    filter1->write(val);
    filter2->write(filter1->read());
}

template <typename T>
T TMA<T>::read()
{
    return filter2->read();
}

template class TMA<float>;
template class TMA<double>;
template class TMA<int>;
template class TMA<signed char>;
template class TMA<unsigned char>;