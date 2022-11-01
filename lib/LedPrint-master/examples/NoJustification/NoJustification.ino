/** If you only need left-justification, you can use the LedPrint 
 *  class instead of LedPrintJustifiable, it will use slightly less
 *  memory.
 *
 */

    #include <LedPrint.h>
    
    LedPrint myLed = LedPrint
      (
        11, // DATA PIN
        13, // CLOCK PIN
        10, // CS PIN
        8,  // NUMBER OF DIGITS
        1   // Orientation 0/1, if it looks backwards try the other
      );
    
    void setup()
    {
      // Set Brightness
      myLed.setIntensity(5);
      
    }
    
    void loop()
    {
      myLed.println("Hello");
      delay(3000);

      myLed.println("Earth");
      delay(3000);

      myLed.clear();
      delay(2000);      
    }