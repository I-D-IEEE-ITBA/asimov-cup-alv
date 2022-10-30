#ifndef SCHMITT_H
#define SCHMITT_H

// Schmitt Trigger emulator (level-activated logic gate)

template <typename T>
class Schmitt
{
public:
    Schmitt(T top, T bottom)
    {
        if(top >= bottom)
        {
            topLevel = top;
            bottomLevel = bottom;
        }
        else
        {
            topLevel = bottom;
            bottomLevel = top;      
            inverted = true;      
        }
    }
    ~Schmitt() {}

    bool filter(T val);

private:
    T topLevel;
    T bottomLevel;
    bool lastState = false;
    bool inverted = false;
};

#endif