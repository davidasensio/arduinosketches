int waterSensorPin = 2;
int led = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(waterSensorPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(250);
  digitalWrite(led, LOW); 
  int isWaterPresent = digitalRead(waterSensorPin);
  if (isWaterPresent == HIGH) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(300);
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(300);
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(5000);
  }   
}
