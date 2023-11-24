#include "server.h"

AsyncWebServerRequest *request;
bool newRequest;

void init_ap()
{
  const char *ssid = "ESP8266_AP";
  const char *password = "defgecd7";

  Serial.print("Starting soft-AP... ");
  WiFi.softAP(ssid, password);

  Serial.print("Soft-AP IP address: ");
  Serial.println(WiFi.softAPIP());
}

void init_web_server()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(200, "text/html", index_html);
  });

  server.on("/setTime", HTTP_POST, [](AsyncWebServerRequest *req) {}, NULL, set_time);

  server.on("/getTime", HTTP_GET, get_time);

  server.onNotFound([](AsyncWebServerRequest *req){
    request = req;
    newRequest = true;
  });

  server.begin();
}

void init_server() {
  init_ap();
  init_web_server();
}

void loop_process_request() {
  if (!newRequest) return;

  WebRequestMethodComposite method = request->method();
  String url = request->url();

  if (method == HTTP_GET && url == "/connect") {
    cameraConnect(request);
  } else {
    request->send(404, "text/plain", "Not found");
  }

  newRequest = false;
}