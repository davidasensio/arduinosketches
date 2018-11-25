#define PWM_MIN 0
#define PWM_MAX 255

#define PWM_SPEED_LEFT 11
#define PWM_SPEED_RIGHT 10

#define LEFT1 5
#define LEFT2 6
#define RIGHT1 7
#define RIGHT2 8

int ejeX = A1;
int ejeY = A2;
int vX = 0;
int vY = 0;
int boton = 4;

void setup()
{
  Serial.begin(9600);

  Serial.println("Simple Tank");

  //attachInterrupt(0 /* INT0 = THROTTLE_IN_PIN */,calcThrottle,CHANGE);
  //attachInterrupt(1 /* INT1 = STEERING_IN_PIN */,calcSteering,CHANGE);

  pinMode(boton, INPUT_PULLUP)
  pinMode(PWM_SPEED_LEFT, OUTPUT);
  pinMode(PWM_SPEED_RIGHT, OUTPUT);
  pinMode(LEFT1, OUTPUT);
  pinMode(LEFT2, OUTPUT);
  pinMode(RIGHT1, OUTPUT);
  pinMode(RIGHT2, OUTPUT);
}

void loop() {
  vX = analogRead(ejeX);
  vy = analogRead(ejeY);

  int rX = map(vX, 0, 1024, 0, 255);
  int ry = map(vY, 0, 1024, 0, 255);

  Serial.println("Read: " + vX + " - " + rX);

  /*
  analogWrite(PWM_SPEED_LEFT, 100);
  analogWrite(PWM_SPEED_RIGHT,100);
  forward();
  delay(3000);
  analogWrite(PWM_SPEED_LEFT, 150);
  analogWrite(PWM_SPEED_RIGHT, 150);
  forward();
  delay(3000);  
  analogWrite(PWM_SPEED_LEFT, 175);
  analogWrite(PWM_SPEED_RIGHT, 175);
  forward();
  delay(2000); 
  */ 
}

void forward() {
  digitalWrite(LEFT2, HIGH);
  digitalWrite(LEFT1, LOW);
  digitalWrite(RIGHT2, HIGH);
  digitalWrite(RIGHT1, LOW);
}

void reverse() {
  digitalWrite(LEFT1, HIGH);
  digitalWrite(LEFT2, LOW);
  digitalWrite(RIGHT1, HIGH);
  digitalWrite(RIGHT2, LOW);
}

void left() {
  digitalWrite(RIGHT1, HIGH);
  digitalWrite(RIGHT2, LOW);
}

void right() {
  digitalWrite(LEFT1, HIGH);
  digitalWrite(LEFT2, LOW);
}




