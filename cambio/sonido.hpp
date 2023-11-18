#ifndef SONIDO_H
#define SONIDO_H
#include <Arduino.h>

#include <string>

class Sonido {
public:
  Sonido(int sensorPin, std::string ssid, std::string pass);
  int lectura();
  void actuador();
private:
  int sensorPin = 0;

  const int audioThreshold = 10000;
  const int measurementCount = 100; // cuantas veces tiene que contar para sacar un buen "promedio", esto es cada 200ms aprox

  int intento = 0;
  int sum = 0;
  int positiveReadings = 0;
  int averageReading = 0;

  std::string ssid, password;
};

Sonido::Sonido(int sensorPin, std::string ssid, std::string pass) {
  Serial.println("--> Sensor de sonido: Inicializado");

  this->sensorPin = sensorPin;
  this->ssid = ssid;
  this->password = pass;

  pinMode(D0, INPUT);
}

int Sonido::lectura() {
  if (this->intento >= measurementCount) {
    this->intento = 0;
    this->sum = 0;
    this->positiveReadings = 0;
  }

  int lecturaRuido = digitalRead(D0);

  // int lecturaRuido = analogRead(this->sensorPin);
  this->sum += lecturaRuido;
  this->intento++;

  if (lecturaRuido >= 1) {
    this->positiveReadings++;
  }

  // Serial.println("----------");
  // Serial.println(lecturaRuido);
  // Serial.println(positiveReadings);
  intento++;

  if (this->positiveReadings >= 1) {
    this->averageReading = this->sum / this->intento;
    this->intento = 0;
    this->sum = 0;
    this->positiveReadings = 0;
    return 1;
  }

  return 0;
}

void Sonido::actuador() {
  Serial.println("actuador bomba de agua");
  return;
}
#endif