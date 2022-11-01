/** Simple Hello World exmaple.
 *
 */

    #include <LedPrint.h>
    
    LedPrintJustifiable myLed = LedPrintJustifiable
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
      
      // Center justify (0), alternatives -1 for left and 1 for right
      myLed.justify(0);
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