#include <LedControl.h>

//Create single LedControl
LedControl lc = LedControl(13,12,11,1);

int delaytime = 500;
int intensity = 1;

unsigned char disp1[38][8]={
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},  //0
{0x8,0x18,0x28,0x8,0x8,0x8,0x8,0x8},        //1
{0x7E,0x2,0x2,0x7E,0x40,0x40,0x40,0x7E},    //2
{0x3E,0x2,0x2,0x3E,0x2,0x2,0x3E,0x0},       //3
{0x8,0x18,0x28,0x48,0xFE,0x8,0x8,0x8},      //4
{0x3C,0x20,0x20,0x3C,0x4,0x4,0x3C,0x0},     //5
{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x0},   //6
{0x3E,0x22,0x4,0x8,0x8,0x8,0x8,0x8},        //7
{0x0,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},   //8
{0x3E,0x22,0x22,0x3E,0x2,0x2,0x2,0x3E},     //9
{0x8,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},   //A
{0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x0},   //B
{0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x0},   //C
{0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x0},   //D
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},  //E
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},    //F
{0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
{0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//H
{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
{0x3C,0x8,0x8,0x8,0x8,0x8,0x48,0x30},//J
{0x0,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
{0x0,0x42,0x62,0x52,0x4A,0x46,0x42,0x0},//N
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
{0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},//P
{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
{0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},//S
{0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8},//T
{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
{0x0,0x49,0x49,0x49,0x49,0x2A,0x1C,0x0},//W
{0x0,0x41,0x22,0x14,0x8,0x14,0x22,0x41},//X
{0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},//Y
{0x0,0x7F,0x2,0x4,0x8,0x10,0x20,0x7F},//Z
};

void setup() {  
  lc.shutdown(0, false);//Wake up
  lc.setIntensity(0, 1); //00..15 Brightness levels
  lc.clearDisplay(0);
}

void loop() {
  
  lc.clearDisplay(0);
  intensity += 2;
  lc.setIntensity(0, 8);
  
  
  delay(delaytime); 
  
  /*writeEmoHappy();
  writeEmoBad();
  writeEmoSad();
  writeEmoAmazing();  
  writeEmoIllusion();
  writeEmoHeart();
  writeOK();
  writeNumbers();
  writeLetters();*/
  writeKit();

  if (intensity > 15) {
    intensity = 1;
  }
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
  delay(delaytime * 3);
 }


void writeEmoSad() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B00100100);
  lc.setRow(0, 2, B00000000);
  lc.setRow(0, 3, B00011000);
  lc.setRow(0, 4, B00100100);
  lc.setRow(0, 5, B01000010);
  lc.setRow(0, 6, B00000000);
  lc.setRow(0, 7, B00000000);
  delay(delaytime * 2);
 }
 void writeEmoBad() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B01000010);
  lc.setRow(0, 2, B00100100);
  lc.setRow(0, 3, B00011000);
  lc.setRow(0, 4, B00000000);
  lc.setRow(0, 5, B00000000);
  lc.setRow(0, 6, B00111100);
  lc.setRow(0, 7, B00000000);
  delay(delaytime * 2);
 }

 void writeEmoAmazing() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B01100110);
  lc.setRow(0, 2, B00000000);
  lc.setRow(0, 3, B00111100);
  lc.setRow(0, 4, B01000010);
  lc.setRow(0, 5, B01000010);
  lc.setRow(0, 6, B00111100);
  lc.setRow(0, 7, B00000000);
  delay(delaytime * 2);
 }

  void writeEmoIllusion() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B00100100);
  lc.setRow(0, 2, B01011010);
  lc.setRow(0, 3, B00000000);
  lc.setRow(0, 4, B00000000);
  lc.setRow(0, 5, B01111110);
  lc.setRow(0, 6, B00000000);
  lc.setRow(0, 7, B00000000);
  delay(delaytime * 2);
 }

void writeEmoHeart() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B01100110);
  lc.setRow(0, 2, B11111111);
  lc.setRow(0, 3, B11111111);
  lc.setRow(0, 4, B11111111);
  lc.setRow(0, 5, B01111110);
  lc.setRow(0, 6, B00111100);
  lc.setRow(0, 7, B00011000);
  delay(delaytime * 2);
}

void writeOK() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B00000000);
  lc.setRow(0, 2, B01001001);
  lc.setRow(0, 3, B10101010);
  lc.setRow(0, 4, B10101100);
  lc.setRow(0, 5, B10101010);
  lc.setRow(0, 6, B01001001);
  lc.setRow(0, 7, B00000000);
  delay(delaytime * 2);
}

 void writeNumbers() {
  for (int j = 0;j< 10;j++) {
    for (int i=0;i<8;i++) {
      lc.setRow(0, i, disp1[j][i]);
    }
    delay(delaytime);
  }
 }

void writeLetters() {
  for (int j = 10;j< 38;j++) {
    for (int i=0;i<8;i++) {
      lc.setRow(0, i, disp1[j][i]);
    }
    delay(delaytime);
  }
 }

void writeKit() {
  int divisor = 12;

  lc.clearDisplay(0);
  for (int i=0;i<3;i++) {
      lc.setRow(0, 1, B00000000);
      lc.setRow(0, 2, B00000000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00000000);
      lc.setRow(0, 6, B00000000);
      delay(delaytime / divisor);
      lc.setRow(0, 1, B00000000);
      lc.setRow(0, 2, B00010000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00010000);
      lc.setRow(0, 6, B00000000);
      delay(delaytime / divisor);
      lc.setRow(0, 1, B00010000);
      lc.setRow(0, 2, B00010000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00010000);
      lc.setRow(0, 6, B00010000);
      delay(delaytime / divisor);  
      lc.setRow(0, 1, B00010000);
      lc.setRow(0, 2, B00010000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00010000);
      lc.setRow(0, 6, B00010000);
      delay(delaytime / divisor); 
      lc.setRow(0, 1, B00010000);
      lc.setRow(0, 2, B01010100);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B01010100);
      lc.setRow(0, 6, B00010000);
      delay(delaytime / divisor);
      lc.setRow(0, 1, B00010000);
      lc.setRow(0, 2, B01010100);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B01010100);
      lc.setRow(0, 6, B00010000);
      delay(delaytime / divisor);
      lc.setRow(0, 1, B00010000);
      lc.setRow(0, 2, B00010000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00010000);
      lc.setRow(0, 6, B00010000);
      delay(delaytime / divisor); 
      lc.setRow(0, 2, B00010000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00010000);
      lc.setRow(0, 6, B00000000);
      delay(delaytime / divisor);
      lc.setRow(0, 1, B00000000);
      lc.setRow(0, 2, B00000000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00000000);
      lc.setRow(0, 6, B00000000);
      delay(delaytime / divisor);
    }  
}
