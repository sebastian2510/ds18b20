#include <Arduino.h>
#include <WiFi.h>
#include <WebServerService.h>
#include <APService.h>
#include <vector>
#include "Data.h"
#include <FileManager.h> 
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 0;

std::vector<Data> data;

void setup()
{
  Serial.begin(115200);
  Serial.println("Setting up APService");
  APService::setup();
  Serial.println("Setup done for APService");

  Serial.println("Setting up WebServerService");
  WebServerService::setup();
  Serial.println("Setup done for WebServerService");

  Serial.println("Fetching data");
  FileManager::GetData(data);
}

void loop()
{

}
