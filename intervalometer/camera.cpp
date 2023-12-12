#include "camera.h"

char apiUrl[64];
bool cameraConnected = false;
const char *apiUrlTemplate = "http://%s:8080/ccapi";
const char *apiVersion = "ver100";
int errorCode = 200;
char errorMsg[256];

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
      String payload = http.getString();
      snprintf(msg, sizeof(msg), "Error payload from %s: %s", url, payload.c_str());
    } else {
      snprintf(msg, sizeof(msg), "Error %d at %s", httpCode, url);
    }
    request->send(502, "text/plain", msg);
    http.end();
    return false;
  }

  return true;
}

bool post(const char *url, char *body) {
  // HTTP connection could not be started
  if (!http.begin(client, url)) {
    snprintf(errorMsg, sizeof(errorMsg), "Could not connect to %s", url);
    errorCode = 502;
    return false;
  }

  int httpCode = http.POST(body);

  // HTTP client error
  if (httpCode < 0) {
    snprintf(errorMsg, sizeof(errorMsg), "%s when connecting to %s", http.errorToString(httpCode).c_str(), url);
    errorCode = 502;
    http.end();
    return false;
  }

  // HTTP failure code
  if (httpCode != HTTP_CODE_OK) {
    if (http.getSize() > 0) {
      String payload = http.getString();
      snprintf(errorMsg, sizeof(errorMsg), "Error payload from %s: %s", url, payload.c_str());
    } else {
      snprintf(errorMsg, sizeof(errorMsg), "Error %d at %s", httpCode, url);
    }
    errorCode = 502;
    http.end();
    return false;
  }

  return true;
}

// Sends a GET request to base CCAPI URL to establish connection
void cameraConnect(AsyncWebServerRequest *request, DynamicJsonDocument doc) {
  String cameraIP = doc["cameraIP"];
  snprintf(apiUrl, sizeof(apiUrl), apiUrlTemplate, cameraIP.c_str());

  if (!connect(request, apiUrl)) {
    cameraConnected = false;
    return;
  }
  
  request->send(200, "text/plain", "Connection to camera successful.");

  http.end();

  cameraConnected = true;
}

// Sends a GET request to base CCAPI URL to establish connection
void triggerShutter() {
  char endpointUrl[128];
  snprintf(endpointUrl, sizeof(endpointUrl), "%s/ver100/shooting/control/shutterbutton", apiUrl);

  char body[] = "{\"af\": false}";
  if (!post(endpointUrl, body)) return;

  errorCode = 200;
  snprintf(errorMsg, sizeof(errorMsg), "Successfully triggered shutter.");

  http.end();
}