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
}

int Fotosensor::lectura() {
  this->valorFotosensor = analogRead(this->sensorPin);
  return this->valorFotosensor;
}

void Fotosensor::actuador() {

  if (this->valorFotosensor < 200) {    //Si el valor del fotosensor < 200
    digitalWrite(this->motorPin, HIGH);   //Mandar corriente al motor (Elevar mecanismo de cuchara)
    delay(500);                           //Esperar 500ms
    digitalWrite(this->motorPin, LOW);    //Dejar de mandar corriente al motor (Bajar mecanismo de cuchara)
    delay(1900);                          //Esperar 1900ms
  }
  return;
}
#endif