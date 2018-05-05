#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#define BUILTIN_LED 2

const char* ssid = "ONO4CDF";
const char* password = "0087423209";

const char* host_upv = "growgreenvlc.webs.upv.es";
const char* host = "api.github.com";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint0 = "35 85 74 EF 67 35 A7 CE 40 69 50 F3 C0 F6 80 CF 80 3B 2E 19";
const char* fingerprint = "8b3eb0d8b616ce0e452317f34e9399e877d12aad";
//8b3eb0d8b616ce0e452317f34e9399e877d12aad

void setup()
{ pinMode(BUILTIN_LED, OUTPUT); // Onboard LED
  Serial.begin(9600);


  WiFi.mode(WIFI_STA); //???
  
  //WiFi.begin("ONO4CDF", "0087423209");   //WiFi connection
  WiFi.begin(ssid, password);   //WiFi connection

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
  Serial.println("Connected");




Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host_upv);
  if (!client.connect(host_upv, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  String url = "/repos/esp8266/Arduino/commits/master/status";
  String url2 = "/conexiongg.php?SERIE=123&TEMPERATURA=18&HUMEDAD=75&SENSACION=0";
  Serial.print("requesting URL: ");
  Serial.println(url2);

  client.print(String("GET ") + url2 + " HTTP/1.1\r\n" +
               "Host: " + host_upv + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      Serial.println(line);
      break;
    }
  }
  String line = client.readStringUntil('\n');
  Serial.println(line);
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
  
}

void loop()
{ digitalWrite(BUILTIN_LED, HIGH);  // turn on LED with voltage HIGH
  delay(1000);                      // wait one second
  digitalWrite(BUILTIN_LED, LOW);   // turn off LED with voltage LOW
  delay(1000);                      // wait one second
  Serial.println(BUILTIN_LED);
  Serial.println("looping");

  //makeSSLGETRequest();
}

void makeGETRequest() {
  Serial.println("GET_1");
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
  Serial.println("GET_2");

    HTTPClient http;  //Declare an object of class HTTPClient

    http.begin("https://growgreenvlc.webs.upv.es/conexiongg.php?SERIE=123&TEMPERATURA=18&HUMEDAD=75&SENSACION=0");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request


  Serial.println("GET_3");  
  Serial.println("httpCode: ");  
  Serial.println(httpCode);
  
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
      
  Serial.println("GET_4");
    }

    http.end();   //Close connection
    Serial.println("GET_5");

  }

  delay(5000);    //Send a request every 30 seconds

}

void makeSSLGETRequest() {
  

}

