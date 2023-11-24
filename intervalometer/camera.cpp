#include "camera.h"

const char *apiUrl = "http://192.168.4.7:8080/ccapi";
const char *apiVersion = "ver100";

// Attempts to start an HTTP connection and request the given url
// Sends error message and returns false if error; otherwise returns true
bool connect(AsyncWebServerRequest *request, const char *url) {
  // HTTP connection could not be started
  if (!http.begin(client, url)) {
    char msg[256];
    snprintf(msg, sizeof(msg), "Could not connect to %s", url);
    request->send(502, "text/plain", msg);
    return false;
  }

  int httpCode = http.GET();

  // HTTP client error
  if (httpCode < 0) {
    char msg[256];
    snprintf(msg, sizeof(msg), "%s when connecting to %s", http.errorToString(httpCode).c_str(), url);
    request->send(502, "text/plain", msg);
    http.end();
    return false;
  }

  // HTTP failure code
  if (httpCode != HTTP_CODE_OK) {
    char msg[256];
    if (http.getSize() > 0) {
      // CCAPI error message from response JSON
      String payload = http.getString();
      DynamicJsonDocument doc(256);
      deserializeJson(doc, payload);
      snprintf(msg, sizeof(msg), "%s at %s", doc["message"], url);
    } else {
      snprintf(msg, sizeof(msg), "Error %d at %s", httpCode, url);
    }
    request->send(502, "text/plain", msg);
    http.end();
    return false;
  }

  return true;
}

// Sends a GET request to base CCAPI URL to establish connection
void cameraConnect(AsyncWebServerRequest *request) {
  if (!connect(request, apiUrl)) return;
  
  request->send(200, "text/plain", "Connection to camera successful.");

  http.end();
}