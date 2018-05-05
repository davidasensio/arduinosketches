//LN298 Motor Driver Pins
int ENA = 5;    // ENA conectada al pin 3 de Arduino
int IN1 = 6;    // Input1 conectada al pin 4
int IN2 = 7;    // Input2 conectada al pin 5 

int IN3 = 9;    // Input3 conectada al pin 7
int IN4 = 8;    // Input4 conectada al pin 8 
int ENB = 10;    // ENB conectada al pin 9 de Arduino

// Sound Sensor Pins
int SOUND_INPUT = 4;

//Speed
int MIN = 100;
int MED = 155;
int MAX = 255;
int CORRECTION = 5;

void setup() {
  pinMode (ENA, OUTPUT); 
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);  
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENB, OUTPUT); 

  pinMode(SOUND_INPUT, INPUT);
}

void loop() {
 //testRight(); 
 //testLeft();
 testVoice();
}

void testVoice() {  
  int soundInput = digitalRead(SOUND_INPUT);  
  if (soundInput == HIGH) {
    moveForward();
    delay(1000);
  } else {
    stop();
  }
}


void moveForward() {
  int speed = MIN;
  //Left  
  analogWrite (ENA, speed - CORRECTION);  
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  //Right
  analogWrite (ENB, speed);
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);  
}

void stop() {
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  digitalWrite (ENA, 0);
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
  digitalWrite (ENB, 0);
  
}
void testRight() {
   //Preparamos la salida para que el motor gire en un sentido
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  
  // Aplicamos PWM al pin ENB, haciendo girar el motor, cada 2 seg aumenta la velocidad
  analogWrite(ENB,55);
  delay(2000);
  analogWrite(ENB,105);
  
  delay(2000);
  analogWrite(ENB,255);
  
  delay(2000);
  // Apagamos el motor y esperamos 5 seg
  analogWrite(ENB,0);
  delay(3000);
}

void testLeft() {
   //Preparamos la salida para que el motor gire en un sentido
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  
  // Aplicamos PWM al pin ENB, haciendo girar el motor, cada 2 seg aumenta la velocidad
  analogWrite(ENA,55);
  delay(2000);
  analogWrite(ENA,105);
  
  delay(2000);
  analogWrite(ENA,255);
  
  delay(2000);
  // Apagamos el motor y esperamos 5 seg
  analogWrite(ENA,0);
  delay(3000);
}
