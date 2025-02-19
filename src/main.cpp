#include <Arduino.h>
#include <WiFi.h>
#include <WebServerService.h>
#include <APService.h>
#include <vector>
#include <Models/WeatherData.h>
#include <FileManager.h> 
#include <WebSocketService.h> 
#include <NTPService.h>
#include <SensorService.h>

#define BUTTON 4

std::vector<WeatherData> data;

/**
 * @brief Sets up the necessary services and components for the application.
 * 
 * This function performs the following setup tasks:
 * - Configures the BUTTON pin as an input with an internal pull-up resistor.
 * - Initializes the serial communication at a baud rate of 115200.
 * - Sets up the APService.
 * - Sets up the FileManager/SPIFFS.
 * - Optionally clears data from the FileManager (commented out).
 * - Sets up the NTPService.
 * - Sets up the SensorService.
 * - Retrieves data from a file using the FileManager.
 * - Sets up the WebServerService and WebSocketService with the retrieved data.
 */
void setup()
{
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("Setting up APService");
  APService::setup();
  Serial.println("Setup done for APService");

  Serial.println("Setting up FileManager/SPIFFS");
  FileManager::setup();
  Serial.println("Setup done for FileManager/SPIFFS");

  FileManager::ClearData();

  Serial.println("Setting up NTPService");
  NTPService::setup();
  Serial.println("Setup done for NTPService");

  Serial.println("Setting up SensorService");
  SensorService::setup();
  Serial.println("Setup done for SensorService");

  Serial.println("Getting data from file");
  FileManager::GetData(data);
  Serial.println("Data retrieved from file");

  Serial.println("Setting up WebServerService & WebSocketService");
  WebServerService::setup(data);
  Serial.println("Setup done for WebServerService & WebSocketService");
}

void loop()
{

  // If the button is pressed down for 10 seconds
  if (digitalRead(BUTTON) == LOW)
  {
    Serial.println("Button pressed");
    delay(10000);
    if (digitalRead(BUTTON) == LOW)
    {
      Serial.println("Button pressed for 10 seconds, disconnecting");
      APService::Disconnect();
      APService::setup();
    }
    return;
  }
  double temperature = SensorService::getTemperatures();

  if (temperature == -127) {
    Serial.println("Failed to read temperature");
    return;
  }

  WeatherData data;
  // Read temperature sensor
  data.setTemperature(temperature); ;
  // Get current time
  struct tm timeinfo = NTPService::getTime();
  char buffer[30];
  // Format the time
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
  data.setTimeStamp(buffer);
  if (!WebSocketService::SendData(data)) {
    Serial.println("Failed to send data");
  }

  if (!FileManager::AppendData(data)) {
    Serial.println("Failed to append data");
  }

  delay(1000);
}