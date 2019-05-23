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
#define DELAY_MS 5000

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "ONOA8E5";
const char* password = "H1uPx0ETKrnw";

ESP8266WebServer server(80);
String webSite = "";
boolean button5Reading = false;
boolean button5LastReading = false;
long lastEvent = millis();

// Servo object
Servo servo;

void servoPush() {
  int pos;
  int angle = 0;
  int pushTime = 500;

  Serial.println("Servo moving!");

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
  //webSite += "<meta http-equiv='refresh' content='10'><title>ESP8266 Demo</title>"\n;
  webSite += "<!DOCTYPE html>\n";
  webSite += "<html>\n";
  webSite += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  webSite += "    <title>MrJeff - Door Bell</title>\n";
  webSite += "    <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  webSite += "  body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  webSite += "  .button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 36px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  webSite += "  .button-on {background-color: #3498db;}\n";
  webSite += "  .button-on:active {background-color: #2980b9;}\n";
  webSite += "  .button-off {background-color: #34495e; visibility: hidden}\n";
  webSite += "  .button-off:active {background-color: #2c3e50;}\n";
  webSite += "  p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  webSite += "</style>\n";
  webSite += "    <script>window.onload = function() {if (location.href.indexOf(\"open\") != -1) {document.getElementById('buttonOff').click();} }</script>\n";
  webSite += "</head>\n";
  webSite += "<body>\n";
  webSite += "<h1>MrJeff - Door Bell</h1>\n";
  webSite += "<h6>ESP8266 Web Server</h6>\n";
  webSite += "<h3>Press the button to open the door</h3>\n";
  webSite += "<br/><br/><br/><br/>\n";
  webSite += "<p>Push to</p><a class=\"button button-on\" href=\"/open\">Open</a>\n";
  webSite += "<p></p><a id='buttonOff' class=\"button button-off\" href=\"/ready\">ready</a>\n";
  webSite += "</body>\n";
  webSite += "</html>\n";

  // preparing GPIOs
  pinMode(PIN_SERVO, OUTPUT);
  digitalWrite(PIN_SERVO, LOW);

  // Attach servo
  servo.attach(PIN_SERVO);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

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
  server.on("/open", []() {
    server.send(200, "text/html", webSite);

    if ((millis() - lastEvent) > DELAY_MS) {
      button5Reading = !button5Reading;
      Serial.println("Trigger fired!");
    }
  });
  server.on("/ready", []() {
    server.send(200, "text/html", webSite);
  });

  server.begin();
  Serial.println("HTTP server started\n");
}

void loop(void) {
  server.handleClient();

  if (WiFi.status() != WL_CONNECTED)
  {

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
  }

  if (button5Reading != button5LastReading) {
    servoPush();
    button5LastReading = button5Reading;
    lastEvent = millis();
  }
}


