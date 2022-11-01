#include <stdint.h>
#include <LedPrint.h>

#define N 50
#define INTERVAL 150
class Display
{
public:
    Display();
    ~Display();

    void printMsg(char * msg);
    void flushMsg(char *msg, uint8_t len);
    void stopflush(); 
    void doAnimation();

protected:
    
    LedPrintJustifiable myLed;    
};