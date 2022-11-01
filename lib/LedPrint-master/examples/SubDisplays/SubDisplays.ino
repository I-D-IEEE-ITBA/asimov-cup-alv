/** Splitting into subdisplays, we take aout 8 digit display
 *  and split off the first 3 digits into displayA on which we 
 *  will put some random numbers, and the last 4 digits into 
 *  displayB on which we write some text.
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
    
    LedPrintJustifiable displayA;
    LedPrintJustifiable displayB;
    
    void setup()
    {
      // Set Brightness
      myLed.setIntensity(5);
      
      displayA = myLed.getSubDisplay(0, 3); // First digit 0, 3 digits
      displayB = myLed.getSubDisplay(4, 4); // First digit 5, 3 digits
    }
    
    void loop()
    {
      displayB.println("vlts");

      // Notice that we can write to displayA without messing up displayB
      for(uint8_t x = 0; x<255; x++)
      {
        displayA.println( ((float)random(0,255))/(float)(random(0,100)), 2);
        delay(500);
      }
    }
    
    