#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

int pinRS = 8;
int pinRW = 13;
int enabled = 9;
int pinD0 = 4;
int pinD1 = 5;
int pinD2 = 6;
int pinD3 = 7;

byte grado[8] = {
  B00000,
  B00100,
  B01010,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000
};

LiquidCrystal lcd(pinRS, pinRW, enabled, pinD0, pinD1, pinD2, pinD3);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);              // start the library
  lcd.createChar(0, grado);
  lcd.setCursor(0, 0);  
  
  dht.begin();
}

void loop() {
  lcd.clear();
  lcd.print("Temp / Hum. Rel");
  
  lcd.setCursor(0, 1);           // move to the begining of the second line

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))  {
    lcd.print("Error de lectura");
  } else {
    char result[25];
    char result2[25];    

    //sprintf(result, "%i / %i", (int)t, (int)h);
    lcd.print((int)t);
    lcd.write(byte(0));
    lcd.print(" / ");
    lcd.print((int)h);
    lcd.write(37);
  }
  delay(1000); 
}
