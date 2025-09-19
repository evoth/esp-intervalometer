#ifndef ESP_INT_CAMERA_H
#define ESP_INT_CAMERA_H

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

class CCAPI {
 public:
  char cameraIP[32];
  bool connected = false;
  bool shutterIsPressed = false;

  void connect(JsonDocument doc);
  int request(const char* method, const char* url, const char* body = "");
  void triggerShutter();
  void pressShutter();
  void releaseShutter();
  void executeAction(String name, String method, String url, JsonObject body);

 private:
  char apiUrl[64];
  char expSetting[16];
  const char* apiUrlTemplate = "http://%s:8080/ccapi";
  WiFiClient client;
  HTTPClient http;
};

#endif
