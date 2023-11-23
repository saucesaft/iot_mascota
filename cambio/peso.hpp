#ifndef PESO_H
#define PESO_H
// #include <Arduino.h>
#include <Servo.h>

#include "HX711.h"

#include <string>

class Peso {
public:
  Peso(int doutPin, int sckPin, int servoPin);
  int lectura();
  void actuador();
private:
  int doutPin, sckPin, servoPin;

  HX711 escala;
  Servo compuerta;

  int measure = 0;
  bool open = false;
};

Peso::Peso(int doutPin, int sckPin, int servoPin) {
  Serial.println("--> Escala: Inicializada");
  this->doutPin = doutPin;
  this->sckPin = sckPin;
  this->servoPin = servoPin;

  this->compuerta.attach(this->servoPin);
  this->escala.begin(this->doutPin, this->sckPin);

  this->escala.set_scale(-7272.2);
  //this->escala.tare();
}

int Peso::lectura() {
  this->measure = this->escala.get_units(10);
  this->escala.power_down();

  delay(50);
  this->escala.power_up();

  return this->measure;
}

void Peso::actuador() {
  //Abrir Servo
  compuerta.write(70);
  delay(500);
  compuerta.detach();
  compuerta.attach(this->servoPin);

  //Cerrar el servo
  compuerta.write(0);
  delay(500);
  compuerta.detach();
  compuerta.attach(this->servoPin);
  return;
}
#endif