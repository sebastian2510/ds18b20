#include <OneWire.h>
#include <DallasTemperature.h>
#include <SensorService.h>

// GPIO where the DS18B20 is connected to
const int oneWireBus = 15;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);



/**
 * @brief Initializes the DS18B20 sensor.
 * 
 * This function starts the DS18B20 sensor by calling the begin() method
 * on the sensors object. It should be called during the setup phase
 * of the application to ensure the sensor is properly initialized before use.
 */
void SensorService::setup() {
  // Start the DS18B20 sensor
  sensors.begin();
}

/**
 * @brief Requests temperature readings from the sensors and returns the temperature in Celsius.
 * 
 * This function initiates a temperature request to the connected sensors and retrieves the temperature
 * reading from the first sensor in the list.
 * 
 * @return double The temperature in Celsius from the first sensor.
 */
double SensorService::getTemperatures() {
  sensors.requestTemperatures(); 
  return sensors.getTempCByIndex(0);
}