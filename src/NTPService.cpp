#include <Arduino.h>
#include "NTPService.h"
#include <WiFi.h>
#include "time.h"
#include <iostream>
#include <APService.h>

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

void NTPService::setup()
{
    try
    {
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
struct tm NTPService::getTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        APService::Disconnect();
        APService::setup();

    }
    return timeinfo;
}