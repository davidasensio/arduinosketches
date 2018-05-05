int numberToConvert = 0;
byte baseToConvert = '\0';
boolean firstTime = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (firstTime) {
    Serial.println("---- Convertidor de base ----");
    firstTime = false;
  }

  //Number to convert
  getNumber();

  //Get base and convert
  getBaseAndConvert();

  numberToConvert = 0;
  baseToConvert = '\0';

  delay(1000);

}

void getNumber() {
  Serial.println();
  Serial.println("\nIntroduce el numero a convertir...");
  do {
    if (Serial.available() > 0) {
      numberToConvert = Serial.parseInt();
    }
  } while (numberToConvert == 0);
}

void getBaseAndConvert() {
  Serial.print("Introduce la base en la que convertir el numero ");
  Serial.println(numberToConvert);
  Serial.println("b) Binario");
  Serial.println("o) Octal");
  Serial.println("h) Hexadecimal");

  boolean baseOk = false;

  do {
    if (Serial.available() > 0) {
      byte base = Serial.read();
      switch (base) {
        case 'b':
          Serial.println("En binario es");
          Serial.println(numberToConvert, BIN);
          baseOk = true;
          break;
          case 'o':
          Serial.println("En octal es");
          Serial.println(numberToConvert, OCT);
          baseOk = true;
          break;
          case 'h':
          Serial.println("En hexadecimal es");
          Serial.println(numberToConvert, HEX);
          baseOk = true;
          break;
      }
    }
  } while (baseOk == false);
}
