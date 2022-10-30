#ifndef Deviation_H
#define Deviation_H

// Deviation Filter implemented with a circular buffer

template <typename T>
class Deviation
{
public:
    Deviation(unsigned int windowSize)
    {
        bufSize = windowSize;
        dataBuffer = new T[windowSize];

        for(pos=0; pos < bufSize; pos++)
        {
            dataBuffer[pos] = 0;
        }
        pos = 0;
    }
    ~Deviation()
    {
        delete[] dataBuffer;
    }

    void write(T val);
    void write(T val, T mean);
    inline T read()
    {
        return value;
    }

private:
    T* dataBuffer;   
    T value; 
    unsigned int bufSize;
    unsigned int pos = 0;

    T defaultMean();
};

#endif