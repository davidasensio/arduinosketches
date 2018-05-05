#include <LiquidCrystal.h>

int pinRS = 8;
int pinRW = 13;
int enabled = 9;
int pinD0 = 4;
int pinD1 = 5;
int pinD2 = 6;
int pinD3 = 7;

LiquidCrystal lcd(pinRS, pinRW, enabled, pinD0, pinD1, pinD2, pinD3);

byte corazon[8] = {
  B00000,
  B01010,
  B10101,
  B10001,
  B01010,
  B00100,
  B00100,
  B00000
};
byte corazon2[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00100,
  B00000
};
void setup() {
  lcd.begin(16, 2);
  //Descomentar una vez para crear los caracteres y volver a comentar para mostrar programa
  //lcd.createChar(0, corazon);  
  //lcd.createChar(1, corazon2);
  lcd.write(byte(0));
  lcd.print(" ");
  lcd.write(byte(1));
  lcd.print("Hola Mery ");
  lcd.print(" Te quiero Mucho! ");
  lcd.write(byte(0));
  lcd.print(" ");
  lcd.write(byte(1));
  lcd.print(" ");
  lcd.write(byte(0));
  lcd.print(" ");
  lcd.write(byte(1));
  lcd.print(" ");

  int counter = 40;
  while (counter > 0) {
    delay(300);
    lcd.scrollDisplayLeft();
    counter--;
  };
}

void loop() {
  // put your main code here, to run repeatedly:

}
