#include <WeatherData.h>
#include <ESPAsyncWebServer.h>

class WebSocketService
{
public:
    static void SendData(WeatherData data);
    static void setup(AsyncWebServer *server);
};