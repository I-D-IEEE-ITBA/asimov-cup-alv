#include "Display.h"
#include <string.h>


static LedPrintJustifiable * led;
static bool newflush;
static uint8_t length;
static char text[N];
static int k=0;

Display::Display(int data, int clk, int cs, int pin): myLed(data, clk, cs, pin){ // 13 = data_in , 10 = clk, 11 = cs, 8 = number of digits
  myLed.setIntensity(5); // Set Brightness
  myLed.justify(-1); // Left justify

  cli();                      //stop interrupts for till we make the settings
  /*1. First we reset the control register to amke sure we start with everything disabled.*/
  TCCR1A = 0;                 // Reset entire TCCR1A to 0 
  TCCR1B = 0;                 // Reset entire TCCR1B to 0
 
  /*2. We set the prescalar to the desired value by changing the CS10 CS12 and CS12 bits. */  
  TCCR1B |= B00000100;        //Set CS12 to 1 so we get prescalar 256  
  
  /*3. We enable compare match mode on register A*/
  TIMSK1 |= B00000010;        //Set OCIE1A to 1 so we enable compare match A 
  
  /*4. Set the value of register A to 31250*/
  OCR1A = 31250;             //Finally we set compare register A to this value  
  sei();                     //Enable back the interrupts
  
  led=&myLed;
}  
Display::~Display(){

}

void Display::printMsg(const char * msg){
  myLed.clear();
  myLed.println(msg);  
}

void Display::flushMsg(const char *msg, uint8_t len){  
  memcpy(text+8, msg, len);
  for (int i=0;i<8;i++){
    text[i]=' ';    
  }
  for (int i=0;i<8;i++){
    text[len+8+i]=' ';
  } 
  length=len;
  myLed.clear();
  k=0;   
  newflush=true;

}; 

void Display::stopflush(){
  newflush=false;
  myLed.clear(); 
} 

void Display::printTime(unsigned long time)
{
  float timeF = (time)/1000.0f;
  myLed.println(timeF,1);
}

void Display::doAnimation(){
  flushMsg(" ", 1); //clear
  flushMsg("IEEE - ItBA",11);
}


ISR(TIMER1_COMPA_vect){
  static unsigned long previousMillis = 0;  // will store last time LED was updated
  unsigned long currentMillis = millis();
  
  char printTxt[8];
  if ((unsigned long)(currentMillis - previousMillis) >= INTERVAL){
    previousMillis = currentMillis;
    if(newflush){
      for (int i=0;i<8;i++){
        printTxt[i]=text[i+k];      
      }
      led->println(printTxt);
      k++;
      if (k==length+8){
        k=0;
      }
    }
    else{
      k=0;
    }
  }

}