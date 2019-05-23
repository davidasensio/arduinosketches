/*
    David Asensio May 2019

    Arduino Sketch for trigger actuators via Wifi
    Control the Fermax phone by using webserver
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

#define PIN_SERVO D5

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "ONOA8E5";
const char* password = "H1uPx0ETKrnw";

ESP8266WebServer server(80);
String webSite = "";
//int sensorPin = 12;
int led0 = 13;
//int led1 = 4;
//int led2 = 5;
//int ledSensor = 16;
boolean button5Reading = false;
boolean button5LastReading = false;

// Servo object
Servo servo;

void servoPush() {
  int pos;
  int angle = 0;
  int pushTime = 500;

  Serial.println("Servo in!");

  // Push
  for (pos = 90; pos >= angle; pos -= 1) // goes from 0 degrees to 180 degrees
  { // in steps of 1 degree
    servo.write(pos);                   // tell servo to go to position in variable 'pos'
    delay(10);                          // waits 15ms for the servo to reach the position
  }

  // Pause
  delay(pushTime);

  // Pull
  for (pos = angle; pos <= 90; pos += 1) // goes from 180 degrees to 0 degrees
  {
    servo.write(pos);                   // tell servo to go to position in variable 'pos'
    delay(5);                           // waits 15ms for the servo to reach the position
  }
}

void setup(void) {

  webSite += "<meta http-equiv='refresh' content='10'><title>ESP8266 Demo</title>\n";
  webSite += "<style>body{ background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>\n";
  webSite += "<h2 dir=\"rtl\" style=\"text-align: left;\"><img alt=\"\" src=\"http://www.mybotic.com.my/webshaper/pcm/pictures/Mybotic-Logo-(5).jpg\" style=\"float: left; height: 103px; width: 999px; border-width: 15px; border-style: solid;\" /></h2>\n";
  webSite += "<p> &nbsp;</p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p>\n";
  webSite += "<button onclick='myFunction()'>HOME</button>";
  webSite += "<script>function myFunction() {location.reload();}</script>";
  webSite += "<script>window.onload = function() {if (location.href.indexOf(\"socket2On\") != -1) {document.getElementById('aoff').click();} }</script>";
  webSite += "<button onclick='myFunction2()'>HOME2</button>";
  webSite += "<script>function myFunction2() {window.location = \"http://192.168.1.127/\";}</script>";
  webSite += "<h1>ESP8266 Web Server</h1><p>LED #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>\n";
  webSite += "<p>LED #2 <a href=\"socket2On\" onMouseUp='myFunction2()'><button>ON</button></a>&nbsp;<a id='aoff' href=\"socket2Off\"><button>OFF</button></a></p>\n";
  webSite += "<p>LED #3  <a href=\"socket3On\" onMouseUp='alert(\"up\")'><button>ON</button></a>&nbsp;<a href=\"socket3Off\"><button>OFF</button></a></p>\n";
  webSite += " <p><h2>Condition read from flamesensor</h2></p>\n";

  // preparing GPIOs

  pinMode(PIN_SERVO, OUTPUT);
  digitalWrite(PIN_SERVO, LOW);
  pinMode(led0, OUTPUT);
  digitalWrite(led0, LOW);
  //  pinMode(led1, OUTPUT);
  //  digitalWrite(led1, LOW);
  //  pinMode(led2, OUTPUT);
  //  digitalWrite(led2, LOW);
  //  pinMode(sensorPin, INPUT);
  //  pinMode(ledSensor, OUTPUT);

  servo.attach(PIN_SERVO);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(led0, HIGH);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  server.on("/", []() {
    server.send(200, "text/html", webSite);
  });
  server.on("/socket1On", []() {
    server.send(200, "text/html", webSite);
  });
  server.on("/socket1Off", []() {
    server.send(200, "text/html", webSite);
  });
  server.on("/socket2On", []() {   
    //server.sendHeader("Location", String("/socket1Off"), true);
    //server.send ( 302, "text/plain", "");
    server.send(200, "text/html", webSite);
    button5Reading = !button5Reading;
    Serial.println("Servo!");

  });
  server.on("/socket2Off", []() {
    server.send(200, "text/html", webSite);
    //digitalWrite(led2, LOW);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  String sentences = "<p>Flame is detected!!!</p>";
  if (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(led0, LOW);
    Serial.println("");
    Serial.print("Wifi is disconnected!");
    Serial.println("");
    Serial.print("Reconnecting");
    Serial.println("");
    //WiFi.begin(ssid,password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    digitalWrite(led0, HIGH);
  }

  //  if (digitalRead(sensorPin) == LOW)
  //  {
  //    Serial.print("Flame is detected");
  //    Serial.println("");
  //    webSite += sentences;
  //    digitalWrite(ledSensor, HIGH);
  //    delay(300);
  //  }
  //  else                            //if no detect
  //  {
  //    digitalWrite(ledSensor, LOW);
  //  }

  if (button5Reading != button5LastReading) {
    servoPush();
    button5LastReading = button5Reading;
    delay(3000);
  }

}


