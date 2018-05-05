#include <LedControl.h>
#include <binary.h>


//Create single LedControl
LedControl lc = LedControl(13,12,11,1);

int defaultDelay = 500;

void setup() {
  //Wake up
  lc.shutdown(0, false);

  lc.setIntensity(0, 1); //00..15 Brightness levels

  lc.clearDisplay(0);
}

void loop() {
  lc.clearDisplay(0);
  delay(500);
  //switch on the led in the 3'rd row 8'th column
  lc.setLed(0,2,7,true);   

  //Led at row 0 second from left too
  lc.setLed(0,0,1,true);   
  delay(500);
  
  //switch the first Led off (second one stays on)
  lc.setLed(0,2,7,false); 
  delay(500);
  
  //Lit a Row value
  lc.setRow(0,2,B10110000);
  
  delay(500);

  //Lit a Column value
  lc.setColumn(0,5,B00001111);

  delay(500);

  writeA();
  writeEmoHappy();

}

void writeA() {
  lc.setRow(0, 0, B01111110);
  lc.setRow(0, 1, B10000001);
  lc.setRow(0, 2, B10000001);
  lc.setRow(0, 3, B10000001);
  lc.setRow(0, 4, B11111111);
  lc.setRow(0, 5, B10000001);
  lc.setRow(0, 6, B10000001);
  lc.setRow(0, 7, B10000001);
  delay(defaultDelay);
}

void writeEmoHappy() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B01000100);
  lc.setRow(0, 2, B00000000);
  lc.setRow(0, 3, B00010000);
  lc.setRow(0, 4, B00000000);
  lc.setRow(0, 5, B01000100);
  lc.setRow(0, 6, B00111000);
  lc.setRow(0, 7, B00000000);
  delay(defaultDelay);
 }
