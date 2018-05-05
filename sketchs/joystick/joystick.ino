/* JOYSTICK */

int pinX = A0;
int pinY = A1;
int pinButton = 2;


void setup() {
  Serial.begin(9600);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinButton, INPUT);
  digitalWrite(pinButton, HIGH);
}

void loop() {
  int coordX = analogRead(pinX);
  int coordY = analogRead(pinY);
  boolean buttonState = digitalRead(pinButton);

  Serial.println("Coordenada X: ");
  Serial.println(coordX);
  Serial.println("  Coordenada Y: ");
  Serial.println(coordY);
  Serial.println("  Pulsador: ");
  Serial.println(buttonState);

  delay(800);

}
