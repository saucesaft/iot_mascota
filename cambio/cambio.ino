#include "luz.hpp"
#include "peso.hpp"
#include "sonido.hpp"
#include "db.hpp"

#include <string>

const std::string SSID = "Tec-IoT";
const std::string PASS = "spotless.magnetic.bridge";
const std::string ROOT_URL = "http://10.22.135.86:3100/api/";

/////////////////////////
// SENSORES DE OCASIÓN //
/////////////////////////

// Incremento porcentual para cada sensor
float luz_incremento_umbral = 0.1;  // Incremento del 10%
float peso_incremento_umbral = 0.2; // Incremento del 20%
float sonido_incremento_umbral = 0.0; // Incremento del 1% (Esta lectura funciona diferente)

// Se tomará la lectura cada minuto y se enviará a la base de datos //
Fotosensor f(A0, 5);
Peso p(12, 13, 4);
Sonido s(16, SSID, PASS);

DB d(SSID, PASS);

// Lecturas iniciales del sensor
int lectura_inicial_luz;
int lectura_inicial_peso;
int lectura_inicial_sonido;

void setup() {
  Serial.begin(9600);
  Serial.println("Holiwis, iniciando programa");

  // Registrar lecturas iniciales del sensor
  lectura_inicial_luz = f.lectura();
  lectura_inicial_peso = p.lectura();
  lectura_inicial_sonido = s.lectura();

  d.connect();
}

void loop() {

  int lectura_foto_sensor = f.lectura();
  int lectura_peso = p.lectura();
  int lectura_sonido = s.lectura();

  // Calcular valores de umbral basados en las lecturas iniciales e incremento porcentual
  int luz_umbral_superior = lectura_inicial_luz * (1 + luz_incremento_umbral);
  int luz_umbral_inferior = lectura_inicial_luz * (1 - luz_incremento_umbral);

  int peso_umbral_superior = lectura_inicial_peso * (1 + peso_incremento_umbral);
  int peso_umbral_inferior = lectura_inicial_peso * (1 - peso_incremento_umbral);

  int sonido_umbral_superior = lectura_inicial_sonido * (1 + sonido_incremento_umbral);
  int sonido_umbral_inferior = lectura_inicial_sonido * (1 - sonido_incremento_umbral);


  // El siguiente codigo solo generara consultas de SQL si hay un cierto cambio de cierto porcentaje

  if (lectura_peso > peso_umbral_superior || lectura_peso < peso_umbral_inferior) {
    std::string consulta = generarConsulta(1, lectura_peso);
    Serial.println(consulta.c_str());
    lectura_inicial_peso = lectura_peso;
    d.log(consulta);
    p.actuador();
  }

  if (lectura_foto_sensor < luz_umbral_inferior) {
    std::string consulta = generarConsulta(2, lectura_foto_sensor);
    Serial.println(consulta.c_str());
    f.actuador();
    d.log(consulta);
  }


  if (lectura_sonido != 0) {
    std::string consulta = generarConsulta(3, lectura_sonido);
    Serial.println(consulta.c_str());
    lectura_inicial_sonido = lectura_sonido;
    s.actuador();
    d.log(consulta);
  }

  delay(200);
}

std::string generarConsulta(int tipo_sensor, int lectura) {
  // http://ip:3100/api/ID/sensor/intervalo/0/0
  // http://ip:3100/api/ID/sensor/cambio/(peso/ruido/pelota)/0

  std::string consulta = ROOT_URL;
  consulta += "1/";
  consulta += "sensor/cambio/";
  consulta += std::to_string(tipo_sensor) + "/";
  consulta += std::to_string(lectura) + "/";

  return consulta;
}
