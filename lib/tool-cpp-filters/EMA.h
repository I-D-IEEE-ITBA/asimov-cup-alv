#ifndef EMA_H
#define EMA_H

// Exponential Moving Average (EMA) Filter
// https://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average

template <typename T>
class EMA
{
public:
    EMA(float a) // alpha is a value between 0 and 1
    {
        if(a > 0 && a < 1)
        {
            alpha = a;
        }
        else
        {
            alpha = 0.3f; // default value
        }
        value = 0;
    }
    ~EMA(){}

    void write(T val);
    
    inline T read()
    {
        return (T)value;
    }

private:
    float alpha;
    double value;
};

#endif
