#include "server.h"

AsyncWebServerRequest *request;
DynamicJsonDocument doc(1024);
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

void queue_loop_request(AsyncWebServerRequest *req, uint8_t *data, size_t len, size_t index, size_t total) {
  request = req;
  newRequest = true;
  deserializeJson(doc, data);
}

void init_web_server()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(200, "text/html", index_html);
  });

  server.on("/icon.svg", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(200, "image/svg+xml", icon_svg);
  });

  server.on("/setTime", HTTP_POST, [](AsyncWebServerRequest *req) {}, NULL, set_time);

  server.on("/getTime", HTTP_GET, get_time);

  server.on("/connect", HTTP_POST, [](AsyncWebServerRequest *req) {}, NULL, queue_loop_request);

  server.on("/start", HTTP_POST, [](AsyncWebServerRequest *req) {}, NULL, queue_loop_request);

  server.on("/stop", HTTP_GET, stopIntervalometer);

  server.on("/getStatus", HTTP_GET, getIntervalometerStatus);

  server.onNotFound([](AsyncWebServerRequest *req){
    request = req;
    newRequest = true;
  });

  // CORS
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Credentials", "true");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET,HEAD,OPTIONS,POST,PUT");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Access-Control-Allow-Headers, Origin,Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Access-Control-Request-Headers");

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

  if (method == HTTP_POST && url == "/connect") {
    cameraConnect(request, doc);
  } else if (method == HTTP_POST && url == "/start") {
    startIntervalometer(request, doc);
  } else if (method == HTTP_OPTIONS) {
    request->send(200);
  } else {
    request->send(404, "text/plain", "Not found");
  }

  newRequest = false;
}