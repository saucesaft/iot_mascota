#include "calidad.hpp"
#include "ultrasonico.hpp"
#include "db.hpp"

#include <string>

const std::string SSID = "Tec-IoT";
const std::string PASS = "spotless.magnetic.bridge";

const std::string ROOT_URL = "http://10.22.135.86:3100/api/";

///////////////////////////
// SENSORES DE INTERVALO //
///////////////////////////

// Se tomara la lectura cada minuto se mandara a la base de datos //
Calidad c(5, 4, 3, A0);
Ultrasonico u(12, 14, 16);
DB d(SSID, PASS);

void setup() {
  Serial.begin(9600);
  d.connect();
}

// Cada minuto se toma la lectura, se actua a partir de los valores y se manda esa misma lectura al API
void loop() {
  int calidad_lectura = c.lectura();
  float ultra_lectura = u.lectura();
  c.actuador();
  u.actuador();
  
  std::string query = generarConsulta(calidad_lectura, ultra_lectura);

  Serial.println(query.c_str());

  d.log(query);

  delay(1000);
}

// Esta función genera el URL completo con el Query para mandar al API
std::string generarConsulta(int calidad_lectura, float ultra_lectura) {
  std::string query = ROOT_URL;
  query += "1/";
  query += "sensor/intervalo/";
  query += std::to_string(calidad_lectura) + "/";
  query += std::to_string(ultra_lectura) + "/";

  return query;
}
