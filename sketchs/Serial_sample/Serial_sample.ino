int year = 2015;
int counter = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("El anyo ");
  Serial.print(year);
  Serial.print(" se escribe en binario asi: ");
  Serial.println(year, BIN);
  Serial.print("Y en hexadecimal asi: ");
  Serial.println(year, HEX);
  delay(1500);
}
