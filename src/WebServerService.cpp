#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebServerService.h>
#include <Pages.h>
#include <WebSocketService.h>
#include <SPIFFS.h>
#include <FileManager.h>
#include <vector>
#include <models/WeatherData.h>
#include <APService.h>

const char *PARAM_INPUT_1 = "output";
const char *PARAM_INPUT_2 = "state";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void WebServerService::setup(std::vector<WeatherData> &data)
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println("WebServerService setup");

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", Pages::index_html); });

  // Route to get data.json
  server.on("/data", HTTP_GET, [&data](AsyncWebServerRequest *request)
            { request->send(200, "application/json", FileManager::ConvertDataToJson(data).dump().c_str()); });

    server.on("/reset-wifi", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(200, "text/html", "Resetting WiFi...");
              APService::Disconnect();
              APService::setup();
            });

  // server.on("/login", HTTP_GET, [](AsyncWebServerRequest *request)
  //           { request->send(200, "text/html", Pages::login_html); });

  // Starting websocket server
  WebSocketService::setup(&server);
  // Start server
  server.begin();
}
