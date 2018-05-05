#include <LedControl.h>

//Create single LedControl
LedControl lc = LedControl(13,12,11,1);
int delaytime = 200;

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
int defSpeed = MAX;
int CORRECTION = 3;

void setup() {
  pinMode (ENA, OUTPUT); 
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);  
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENB, OUTPUT); 

  pinMode(SOUND_INPUT, INPUT);

  lc.shutdown(0, false);//Wake up
  lc.setIntensity(0, 1); //00..15 Brightness levels
  lc.clearDisplay(0);

  randomSeed(analogRead(0));

  writeEmoHappy();
}

void loop() {
  printFace();
 //testRight(); 
 //testLeft();
 testVoice();
}

void printFace() {
  long n = random(1000);
  Serial.println(n);
  if (n > 985) {
     n = random(1000);
    if (n == 995) {
      writeEmoSad();
    }else if (n == 985) {
      writeEmoAmazing();
    }else if (n == 975) {
      writeEmoBad();
    } else if (n > 500 && n < 505) {
      writeEmoHappy();
    }
  }
}

void testVoice() {  
  int soundInput = digitalRead(SOUND_INPUT);  
  if (soundInput == HIGH) {
    writeKit();
    writeEmoHappy();
    long n = random(100);
    if (n > 80) {
      moveBackward();
    } else if (n > 65) {
      moveAround();
    } else {
      moveForward();
    }
    
    delay(1500);
  } else {
    stop();
  }
}


void moveForward() {
  int speed = defSpeed;
  //Left  
  analogWrite (ENA, speed );  
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  //Right
  analogWrite (ENB, speed - CORRECTION);
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);  
}

void moveBackward() {
  int speed = defSpeed;
  //Left  
  analogWrite (ENA, speed );  
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  //Right
  analogWrite (ENB, speed - CORRECTION);
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);  
}


void moveAround() {
  int speed = defSpeed;
  //Left  
  analogWrite (ENA, speed );  
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  //Right
  analogWrite (ENB, speed - CORRECTION);
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

//Led Matrix functions
void writeEmoHappy2() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B01000100);
  lc.setRow(0, 2, B00000000);
  lc.setRow(0, 3, B00010000);
  lc.setRow(0, 4, B00000000);
  lc.setRow(0, 5, B01000100);
  lc.setRow(0, 6, B00111000);
  lc.setRow(0, 7, B00000000);
  //delay(delaytime * 3);
 }

void writeEmoHappy() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B01100110);
  lc.setRow(0, 2, B01100110);
  lc.setRow(0, 3, B00000000);
  lc.setRow(0, 4, B00000000);
  lc.setRow(0, 5, B01000010);
  lc.setRow(0, 6, B00111100);
  lc.setRow(0, 7, B00000000);
  //delay(delaytime * 3);
 }

void writeEmoSad() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B00100100);
  lc.setRow(0, 2, B00000000);
  lc.setRow(0, 3, B00011000);
  lc.setRow(0, 4, B00100100);
  lc.setRow(0, 5, B01000010);
  lc.setRow(0, 6, B00000000);
  lc.setRow(0, 7, B00000000);  
 }
 void writeEmoBad() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B01000010);
  lc.setRow(0, 2, B00100100);
  lc.setRow(0, 3, B00000000);
  lc.setRow(0, 4, B00000000);
  lc.setRow(0, 5, B00111100);
  lc.setRow(0, 6, B00000000);
  lc.setRow(0, 7, B00000000);
  delay(delaytime * 2);
 }

 void writeEmoAmazing() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B01100110);
  lc.setRow(0, 2, B00000000);
  lc.setRow(0, 3, B00111100);
  lc.setRow(0, 4, B01000010);
  lc.setRow(0, 5, B01000010);
  lc.setRow(0, 6, B00111100);
  lc.setRow(0, 7, B00000000);
  delay(delaytime * 2);
 }

  void writeEmoIllusion() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B00100100);
  lc.setRow(0, 2, B01011010);
  lc.setRow(0, 3, B00000000);
  lc.setRow(0, 4, B00000000);
  lc.setRow(0, 5, B01111110);
  lc.setRow(0, 6, B00000000);
  lc.setRow(0, 7, B00000000);
  delay(delaytime * 2);
 }

void writeEmoHeart() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B01100110);
  lc.setRow(0, 2, B11111111);
  lc.setRow(0, 3, B11111111);
  lc.setRow(0, 4, B11111111);
  lc.setRow(0, 5, B01111110);
  lc.setRow(0, 6, B00111100);
  lc.setRow(0, 7, B00011000);
  delay(delaytime * 2);
}


void writeOK() {
  lc.setRow(0, 0, B00000000);
  lc.setRow(0, 1, B00000000);
  lc.setRow(0, 2, B01001001);
  lc.setRow(0, 3, B10101010);
  lc.setRow(0, 4, B10101100);
  lc.setRow(0, 5, B10101010);
  lc.setRow(0, 6, B01001001);
  lc.setRow(0, 7, B00000000);
  delay(delaytime * 2);
}

void writeKit() {
  int divisor = 12;

  lc.clearDisplay(0);
  for (int i=0;i<3;i++) {
      lc.setRow(0, 1, B00000000);
      lc.setRow(0, 2, B00000000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00000000);
      lc.setRow(0, 6, B00000000);
      delay(delaytime / divisor);
      lc.setRow(0, 1, B00000000);
      lc.setRow(0, 2, B00010000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00010000);
      lc.setRow(0, 6, B00000000);
      delay(delaytime / divisor);
      lc.setRow(0, 1, B00010000);
      lc.setRow(0, 2, B00010000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00010000);
      lc.setRow(0, 6, B00010000);
      delay(delaytime / divisor);  
      lc.setRow(0, 1, B00010000);
      lc.setRow(0, 2, B00010000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00010000);
      lc.setRow(0, 6, B00010000);
      delay(delaytime / divisor); 
      lc.setRow(0, 1, B00010000);
      lc.setRow(0, 2, B01010100);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B01010100);
      lc.setRow(0, 6, B00010000);
      delay(delaytime / divisor);
      lc.setRow(0, 1, B00010000);
      lc.setRow(0, 2, B01010100);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B01010100);
      lc.setRow(0, 6, B00010000);
      delay(delaytime / divisor);
      lc.setRow(0, 1, B00010000);
      lc.setRow(0, 2, B00010000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00010000);
      lc.setRow(0, 6, B00010000);
      delay(delaytime / divisor); 
      lc.setRow(0, 2, B00010000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00010000);
      lc.setRow(0, 6, B00000000);
      delay(delaytime / divisor);
      lc.setRow(0, 1, B00000000);
      lc.setRow(0, 2, B00000000);
      lc.setRow(0, 3, B01010100);
      lc.setRow(0, 4, B01010100);
      lc.setRow(0, 5, B00000000);
      lc.setRow(0, 6, B00000000);
      delay(delaytime / divisor);
    }  
}
