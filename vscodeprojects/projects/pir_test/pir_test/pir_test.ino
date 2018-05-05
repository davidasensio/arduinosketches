void setup() {
  pinMode(8, INPUT);
  Serial.begin(9600);
}

void loop() {
  int val = digitalRead(8);
  Serial.print(val);
  delay(300);
}
