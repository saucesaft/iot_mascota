#ifndef DB_H
#define DB_H
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#include <string>

class DB {
public:
  DB(std::string ssid, std::string pass);
  int log(std::string query);
  void connect();
private:
  HTTPClient httpClient;
  WiFiClient wClient;

  std::string ssid, password;
};

DB::DB(std::string ssid, std::string pass) {
  this->ssid = ssid;
  this->password = pass;
}

void DB::connect() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println();
  Serial.print("Conectando (");
  Serial.print(ssid.c_str());
  Serial.print(") ");
  WiFi.begin(this->ssid.c_str(), this->password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());
  delay(500);
}

int DB::log(std::string query) {
  if(WiFi.status() == WL_CONNECTED){

    Serial.println(query.c_str());

    // Se crea el request y se ponen ciertos metadatos, para finalmente mandarla
    httpClient.begin(wClient, query.c_str()); 
    httpClient.addHeader("Content-Type", "Content-Type: application/json");
    int httpResponseCode = httpClient.POST(query.c_str());
    Serial.println(httpResponseCode); 
    httpClient.end(); 
    return httpResponseCode;
  }
  return -1;
}
#endif