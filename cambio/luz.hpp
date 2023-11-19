#ifndef FOTOSENSOR_H
#define FOTOSENSOR_H
#include <Arduino.h>

#include <string>

class Fotosensor {
public:
  Fotosensor(int sensorPin, int motorPin);
  int lectura();
  void actuador();
private:
  int sensorPin = 0, motorPin = 0;

  int valorFotosensor = 0;
};

Fotosensor::Fotosensor(int sensorPin, int motorPin) {
  Serial.begin(9600);
  Serial.println("--> Fotosensor: Inicializado");

  this->sensorPin = sensorPin;
  this->motorPin = motorPin;
  pinMode(motorPin,OUTPUT);
  digitalWrite(motorPin,HIGH);
  Serial.println("Fotosensor ya inizialsisdifojzo");
}

int Fotosensor::lectura() {
  this->valorFotosensor = analogRead(this->sensorPin);
  return this->valorFotosensor;
}

void Fotosensor::actuador() {
    digitalWrite(this->motorPin, LOW);   //Mandar corriente al motor (Elevar mecanismo de cuchara)
    delay(500);                           //Esperar 500ms
    digitalWrite(this->motorPin, HIGH);    //Dejar de mandar corriente al motor (Bajar mecanismo de cuchara)
    delay(1900);                          //Esperar 1900ms
  return;
}
#endif