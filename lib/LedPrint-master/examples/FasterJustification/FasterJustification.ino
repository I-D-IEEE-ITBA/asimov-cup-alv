/** Easy justification can be a bit slow (or rather if you make the update rate fast it will look bad) 
 *  if you need a faster update rate you can use sprint to pre-justify your strings manually
 *  and then just pass them in directly so no justification jiggery pokery is done on the display.
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
     
      // Print some numbers right justified with zero pad
      myLed.justify(-1);
      myLed.println("Easy but"); delay(1500);
      myLed.println("Slow and"); delay(1500);
      myLed.println("blurry.."); delay(1500);
      
      
      // Slow easy method...
      // ==================================================
      myLed.justify(1, 0);
      for(uint8_t x = 1; x < 100; x++)
      {
        myLed.println(x); delay(100);
      }
      // ==================================================
      
      
      myLed.justify(-1);
      myLed.println("Hard but"); delay(1500);
      myLed.println("fast and"); delay(1500);
      myLed.println("clear..."); delay(1500);
      
      // Fast tricksy method...
      // ==================================================
      myLed.justify(-1); // disable justification (left justify)
      char buf[9];       // a buffer
      for(uint8_t x = 1; x < 100; x++)
      {
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%08d", x);
        myLed.println(buf); delay(50);
      }
      // ==================================================
      
      
      
    }