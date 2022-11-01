/** Shows the difference between print and println
 * 
 * In short, println causes the next thing you print (or println) 
 * to clear the display first, while print does not, basically 
 * think of your display as alwasys showing the last line, and just 
 * like with Serial you can build on that line with print.
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
      myLed.println("print"); delay(1500);

      myLed.print('h'); delay(500);
      myLed.print('e'); delay(500);
      myLed.print('l'); delay(500);
      myLed.print('l'); delay(500);
      myLed.print('o'); delay(500);
      myLed.println();
      
      myLed.println("println"); delay(1500);

      myLed.println('h'); delay(500);
      myLed.println('e'); delay(500);
      myLed.println('l'); delay(500);
      myLed.println('l'); delay(500);
      myLed.println('o'); delay(500);
      myLed.println();
      
      
    }