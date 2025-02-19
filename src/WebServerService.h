#include <Arduino.h>
#include <vector>
#include <models/WeatherData.h>

class WebServerService
{
public:
    static void setup(std::vector<WeatherData>& data);
};