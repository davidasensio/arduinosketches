/* JOYSTICK TO PC */

//INIT_CODE: 250
//250 / coordX / coordY / buttonState

byte message[4];

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

  int cX = (int)((coordX * 20) / 1023); //Convertido a porcentaje y casteado
  int cY = (int)((coordY * 20) / 1023);

  message[0] = 25;
  message[1] = cX; 
  message[2] = cY;
  message[3] = buttonState;

  Serial.write(message, 4); //Envio al PC
  delay(80);
}
