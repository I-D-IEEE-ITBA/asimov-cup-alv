#ifndef Range_H
#define Range_H

// Range Filter implemented with a circular buffer
// Is recommended to use it with a Low Pass Filter

template <typename T>
class Range
{
public:
    Range(unsigned int windowSize)
    {
        bufSize = windowSize;
        dataBuffer = new T[windowSize];

        for(pos=0; pos < bufSize; pos++)
        {
            dataBuffer[pos] = 0;
        }
        pos = 0;
    }
    ~Range()
    {
        delete[] dataBuffer;
    }

    void write(T val);
    inline T read()
    {
        return value;
    }

private:
    T* dataBuffer;    
    T value;
    int bufSize;
    int pos = 0;
};

#endif
