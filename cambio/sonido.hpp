#ifndef SONIDO_H
#define SONIDO_H
#include <Arduino.h>
#include <ESP_Mail_Client.h>

#include <string>

class Sonido {
public:
  Sonido(int sensorPin, std::string ssid, std::string pass);
  int lectura();
  void actuador();
  void setup();
private:
  int sensorPin = 0;
  const char* smtpServer = "smtp.gmail.com";
  const int smtpServerPort = 465; // Puerto SMTP (por ejemplo, 587 para TLS)
  const char* emailSender = "alertasmascotas@gmail.com"; // Cambia por tu dirección de correo
  const char* emailPassword = "cijyuirswvkxcyfz"; // Cambia por tu contraseña de correo
  const char* emailRecipient = "Ray.medarz@gmail.com"; // Cambia por la dirección de correo de destino
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

  pinMode(16, INPUT);
}

int Sonido::lectura() {
  if (this->intento >= measurementCount) {
    this->intento = 0;
    this->sum = 0;
    this->positiveReadings = 0;
  }

  int lecturaRuido = digitalRead(16);

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
  // Declare the Session_Config for user-defined session credentials
  SMTPSession smtp;
  Session_Config config;

  // Set the session config
  config.server.host_name = smtpServer;
  config.server.port = smtpServerPort;
  config.login.email = emailSender;
  config.login.password = emailPassword;
  config.login.user_domain = "";

  // Connect to the server
  if (!smtp.connect(&config)) {
    Serial.println("Error al conectarse al servidor SMTP");
    return;
  }

  // Declare the message class
  SMTP_Message message;

  // Set the message headers
  message.sender.name = "ESP8266";
  message.sender.email = emailSender;
  message.subject = "Alerta: Se detectó un problema";
  message.addRecipient(F("Usuario"),emailRecipient);

  // Send raw text message
  String textMsg = "Se detectó un problema en las lecturas de audio.";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  // Send email
  if (MailClient.sendMail(&smtp, &message)) {
    Serial.println("Correo electrónico enviado correctamente");
  } else {
    Serial.println("Fallo en el envío del correo electrónico");
  }
  return;
}
#endif