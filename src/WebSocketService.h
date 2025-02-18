#include <Data.h>
#include <ESPAsyncWebServer.h>

class WebSocketService
{
public:
    static void SendData(Data data);
    static void setup(AsyncWebServer *server);
};