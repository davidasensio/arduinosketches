//#include <LedControl.h>
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high

#define OUTPUT_READABLE_YAWPITCHROLL

//#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
//bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

// ================================================================
// ===                       SELF BALANCE                       ===
// ================================================================

float yAxisValue = 0;
unsigned long previousMillis = 0; // last time update
long interval = 8000; // interval at which to do something (milliseconds)


//Create single LedControl
//LedControl lc = LedControl(13,12,11,1);
int delaytime = 200;

//LN298 Motor Driver Pins
int ENA = 5;    // ENA conectada al pin 3 de Arduino
int IN1 = 6;    // Input1 conectada al pin 4
int IN2 = 7;    // Input2 conectada al pin 5 

int IN3 = 9;    // Input3 conectada al pin 7
int IN4 = 8;    // Input4 conectada al pin 8 
int ENB = 10;    // ENB conectada al pin 9 de Arduino

// Sound Sensor Pins
//int SOUND_INPUT = 4;

//Speed
int factor = 3.7; //For balancing
int MIN = 125;
int MED = 220;
int MAX = 255;
int defSpeed = MAX;
int CORRECTION = 0;



// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================
void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz). Comment this line if having compilation difficulties with TWBR.
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    Serial.begin(115200);
    //while (!Serial); // wait for Leonardo enumeration, others continue immediately

    // NOTE: 8MHz or slower host processors, like the Teensy @ 3.3v or Ardunio
    // Pro Mini running at 3.3v, cannot handle this baud rate reliably due to
    // the baud timing being too misaligned with processor ticks. You must use
    // 38400 or slower in these cases, or use some kind of external separate
    // crystal solution for the UART timer.

    // initialize device
    //Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();

    // verify connection
    //Serial.println(F("Testing device connections..."));
    //Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // wait for ready
    //Serial.println(F("\nSend any character to begin DMP programming and demo: "));
    //while (Serial.available() && Serial.read()); // empty buffer
    //while (!Serial.available());                 // wait for data
    //while (Serial.available() && Serial.read()); // empty buffer again

    // load and configure the DMP
    //Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        //Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        //Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        //Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        //Serial.print(F("DMP Initialization failed (code "));
        //Serial.print(devStatus);
        //Serial.println(F(")"));
    }

    // ================================================================
    // ===                       SELF BALANCE                       ===
    // ================================================================
    pinMode (ENA, OUTPUT); 
    pinMode (IN1, OUTPUT);
    pinMode (IN2, OUTPUT);  
    pinMode (IN3, OUTPUT);
    pinMode (IN4, OUTPUT);
    pinMode (ENB, OUTPUT); 
  
    //pinMode(SOUND_INPUT, INPUT);
  
/*lc.shutdown(0, false);//Wake up
    lc.setIntensity(0, 1); //00..15 Brightness levels
    lc.clearDisplay(0);
  
    randomSeed(analogRead(0));
  
    writeEmoHappy();  
    */  
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
    // if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
        // other program behavior stuff here
        // .
        // .
        // .
        // if you are really paranoid you can frequently test in between other
        // stuff to see if mpuInterrupt is true, and if so, "break;" from the
        // while() loop to immediately process the MPU data
        // .
        // .
        // .

        
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        //Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

       

        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

            yAxisValue = ypr[1] * 180/M_PI;
            
            //Serial.print("ypr\t");
            //Serial.print(ypr[0] * 180/M_PI);
            //Serial.print("\t");
            //Serial.println(yAxisValue);
            //Serial.print("\t");
            //Serial.println(ypr[2] * 180/M_PI);

            doBalance();
        #endif

            
        #ifdef OUTPUT_TEAPOT
            // display quaternion values in InvenSense Teapot demo format:
            teapotPacket[2] = fifoBuffer[0];
            teapotPacket[3] = fifoBuffer[1];
            teapotPacket[4] = fifoBuffer[4];
            teapotPacket[5] = fifoBuffer[5];
            teapotPacket[6] = fifoBuffer[8];
            teapotPacket[7] = fifoBuffer[9];
            teapotPacket[8] = fifoBuffer[12];
            teapotPacket[9] = fifoBuffer[13];
            Serial.write(teapotPacket, 14);
            teapotPacket[11]++; // packetCount, loops at 0xFF on purpose
        #endif
    }
}

void doBalance() {
  //Serial.print("\t");
  //Serial.println(yAxisValue);  
  int minMargin =-2;
  int maxMargin = 2;
  int withStop = false;
  
  if (yAxisValue >= -6 && yAxisValue <= 2) {
    defSpeed = 40 + (abs(yAxisValue) * factor);     
  }else {
    withStop = true;
    defSpeed = MED + (abs(yAxisValue) * factor);
   
  }
  if(defSpeed > 255) {
    defSpeed = 255;
  }

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
     previousMillis = currentMillis;  
     interval = 25;
      //stop();
     if (yAxisValue < minMargin) {
        moveForward();
     }else if (yAxisValue > maxMargin) {
        moveBackward();
     } else {
        stop();
     } 
     if (withStop) {
      delay(14);
      stop(); 
     }
  }
}

//Movement functions
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
/*
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
}*/
