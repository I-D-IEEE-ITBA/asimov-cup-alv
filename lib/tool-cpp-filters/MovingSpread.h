#ifndef MovingSpread_H
#define MovingSpread_H

// Moving Spread Filter (Constant O(1) real-time discrete spread calculator)


template <typename T>
class MovingSpread
{
public:
    /**
     * @brief Construct a new Moving Spread object
     * 
     * @param s sustain = value between 0 and 1
     * @param g gain = positive value, default 1
     */
    MovingSpread(float s, float g = 1.0f)
    {
        if(s > 0 && s < 1)
        {
            sustain = s;
        }
        else
        {
            sustain = 0.6f; // default value
        }
        gain = g;
        lastValue = 0;
        spreadAccumulator = 0;
    }
    ~MovingSpread(){}

    void write(T val);
    
    inline T read()
    {
        return (T)spreadAccumulator;
    }

private:
    T lastValue;

    float gain;
    float sustain;
    double spreadAccumulator;
};

#endif
