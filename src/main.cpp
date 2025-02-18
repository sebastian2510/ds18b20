#include <Arduino.h>
#include <WiFi.h>
#include <WebServerService.h>
#include <APService.h>
#include <vector>
#include "Data.h"
#include <FileManager.h> 
#include <WebSocketService.h> 
#include <NTPService.h>

const char *ntpServer = "dk.pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 0;
#define TEMP_SENSOR 23
#define BUTTON 4

std::vector<WeatherData> data;

void setup()
{
  pinMode(TEMP_SENSOR, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("Setting up APService");
  APService::setup();
  Serial.println("Setup done for APService");

  Serial.println("Setting up WebServerService & WebSocketService");
  WebServerService::setup();
  Serial.println("Setup done for WebServerService & WebSocketService");
  
  Serial.println("Fetching data");
  FileManager::GetData(data);
}

void loop()
{
  // If the button is pressed down for 10 seconds
  if (digitalRead(BUTTON) == LOW)
  {
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
  data.Temperature = analogRead(TEMP_SENSOR);
  // Get current time
  struct tm timeinfo = NTPService::getTime();
  char buffer[30];
  // Format the time
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
  data.TimeStamp = buffer;
  WebSocketService::SendData(data);

  if (!FileManager::AppendData(data)) {
    Serial.println("Failed to append data");
  }
}