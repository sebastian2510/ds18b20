#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class Pages
{
public:
    static const char index_html[] PROGMEM;
    static const char login_html[] PROGMEM;
};
