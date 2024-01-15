#include "camera.h"

char cameraIP[32];
char apiUrl[64];
bool cameraConnected = false;
const char *apiUrlTemplate = "http://%s:8080/ccapi";

// Helper function that sets up HTTP connection before running the "action" function
// (e.g. http.GET(), http.POST(), etc.), then runs either the success or failure
// functions depending on the returned status code.
void request(const char *url, std::function<int()> action, std::function<void()> success, std::function<void()> failure) {
  // Indicates semantic error like malformed URL
  if (!http.begin(client, url)) {
    snprintf(statusMsg, sizeof(statusMsg), "Could not connect to %s", url);
    statusCode = HTTPC_ERROR_CONNECTION_FAILED;
    failure();
    return;
  }

  int httpCode = action();
  statusCode = httpCode;

  // HTTP client error
  if (httpCode < 0) {
    snprintf(statusMsg, sizeof(statusMsg), "%s when connecting to %s", http.errorToString(httpCode).c_str(), url);
    http.end();
    failure();
    return;
  }

  // HTTP failure code
  if (httpCode != HTTP_CODE_OK) {
    if (http.getSize() > 0) {
      String payload = http.getString();
      snprintf(statusMsg, sizeof(statusMsg), "Error payload from %s: %s", url, payload.c_str());
    } else {
      snprintf(statusMsg, sizeof(statusMsg), "Error %d at %s", httpCode, url);
    }
    http.end();
    failure();
    return;
  }

  success();

  http.end();
}

// Sends a GET request to base CCAPI URL to establish connection
void cameraConnect(DynamicJsonDocument doc) {
  String cameraIPTemp = doc["cameraIP"];
  snprintf(cameraIP, sizeof(cameraIP), cameraIPTemp.c_str());
  snprintf(apiUrl, sizeof(apiUrl), apiUrlTemplate, cameraIP);

  request(apiUrl,
    []() {
      return http.GET();
    },
    []() {
      snprintf(statusMsg, sizeof(statusMsg), "Successfully connected to camera.");
      cameraConnected = true;
    },
    []() {
      cameraConnected = false;
    }
  );
}

// Sends a POST request to trigger the shutter
void triggerShutter() {
  char endpointUrl[128];
  snprintf(endpointUrl, sizeof(endpointUrl), "%s/ver100/shooting/control/shutterbutton", apiUrl);

  request(endpointUrl,
    []() {
      char body[] = "{\"af\": false}";
      return http.POST(body);
    },
    []() {
      snprintf(statusMsg, sizeof(statusMsg), "Successfully triggered shutter.");
    },
    []() {
      if (statusCode < 0) {
        cameraConnected = false;
      }
    }
  );
}