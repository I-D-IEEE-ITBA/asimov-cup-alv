#include "MovingSpread.h"

template<typename T> 
void MovingSpread<T>::write(T newval)
{
    double spread = (lastValue - ((double)newval));
    spread = (spread>=0)? spread : (-spread);
    
    spreadAccumulator = spreadAccumulator * sustain + spread * gain;
    lastValue = newval;
}

template class MovingSpread<float>;
template class MovingSpread<double>;
template class MovingSpread<int>;
template class MovingSpread<unsigned char>;
template class MovingSpread<signed char>;
