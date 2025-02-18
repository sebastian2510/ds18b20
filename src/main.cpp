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

void setup()
{
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("Setting up APService");
  APService::setup();
  Serial.println("Setup done for APService");

  Serial.println("Setting up WebServerService & WebSocketService");
  WebServerService::setup();
  Serial.println("Setup done for WebServerService & WebSocketService");
  
  FileManager::GetData(data);
}

void loop()
{
  double temperature = SensorService::getTemperatures();
  Serial.println(temperature);
  Serial.println(digitalRead(BUTTON));
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

  WeatherData data;
  // Read temperature sensor
  data.setTemperature(temperature); ;
  // Get current time
  struct tm timeinfo = NTPService::getTime();
  char buffer[30];
  // Format the time
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
  data.setTimeStamp(buffer);
  WebSocketService::SendData(data);

  if (!FileManager::AppendData(data)) {
    Serial.println("Failed to append data");
  }

  delay(2000);
}