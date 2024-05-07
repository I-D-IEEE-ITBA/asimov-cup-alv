#include <stdint.h>
#include <LedPrint.h>

#define N 50
#define INTERVAL 150
class Display
{
public:
    Display(int data, int clk, int cs, int pin);
    ~Display();

    void printMsg(const char * msg);
    void printTime(unsigned long time);
    void flushMsg(const char *msg, uint8_t len);
    void stopflush(); 
    void doAnimation();

protected:
    
    LedPrintJustifiable myLed;    
};