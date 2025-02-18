#include <TestWeatherData.h>
#include <ESPAsyncWebServer.h>

class WebSocketService
{
public:
    static void SendData(TestWeatherData data);
    static void setup(AsyncWebServer *server);
};