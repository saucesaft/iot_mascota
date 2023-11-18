#include "calidad.hpp"
#include "ultrasonico.hpp"
#include "db.hpp"

#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>

#define QUERY_SIZE  256
const std::string SSID = "Tec-IoT";
const std::string PASS = "spotless.magnetic.bridge";
const std::string ROOT_URL = "http://10.22.224.39:3100/api/";

///////////////////////////
// SENSORES DE INTERVALO //
///////////////////////////

// se tomara la lectura cada minuto se mandara a la base de datos //
Calidad c(5, 4, 3, A0);
Ultrasonico u(12, 14, 16);
DB d(SSID, PASS);

void setup() {
  Serial.begin(9600);
  d.connect();
}

void loop() {
  int calidad_lectura = c.lectura();
  float ultra_lectura = u.lectura();

  std::string query = generarQuery(calidad_lectura, ultra_lectura);

  Serial.println(query.c_str());

  d.log(query);

  delay(1000);
}

std::string generarQuery(int calidad_lectura, float ultra_lectura) {
  std::string query = ROOT_URL;
  query += "1/";
  query += "sensor/intervalo/";
  query += url_encode(std::to_string(calidad_lectura)) + "/";
  query += url_encode(std::to_string(ultra_lectura)) + "/";

  return query;
}

std::string url_encode(const std::string &value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        std::string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int((unsigned char) c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}