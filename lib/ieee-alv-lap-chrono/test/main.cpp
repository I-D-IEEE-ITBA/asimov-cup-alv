#include <iostream>

#include "../src/LapChrono.h"

class LapChronoTest : public LapChrono
{
public:
    LapChronoTest(uint8_t laps) : LapChrono(laps) {}
    ~LapChronoTest();

    unsigned long virtualTime = 0;

protected:
    virtual unsigned long timeProvider()
    {
        return virtualTime;
    };
};

using namespace std;

LapChronoTest lap(3);

int main(int, char**) {

    lap.setLapDistanceCM(60);

    lap.start();
/* code */

    lap.virtualTime = 1400;
    while (lap.isRacing())
    {
        lap.virtualTime *= 2;
        lap.lap();
    }
    

    std::cout << "Hello, world!\n";
}
