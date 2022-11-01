# LedPrint

An Arduino library for simple Arduino Print style use of 7-segment displays in Arduino using the MAX7219 and MAX7221 Led Display Drivers facilitating printing numbers, and appropriate letters to 7-segment displays, splitting displays into sub displays, and chaining drivers.

Derived from, and including, a modified [LedControl](http://wayoda.github.io/LedControl/) library.

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [LedPrint](#ledprint)
  - [Features](#features)
  - [Download, Install and Example](#download-install-and-example)
  - [Simple Example](#simple-example)
  - [Full Class Reference](#full-class-reference)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Features

  Printing pretty much anything works the same as it would for, for example, Serial, since LedPrint derives from [Print class just like Serial does](https://www.arduino.cc/en/Serial/Print).
  
    // Strings
    myDisplay.println("Hello");
    
    // Flash strings
    myDisplay.println(F("EARTH"));
    
    // Integers
    myDisplay.println(123);
    
    // Floats
    myDisplay.println(5.345, 3); // 3 dp
  
    // Hex
    myDisplay.println(456, HEX);
    
    // Combining things
    myDisplay.print(3);
    myDisplay.println(" Volts");
    
    // etc...
    
  Using the special type LedPrintJustifiable we can justify our prints to the right or center
  
    LedPrintJustifiable myDisplay = LedPrintJustifiable(11, 13, 10, 8); // 11 = data, 13 = clk, 10 = cs, 8 = number of digits
    
    // Justify Left (default)
    myDisplay.justify(-1);
    myDisplay.println("Hello");
    
    // Justify Right (1)
    myDisplay.justify(1);
    myDisplay.println(F("Earth"));
  
    // Center Justify (0)
    myDisplay.justify(0);
    myDisplay.println("Arduino");
    
    // Right justification with 0 padding
    myDisplay.justify(1,0);
    myDisplay.print(12);
    
  Note that justification is fairly suboptimal, but works OK for typical update rates.
  
  You can create sub-displays from your main display, that is you could split an 8 digit display into two 4 digit ones...
  
    LedPrint displayA = myDisplay.getSubDisplay(0, 4); // 0 = first digit, 4 = number of digits
    LedPrint displayB = myDisplay.getSubDisplay(4, 4); // 4 = first digit, 4 = number of digits
  
  thereafter you can print to those sub displays
  
  Note that  the sub displays don't have to be contiguous, for example an 8 digit display made into a 3 digit one and a 2 digit one, the first 3 digits and the last 2 digits
  
    LedPrint displayA = myDisplay.getSubDisplay(0, 3); // 0 = first digit, 3 = number of digits
    LedPrint displayB = myDisplay.getSubDisplay(6, 2); // 6 = first digit, 2 = number of digits
    
  Displays or sub-displays can be cleared
  
    displayB.clear();
    
  Intensity adjusted for the entire display (not individual subdisplays)
  
    myDisplay.setIntensity(7);
    
  The entire display can be shutdown
  
    myDisplay.shutdown();
    
  Or restarted
  
    myDisplay.shutdown(false);
    
## Download, Install and Example

* Download: http://sparks.gogo.co.nz/LedPrint.zip
* Open the Arduino IDE (this library was tested in 1.8.5, older versions may work)
* Select the menu item Sketch > Import Library > Add Library
* Choose to install the LedPrint.zip file you downloaded
* Now you can choose File > Examples > LedPrint > HelloWorld

Upload the example to your Arduino and stand back in awe of the results. 
  
## Simple Example

An 8 digit 7-segment Max7219 display is connected to pins 11 (data), 13 (clk), and 10 (chip select) of an Arduino, we print a message center-justified...

    #include <LedPrint.h>
    
    LedPrintJustifiable myLed = LedPrintJustifiable(11, 13, 10, 8); // 11 = data, 13 = clk, 10 = cs, 8 = number of digits
    
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
    

## Full Class Reference

I recommend to just look at the examples which show you how to use all the features, but if you want the nitty-gritty then here is the [full class reference](https://rawcdn.githack.com/sleemanj/LedPrint/be0d4be7943a2f60188f92e1efde4d1307e922f4/docs/html/class_led_print.html)

Docs served by http://raw.githack.com/
