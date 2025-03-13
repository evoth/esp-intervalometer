#include "camera.h"
#include <cstring>
#include "status.h"

// Helper function that sets up HTTP connection before running the "action"
// function (e.g. http.GET(), http.POST(), etc.), then runs either the success
// or failure functions depending on the returned status code.
int Camera::request(const char* method, const char* url, const char* body) {
  // Indicates semantic error like malformed URL
  if (!http.begin(client, url)) {
    snprintf(statusMsg, sizeof(statusMsg), "Could not connect to %s", url);
    statusCode = HTTPC_ERROR_CONNECTION_FAILED;
    return statusCode;
  }

  int httpCode = 0;
  if (strcmp(method, "POST") == 0) {
    httpCode = http.POST(body);
  } else if (strcmp(method, "PUT") == 0) {
    httpCode = http.PUT(body);
  } else if (strcmp(method, "GET") == 0) {
    httpCode = http.GET();
  }

  statusCode = httpCode;

  // HTTP client error
  if (httpCode < 0) {
    snprintf(statusMsg, sizeof(statusMsg), "%s when connecting to %s",
             http.errorToString(httpCode).c_str(), url);
    http.end();
    connected = false;
    return statusCode;
  }

  // HTTP failure code
  if (httpCode != HTTP_CODE_OK) {
    if (http.getSize() > 0) {
      String payload = http.getString();
      snprintf(statusMsg, sizeof(statusMsg), "Error payload from %s: %s", url,
               payload.c_str());
    } else {
      snprintf(statusMsg, sizeof(statusMsg), "Error %d at %s", httpCode, url);
    }
    http.end();
    return statusCode;
  }

  http.end();
  return statusCode;
}

// Sends a GET request to base CCAPI URL to establish connection
void Camera::connect(JsonDocument doc) {
  String cameraIPTemp = doc["cameraIP"];
  snprintf(cameraIP, sizeof(cameraIP), cameraIPTemp.c_str());
  snprintf(apiUrl, sizeof(apiUrl), apiUrlTemplate, cameraIP);

  if (request("GET", apiUrl) != HTTP_CODE_OK) {
    connected = false;
    return;
  }

  snprintf(statusMsg, sizeof(statusMsg), "Successfully connected to camera.");
  connected = true;
}

// Sends a POST request to trigger the shutter
void Camera::triggerShutter() {
  char endpointUrl[128];
  snprintf(endpointUrl, sizeof(endpointUrl),
           "%s/ver100/shooting/control/shutterbutton", apiUrl);

  if (request("POST", endpointUrl, "{\"af\": false}") != HTTP_CODE_OK)
    return;

  snprintf(statusMsg, sizeof(statusMsg), "Successfully triggered shutter.");
}

// Sends a POST request to simulate pressing and holding the shutter
void Camera::pressShutter() {
  char endpointUrl[128];
  snprintf(endpointUrl, sizeof(endpointUrl),
           "%s/ver100/shooting/control/shutterbutton/manual", apiUrl);

  if (request("POST", endpointUrl,
              "{\"action\":\"full_press\",\"af\": false}") != HTTP_CODE_OK)
    return;

  snprintf(statusMsg, sizeof(statusMsg), "Successfully pressed shutter.");
  shutterIsPressed = true;
}

// Sends a POST request to simulate releasing the shutter
void Camera::releaseShutter() {
  char endpointUrl[128];
  snprintf(endpointUrl, sizeof(endpointUrl),
           "%s/ver100/shooting/control/shutterbutton/manual", apiUrl);

  if (request("POST", endpointUrl, "{\"action\":\"release\",\"af\": false}") !=
      HTTP_CODE_OK)
    return;

  snprintf(statusMsg, sizeof(statusMsg), "Successfully released shutter.");
  shutterIsPressed = false;
}

// Sends a POST request to simulate releasing the shutter
void Camera::executeAction(String name,
                           String method,
                           String url,
                           String body) {
  char endpointUrl[128];
  snprintf(endpointUrl, sizeof(endpointUrl), "%s%s", apiUrl, url.c_str());

  if (request(method.c_str(), endpointUrl, body.c_str()) != HTTP_CODE_OK)
    return;

  snprintf(statusMsg, sizeof(statusMsg), "Successfully executed '%s' action.",
           name.c_str());
  shutterIsPressed = false;
}