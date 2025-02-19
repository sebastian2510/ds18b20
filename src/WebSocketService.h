#include <Models/WeatherData.h>
#include <ESPAsyncWebServer.h>

class WebSocketService
{
public:
    static bool SendData(WeatherData data);
    static void setup(AsyncWebServer *server);
};