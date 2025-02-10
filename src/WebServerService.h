#include <Arduino.h>

class WebServerService
{
public:
    String processor(const String &var);
    String outputState(int output);
    static void setup();
};