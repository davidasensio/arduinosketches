/*
    David Asensio 2018
    Arduino Firebase Notification PIR Sensor sketch

    This example demonstrates how to use
    WiFiClientSecure class to access HTTPS API.
    And send Firebase Notifications
*/


#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#define PIR_LED D13
#define PIR_SENSOR D2

//const char* ssid = "Red de MENSAMATIC";
//const char* password = "06v94_mm";
const char* ssid = "ONO4CDF";
const char* password = "0087423209";
const char* host = "fcm.googleapis.com";
const int httpsPort = 443;

String url = "/fcm/send";

int val = 0;
int pirState = LOW;
int counter = 0;
int interval = 30 * 2; //5min (30 counters is 1 minute)

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long triggerCheckInterval = 1000 * 60 * 5; //5 min

int connectToWifi() {
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  return 1;
}

void requestPOST(String postData) {
  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");

  } else {

    client.connect(host, httpsPort);
    Serial.print("requesting URL: ");
    Serial.println(url);

    Serial.println("connected");
    client.println("POST " + url + " HTTP/1.1");
    client.println("Host: fcm.googleapis.com");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.println("Authorization: key=AAAA4Cj4sl4:APA91bG1zDZOjPQL4b5H1MiWi-GgB9UIhdGCLsv2J0q2EZrL8C6Eh0kmZW1OxX3qSUrFoOXgBxpgYypVXnN0vYlqR_VSms7-A40SqOHBFM-vMRrFbc7uFbRSB3tKRBaICKdMhiWlT7IB");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.println(postData);

    Serial.println("request sent");
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }

    String line = client.readStringUntil('\n');

    bool checkResponse = false;
    String expectedResponse = "";
    if (checkResponse == true) {
      if (line.startsWith(expectedResponse)) {
        Serial.println("esp8266/Arduino CI successfull!");
      } else {
        Serial.println("esp8266/Arduino CI has failed");
      }
    }
    Serial.println("reply was:");
    Serial.println("==========");
    Serial.println(line);
    Serial.println("==========");
    Serial.println("closing connection");

  }
}

void printCounterStatus() {
  Serial.println("Counter is ");
  Serial.print(counter);
  Serial.print(" and interval is ");
  Serial.print(interval);
  Serial.println("");
}

void checkPirSensor() {
  val = digitalRead(PIR_SENSOR);
  Serial.print(val,DEC);
  if (val == HIGH) {
    digitalWrite(PIR_LED, HIGH);
    if (pirState == LOW) {
      Serial.println("\nSensor activado");
      pirState = HIGH;

      //If passed X seconds since last trigger then check
      //unsigned long currentMillis = millis();
      //if (currentMillis - previousMillis >= triggerCheckInterval) {
      printCounterStatus();
      if (counter > interval) {
        Serial.println("Sending notification");
        //previousMillis = currentMillis;

        int retVal = connectToWifi();

  if (retVal > 0) {
        sendPirSensorActivatedNotification();        
  }
        counter = 0;
        
    WiFi.disconnect();
        //        WiFi.forceSleepBegin();
        //        delay(1000);
      }
    }
  } else {
    digitalWrite(PIR_LED, LOW);
    if (pirState == HIGH) {
      Serial.println("\nSensor apagado");
      pirState = LOW;
    }
  }
}

void sendPirSensorListeningNotification() {
  Serial.println("Notifcation PIR listening sended");
  String postData = "{\"to\":\"/topics/key_asser\",\"priority\":\"high\",\"notification\":{\"body\":\"PIR Sensor listening!\",\"title\":\"Arduino - PIR Sensor\"}}";
  requestPOST(postData);
}

void sendPirSensorActivatedNotification() {
  Serial.println("Notifcation PIR Activated listening sended");
  String postData = "{\"to\":\"/topics/key_asser\",\"priority\":\"high\",\"notification\":{\"body\":\"PIR Sensor activated!\",\"title\":\"Arduino - PIR Sensor\"}}";
  requestPOST(postData);
}

void setup() {
  pinMode(PIR_LED, OUTPUT);
  pinMode(PIR_SENSOR, INPUT);

  Serial.begin(9600);

  int retVal = connectToWifi();

  if (retVal > 0) {
    sendPirSensorListeningNotification();
    WiFi.disconnect();
  }
  Serial.println("End setup");
  delay(5000);
}

void loop() {
  checkPirSensor();
  delay(200);
  if (counter++ > (interval * 10)) {
    counter = 0;
  }
  //  val = digitalRead(PIR_SENSOR);
  //  Serial.print(val);
}


