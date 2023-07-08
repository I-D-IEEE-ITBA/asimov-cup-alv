#include "Display.h"
#include <LedPrint.h>

Display mydisp;

void setup()
{
  
}

void loop()
{
 
  mydisp.printMsg("Hola");
  delay(3000);
  
  mydisp.flushMsg("Hello earth", 11);
  delay(3000);
  
  mydisp.stopflush();
  delay(3000);
  
  mydisp.flushMsg("Bye", 3);
  delay(3000);

  mydisp.doAnimation();
  delay(3000);

  mydisp.stopflush();
  delay(3000);  
}