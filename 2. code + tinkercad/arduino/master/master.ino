#include <Wire.h> // use this library to connect and transmit data bia I2C
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
String URL = "http://api.thingspeak.com/update?api_key=KO0XX903BUAHFNDV&field1=";

const char *ssid = "Familia_Cifu"; 
const char *pass = "77Familia9"; 

WiFiClient client;
HTTPClient http;

void setup() {
  Wire.begin(); // init communication
  Serial.begin(9600); // set data transfer rate
  WiFi.disconnect();
  delay(2000);
  Serial.print("Start connection");
  WiFi.begin(ssid, pass);
  while((!(WiFi.status() == WL_CONNECTED))){
    delay(200);
    Serial.print("..");
  }
  Serial.println("Connected");
}

void loop() {
  int temperatura = getTemp_SENSOR(); // get temp
  if (temperatura >= 30.0) { // send temp if greater than 30
    Wire.beginTransmission(8); // transmit data by serial bus 8
    Wire.write('1');  // send 1
    Wire.endTransmission(); // close transmission
  } else {
    Wire.beginTransmission(8); // transmit data by serial bus 8
    Wire.write('0'); // send 0
    Wire.endTransmission(); // close transmission
  }
  Serial.println("Temperatura: "+ (String)temperatura);
  // send data
  String URL_ = URL + (String)temperatura;
  http.begin(client, URL_);
  int responsecode = http.GET();
  String data = http.getString();
  http.end();
  delay(1000);
}

float getTemp_SENSOR() {
  int lectura = analogRead(33); // read tension from A0
  float temperatura = lectura/10;  
  return temperatura;
}

