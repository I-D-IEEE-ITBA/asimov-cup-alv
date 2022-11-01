/** Printing numbers
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
      
    }
    
    void loop()
    {
     
      // Print some numbers left justified
      myLed.justify(-1);
      for(uint8_t x = 1; x < 100; x++)
      {
        myLed.println(x); delay(20);
      }
      
      // Print some numbers center justified
      myLed.justify(0);
      for(uint8_t x = 1; x < 100; x++)
      {
        myLed.println(x); delay(20);
      }
      
      // Print some numbers right justified
      myLed.justify(1);
      for(uint8_t x = 1; x < 100; x++)
      {
        myLed.println(x); delay(20);
      }
      
      // Print some numbers right justified with zero pad
      myLed.justify(1, 0);
      for(uint8_t x = 1; x < 100; x+=9)
      {
        // because of the way the justification works
        // this needs to happen a bit slower so that it doesn't
        // have too much bleed-through of the zero padding when
        // the characters are shifted in
        myLed.println(x); delay(500);
      }
      
      // Print some floating point numbers on the right, to 2 decimal places
      myLed.justify(1);
      for(uint8_t x = 1; x < 20; x++)
      {
        myLed.println((float)(random(0,99999999))/((float)(random(0,9999999))),2); delay(500);
      }
    }