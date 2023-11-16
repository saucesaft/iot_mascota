#ifndef CALIDAD_H
#define CALIDAD_H
#include <Arduino.h>

class Calidad {
public:
  Calidad(int red, int green, int blue, int tds);
  int lectura();
  void actuador();
private:
  int getMedianNum(int bArray[], int iFilterLen);

  static const int SCOUNT = 30; // sum of sample point
  int analogBuffer[SCOUNT]; // store the analog value in the array, read from ADC
  int analogBufferTemp[SCOUNT];

  int analogBufferIndex = 0, copyIndex = 0;
  float averageVoltage = 0, temperature = 25;

  int TdsSensorPin;
  const int VREF = 5.0; // analog reference voltage(Volt) of the ADC

  int red, green, blue;

  int tdsValue = 0;
};

Calidad::Calidad(int red, int green, int blue, int tds) {
  this->red = red;
  this->green = green;
  this->blue = blue;

  pinMode(tds, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  Serial.println("--> Sensor de calidad de agua: Inicializado");
}

int Calidad::lectura() {

  // return 42;

  static unsigned long analogSampleTimepoint = millis();

  if (millis() - analogSampleTimepoint > 40U)  // every 40 milliseconds, read the analog value from the ADC
  {
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
    analogBufferIndex++;
    if (analogBufferIndex == SCOUNT)
      analogBufferIndex = 0;
  }

  static unsigned long printTimepoint = millis();
  if (millis() - printTimepoint > 800U)
  {
    printTimepoint = millis();
    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
    averageVoltage = this->getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0); //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
    float compensationVolatge = averageVoltage / compensationCoefficient; //temperature compensation
    tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5; // convert voltage value to tds value

    return tdsValue;
  }
  return -1;
}

void Calidad::actuador() {
  Serial.println("actuador RGB");

  return;

  switch (tdsValue) {
    case 0 ... 300: // Valores bajos, por ejemplo, de 0 a 341
      //setColor(255, 0, 0);
      //digitalWrite(GREEN,HIGH); // Rojo
      digitalWrite(this->blue, HIGH);
      break;
    case 301 ... 600: // Valores intermedios, por ejemplo, de 342 a 682
      //setColor(0, 255, 0); 
      digitalWrite(this->green, HIGH); // Verde
      break;
    default: // Valores altos
      //setColor(0, 0, 255);
      digitalWrite(this->red, HIGH); // Azul
      break;
  }
}

int Calidad::getMedianNum(int bArray[], int iFilterLen)
{
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++)
  {
    for (i = 0; i < iFilterLen - j - 1; i++)
    {
      if (bTab[i] > bTab[i + 1])
      {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}
#endif