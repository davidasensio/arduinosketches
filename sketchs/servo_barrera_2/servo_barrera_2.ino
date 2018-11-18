
/* Barrera con sonido y luz de policia */
/* Septiembre 2016 */

#include <Bounce2.h>
#include <Servo.h>

//Barrera and led pin
int pushButtonPin = 6;
int servoPin = 5;
int ledPin = 13;
int val = 0;
Servo servo;
int pos = 0;
boolean pushedEven = false;
boolean isUp = false;
int servoMaxDegrees = 90;

Bounce bouncer = Bounce();

//Sonido
int speakerPin = 7;
int duracion = 250; //Duración del sonido
int fMin = 1000; //Frecuencia más baja que queremos emitir
int fMax = 3500; //Frecuencia más alta que queremos emitir
int i = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(servoPin, OUTPUT);
  pinMode(pushButtonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  bouncer.attach(pushButtonPin);
  bouncer.interval(10);
  servo.attach(servoPin);

  //Sonido
  pinMode (speakerPin, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  bouncer.update();

  if (bouncer.fell()) {
    pushedEven = !pushedEven;
  }
  //move();

  soundAndMove();
}

void move() {
  if (pushedEven == true) {

    if (isUp == true) {
      down();
      isUp = false;
    }
    digitalWrite(ledPin, HIGH);
  } else {

    if (isUp == false) {
      up();
      isUp = true;
    }
    digitalWrite(ledPin, LOW);
  }
}

void up() {
  for (pos = servoMaxDegrees; pos >= 0; pos -= 3) {
    servo.write(pos);
    delay(15);
  }
}

void down() {
  for (pos = 0; pos <= servoMaxDegrees; pos += 3) {
    servo.write(pos);
    delay(35);
  }
}

void soundAndMove() {

  if (pushedEven == true) {
    if (isUp == true) {
      makeSoundAndLight(6);
      down();
      turnOffLights();
      isUp = false;
    }
    digitalWrite(ledPin, HIGH);
  } else {

    if (isUp == false) {
      up();
      isUp = true;
    }
    digitalWrite(ledPin, LOW);
  }
}

void turnOffLights() {
  digitalWrite(ledPin, 0);
}

void makeSound(int count) {
  //tone(pin, frequency, duration)
  //sonido más agudo
  for (int j = 0; j < count; j++) {
    for (i = fMin; i <= fMax; i++)
      tone(speakerPin, i, duracion);
    //sonido más grave
    for (i = fMax; i >= fMin; i--)
      tone(speakerPin, i, duracion);
  }
}

void ledLight() {
  digitalWrite(ledPin, 0);
}

void makeSoundAndLight(int count) {
  for (int j = 0; j < count; j++) {
    //Sound
    makeSound(1);

    ledLight();

    //Turn off lights
    turnOffLights();
  }



}

