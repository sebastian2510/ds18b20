#include <OneWire.h>
#include <DallasTemperature.h>
#include <SensorService.h>

// GPIO where the DS18B20 is connected to
const int oneWireBus = 15;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void SensorService::setup() {
  // Start the DS18B20 sensor
  sensors.begin();
}

double SensorService::getTemperatures() {
  sensors.requestTemperatures(); 
  return sensors.getTempCByIndex(0);
}