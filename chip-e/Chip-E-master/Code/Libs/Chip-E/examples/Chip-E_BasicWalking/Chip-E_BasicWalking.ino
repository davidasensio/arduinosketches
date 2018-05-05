/***********************************************************************************
                    RobotGeek 'Chip-E' Biped - Basic Walking

                                 ______________
                                /              |
                               |   _________   |
                               |  [_________]  |
                               |               |
                               |               |
                               |               |
                               |       O       |
                               |               |
                                ---------------
                                   ||     ||
                                   ||     ||
                                   ||     ||
                              -------     -------
                              -------     -------

    Wiring

      LCD - I2C
      Buzzer - Digital Pin 12
      IR Receiver - Digital Pin 2
      Left Hip Servo - Digital Pin 10
      Right Hip Servo - Digital Pin 9
      Left Ankle Servo - Digital Pin 6
      Right Ankle Servo - Digital Pin 5

      Jumper for pins 9/10/11 should be set to 'VIN'
      Jumper for pins 3/5/6 should be set to 'VIN'

    Control Behavior:

      Power on Chip-E for a short demonstration.

 ***********************************************************************************/

#include "ChipE.h"
//--Chip-E
/*
            ______________
           /              |
          |   _________   |
          |  [_________]  |
          |               |
          |               |
          |               |
          |       O       |
   YR ==> |               | <== YL
           ---------------
              ||     ||
              ||     ||
              ||     ||
   RR ==>   -----   ------  <== RL
            -----   ------
*/
const int PIN_RR = 5; //Roll Right
const int PIN_RL = 6; //Roll Left
const int PIN_YR = 9; //Yaw Right
const int PIN_YL = 10; //Yaw Left
const int TRIM_RR = -35; //Trim on the right ankle (adjust +/- as necessary)
const int TRIM_RL = -70; //Trim on the left ankle (adjust +/- as necessary)
const int TRIM_YR = -40; //Trim on the right hip (adjust +/- as necessary)
const int TRIM_YL = -70; //Trim on the left hip (adjust +/- as necessary)

ChipE myChipE; //Chip-E object (your robot!:)

//Ultrasonic sensor
int ultrasonicTriggPin = 13;
int ultrasonicEchoPin = 12;
long distancia;
long tiempo;

boolean demoEnd = false;
boolean alternateDemo = false;
boolean reactionEnd = true;

void setup()
{
  Serial.begin(38400);

  pinMode(ultrasonicTriggPin, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(ultrasonicEchoPin, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/


  //--Chip-E initialization
  myChipE.init( PIN_YL, PIN_YR, PIN_RL, PIN_RR );
  myChipE.setTrims( TRIM_YL, TRIM_YR, TRIM_RL, TRIM_RR ); //Set the servo trims
  myChipE.home(); //Move feet to home position
  delay( 500 );

}

void loop() {
  if (demoEnd) {
    utlrasonicCheck();
  } else {
    demo2();
  }
}

void utlrasonicCheck() {
  digitalWrite(ultrasonicTriggPin, LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(ultrasonicTriggPin, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  tiempo = pulseIn(ultrasonicEchoPin, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
  deja de hacerlo, LOW, la longitud del pulso entrante*/
  distancia = int(0.017 * tiempo); /*fórmula para calcular la distancia obteniendo un valor entero*/
  /*Monitorización en centímetros por el monitor serial*/
  Serial.println("Distancia ");
  Serial.println(distancia);
  Serial.println(" cm");

  if (reactionEnd && distancia < 30) {
    alternateDemo = !alternateDemo;
    reactionEnd = false;
    if (alternateDemo) {
      reaction1();
    } else {
      reaction2();
    }
  }
  delay(50);
}
void demo2() {
  demoEnd = true;

  myChipE.home();
  myChipE.walk( 3, 2000, FORWARD );

  myChipE.home();

  myChipE.walk( 3, 1500, BACKWARD );

  myChipE.home();

  myChipE.turn( 3, 2000, RIGHT );
  myChipE.turn( 3, 2000, LEFT );
  
  myChipE.home();
}

void reaction1() {
  myChipE.home();
  delay( 500 );

  myChipE.updown( 3, 500, MEDIUM );

  myChipE.moonwalker( 3, 2000, 30, LEFT );

  myChipE.home();
  reactionEnd = true;  
}

void reaction2() {
  myChipE.home();
  delay( 500 );

  myChipE.swing( 3, 600, 10 );

  myChipE.crusaito( 3, 2000, 40, RIGHT );

  myChipE.home();
  reactionEnd = true; 
}

void demo1()
{

  demoEnd = true;
  myChipE.home();
  delay( 500 );

  myChipE.walk( 4, 2000, FORWARD );
  myChipE.walk( 4, 1000, FORWARD );

  myChipE.home();

  myChipE.walk( 4, 1000, BACKWARD );
  myChipE.walk( 4, 2000, BACKWARD );

  myChipE.home();


  myChipE.turn( 3, 2000, RIGHT );
  myChipE.turn( 3, 2000, LEFT );

  myChipE.updown( 6, 500, SMALL );
  myChipE.updown( 6, 500, MEDIUM );
  myChipE.updown( 2, 4000, BIG );

  myChipE.moonwalker( 3, 2000, 30, LEFT );
  myChipE.moonwalker( 3, 2000, 30, RIGHT );

  myChipE.swing( 6, 600, 10 );
  myChipE.swing( 4, 2000, 40 );

  myChipE.crusaito( 6, 2000, 40, LEFT );
  myChipE.crusaito( 6, 2000, 40, RIGHT );

  myChipE.flapping( 10, 600, 10, FORWARD );
  myChipE.flapping( 10, 600, 10, BACKWARD );
}
