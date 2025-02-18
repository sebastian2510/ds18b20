#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebServerService.h>
#include <Pages.h>
#include <WebSocketService.h>

// Replace with your network credentials
const char *ssid = "REPLACE_WITH_YOUR_SSID";
const char *password = "REPLACE_WITH_YOUR_PASSWORD";

const char *PARAM_INPUT_1 = "output";
const char *PARAM_INPUT_2 = "state";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void WebServerService::setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println("WebServerService setup");

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", Pages::index_html); });

  // server.on("/login", HTTP_GET, [](AsyncWebServerRequest *request)
  //           { request->send(200, "text/html", Pages::login_html); });

  // Starting websocket server
  WebSocketService::setup(&server);
  // Start server
  server.begin();
}
