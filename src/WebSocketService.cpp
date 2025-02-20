#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebServerService.h>
#include <nlohmann/json.hpp>
#include <Models/WeatherData.h>
#include <iostream>
#include <WebSocketService.h>
AsyncWebSocket ws("/ws");

/**
 * @brief Handles WebSocket events.
 * 
 * This function is called whenever a WebSocket event occurs. It processes
 * different types of WebSocket events such as connection, disconnection,
 * errors, and pong responses.
 * 
 * @param server Pointer to the AsyncWebSocket server instance.
 * @param client Pointer to the AsyncWebSocketClient instance.
 * @param type The type of WebSocket event (e.g., WS_EVT_CONNECT, WS_EVT_DISCONNECT, WS_EVT_ERROR, WS_EVT_PONG).
 * @param arg Additional arguments associated with the event.
 * @param data Pointer to the data associated with the event.
 * @param len Length of the data.
 */
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


/**
 * @brief Sends weather data to all connected WebSocket clients.
 * 
 * This function iterates through all connected WebSocket clients and sends
 * the provided weather data in JSON format. It also prints the client IDs
 * and the weather data to the serial monitor for debugging purposes.
 * 
 * @param data The WeatherData object containing the temperature and timestamp
 *             to be sent to the clients.
 */
bool WebSocketService::SendData(WeatherData data)
{
    if (ws.count() == 0 || ws.getClients().size() == 0)
    {
        Serial.println(ws.count());
        Serial.println(ws.getClients().size());
        return false;
    }

    String json = "{\"Temperature\": " + String(data.getTemperature()) + ", \"TimeStamp\": \"" + String(data.getTimeStamp().c_str()) + "\"}";
    Serial.println(json);
    ws.textAll(json);
    return true;
}

/**
 * @brief Sets up the WebSocket service by attaching the WebSocket event handler to the provided server.
 * 
 * This function initializes the WebSocket service by setting the event handler and adding the WebSocket
 * handler to the provided asynchronous web server. It also includes exception handling to catch and log
 * any errors that may occur during the setup process.
 * 
 * @param server A pointer to the AsyncWebServer instance to which the WebSocket handler will be added.
 */
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