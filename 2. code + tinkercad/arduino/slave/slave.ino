#include <Wire.h> // use this library to connect and transmit data bia I2C

const int led_Pin = 13; // declare pin 13 as output warning

void setup() {
  Wire.begin(8); // listen data by serial bus 8
  Wire.onReceive(receiveEvent); // recive data
  pinMode(led_Pin, OUTPUT);
}

void loop(){// as slave just listen, slave does no need loop
}

void receiveEvent(int bytes) {
  if (Wire.available()) { // if exist data on serial bus 8
    char LED = Wire.read(); // LED is setted as 1 or 0

    if (LED == '1') {
      digitalWrite(led_Pin, HIGH); // temp greater than 30, led is on
    } else if (LED == '0') {
      digitalWrite(led_Pin, LOW); // temp lower than 30. led is off
    }
  }
}
