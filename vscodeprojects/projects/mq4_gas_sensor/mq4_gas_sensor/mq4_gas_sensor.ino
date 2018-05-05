/*
www.geekstips.com
MQ4 Gas Sensor - Arduino tutorial
*/
const int gasPin = A0; //GAS sensor output pin to Arduino analog A0 pin

void setup(){
  pinMode(13, OUTPUT);
  Serial.begin(9600); //Initialize serial port - 9600 bps
}

void loop(){
  int value = analogRead(gasPin);
  if (value > 200) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  Serial.println(value);
  delay(250); // Print value every 1 sec.
}
