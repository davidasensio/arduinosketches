/* Sound, light and animation for nativity scene */
/* Septiembre 2016 */

#include <Servo.h>
#include <Bounce2.h>
#include <time.h>
#include <stdlib.h>

#define RED 1
#define GREEN 2
#define BLUE 3

//Barrera and led pin
int pushButtonPin = 6;
int servoPin = 5;
int val = 0;
Servo servo;
int pos = 0;
int servoMaxDegrees = 120;
boolean pushedEven = false;
boolean isUp = false;

Bounce bouncer = Bounce();

//Sound
int speakerPin = 7;

//RGB led
int redPin = 1;
int greenPin = 2;
int bluePin = 3;

int cycleTime = 1000;

int dimmer = 0;
boolean isFading = false;
int completeCycles = 1;
int currentColor = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(servoPin, OUTPUT);
  pinMode(pushButtonPin, INPUT);
  bouncer.attach(pushButtonPin);
  bouncer.interval(10);
  servo.attach(servoPin);

  //Sonido
  pinMode (speakerPin, OUTPUT);

  //lights
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  turnOffLights();
}

void loop() {
  bouncer.update();

  if (bouncer.fell()) {
    pushedEven = !pushedEven;
  }

  ambient();
}

void ambient() {
  if (completeCycles % 3 == 0) {
    completeCycles++;
    currentColor = 1 + (rand() % 3);
  } else if (completeCycles % 4 == 0) {
    completeCycles++;
    playMelody();
  }

  fadeFn(currentColor);
}

void fadeFn(int colorPin) {
  dimmer += isFading ? 1 : -1;
  if (dimmer > cycleTime) {
    isFading = false;
  }
  if (dimmer < 0) {
    isFading = true;
    completeCycles++;
  }

  //moveServo
  servo.write(30 + (dimmer/10));

  digitalWrite(colorPin, HIGH);
  delay(1);
  turnOffLights();
  delay(32 * dimmer / cycleTime);
}

void turnOffLights() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

//Melody
char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' };
int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 };
int tempo = 100;

int length = 19;
char notes[] = "gage gage ddb ccg aacba";
int beats[] = { 6,3,6,6, 2,6,3,6,6, 2, 12,6,8,2 ,12,6,12, 4,12,6,6,6,2};

void playTone(int tone, int duration) {
  int p = tone*2;
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(p);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(p);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      int t = tones[i]*0.05;
      playTone(t, duration);
    }
  }
}

void playMelody() {
   for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2); 
  }
}




//void moveServo() {
//  int inc = 1;
//  for (pos = servoMaxDegrees; pos >= 30; pos -= inc) {
//    servo.write(pos);
//    delay(50);
//  }
//  for (pos = pos; pos <= servoMaxDegrees; pos += inc) {
//    servo.write(pos);
//    delay(50);
//  }
//}



//void dangerLight() {
//  //Light red
//  orangeLight();
//  delay(120);
//
//  //Light blue
//  orangeRedLight();
//  delay(120);
//}
//
//void redLight() {
//  analogWrite(bluePin, 0);
//  analogWrite(redPin, 255);
//  analogWrite(greenPin, 0);
//}
//
//void blueLight() {
//  analogWrite(bluePin, 255);
//  analogWrite(redPin, 0);
//  analogWrite(greenPin, 0);
//}
//
//void orangeLight() {
//  analogWrite(greenPin, 125);
//  analogWrite(bluePin, 0);
//  analogWrite(redPin, 255);
//}
//void orangeRedLight() {
//  analogWrite(greenPin, 130);
//  analogWrite(bluePin, 0);
//  analogWrite(redPin, 255);
//}


