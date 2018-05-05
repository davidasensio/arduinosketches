#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))  {
    Serial.println("Error en la lectura del sensor");

  } else {
    char result[25];
    char result2[25];
    
    
    

    sprintf(result, "%s %i", "Humedad rel: ", (int)h);
    Serial.println(result);
    sprintf(result2, "%s %i", "Temperatura: ", (int)t );
    Serial.println(result2);

    //Serial.print("Humedad relativa: ");
    //Serial.print(h, 0);  //Cero decimales
    //Serial.print(" %    ");
    //Serial.print("Temperatura: ");
    //Serial.print(t, 0); //Cero decimales
    //Serial.println(" Grados C");

  }
  delay(1000);
}

