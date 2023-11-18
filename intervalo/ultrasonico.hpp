#ifndef ULTRASONICO_H
#define ULTRASONICO_H
#include <Arduino.h>

#include <string>

class Ultrasonico {
public:
  Ultrasonico(int trig, int echo, int pump);
  float lectura();
  void actuador();
private:
  int trig, echo, pump;
  float distancia;
};

Ultrasonico::Ultrasonico(int trig, int echo, int pump) {
  this->trig = trig;
  this->echo = echo;
  this->pump = pump;

  pinMode(trig, OUTPUT); // Pin de disparo del sensor.
  pinMode(echo, INPUT);  // Pin de eco del sensor.
  pinMode(pump, OUTPUT); // Configura el pin de la bomba como salida.

  Serial.println("--> Sensor ultrasonico: Inicializado");
}

float Ultrasonico::lectura() {

  // return 3.14;

  // Genera un pulso de disparo con el sensor ultrasónico.
  digitalWrite(this->trig, LOW);
  delayMicroseconds(3);  // Tiempo de espera a 3 microsegundos.
  digitalWrite(this->trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->trig, LOW);

  // Mide el tiempo del eco y calcula la distancia en centímetros.
  float tiempo = pulseIn(this->echo, HIGH, 30000);  // Reducir el tiempo de espera a 30,000 microsegundos (30 ms).
  this->distancia = tiempo / 58.3;

  return this->distancia;
}

void Ultrasonico::actuador() {
  Serial.println("actuador bomba de agua");
  return;

  if (this->distancia <= 3.9) {
     // El nivel de agua es igual o menor a 3.9 cm, apaga la bomba.
     digitalWrite(this->pump, HIGH);
   } else if (this->distancia >= 6.5) {
     // El nivel de agua es igual o mayor a 6.5 cm, enciende la bomba.
     digitalWrite(this->pump, LOW);
   }
   digitalWrite(this->pump, HIGH);
}

#endif