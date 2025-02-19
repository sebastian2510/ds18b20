#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebServerService.h>
#include <nlohmann/json.hpp>
#include <Models/WeatherData.h>
#include <iostream>
#include <WebSocketService.h>
AsyncWebSocket ws("/ws");

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
    }
    else if (type == WS_EVT_ERROR)
    {
        Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
    }
    else if (type == WS_EVT_PONG)
    {
        Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char *)data : "none");
    }
}


void WebSocketService::SendData(WeatherData data)
{

    for (auto& client : ws.getClients())
    {
        Serial.println("Client: " + String(client.id()));
    }

    Serial.println(data.getTemperature());
    String json = "{\"Temperature\": " + String(data.getTemperature()) + ", \"TimeStamp\": \"" + String(data.getTimeStamp().c_str()) + "\"}";
    Serial.println(json);
    ws.textAll(json);
}

void WebSocketService::setup(AsyncWebServer *server)
{
    try
    {
        ws.onEvent(onWsEvent);
        server->addHandler(&ws);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}