#include "camera.h"
#include "status.h"
#include <cstring>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

WiFiClient client;
HTTPClient http;

char cameraIP[32];
char apiUrl[64];
bool cameraConnected = false;
bool bulbMode = false;
char expSetting[16];
const char *apiUrlTemplate = "http://%s:8080/ccapi";
bool shutterIsPressed = false;

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
void cameraConnect(JsonDocument doc) {
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

// Sends a POST request to simulate pressing and holding the shutter
void pressShutter() {
  char endpointUrl[128];
  snprintf(endpointUrl, sizeof(endpointUrl), "%s/ver100/shooting/control/shutterbutton/manual", apiUrl);

  request(endpointUrl,
    []() {
      char body[] = "{\"action\":\"full_press\",\"af\": false}";
      return http.POST(body);
    },
    []() {
      snprintf(statusMsg, sizeof(statusMsg), "Successfully pressed shutter.");
      shutterIsPressed = true;
    },
    []() {
      if (statusCode < 0) {
        cameraConnected = false;
      }
    }
  );
}

// Sends a POST request to simulate releasing the shutter
void releaseShutter() {
  char endpointUrl[128];
  snprintf(endpointUrl, sizeof(endpointUrl), "%s/ver100/shooting/control/shutterbutton/manual", apiUrl);

  request(endpointUrl,
    []() {
      char body[] = "{\"action\":\"release\",\"af\": false}";
      return http.POST(body);
    },
    []() {
      snprintf(statusMsg, sizeof(statusMsg), "Successfully released shutter.");
      shutterIsPressed = false;
    },
    []() {
      if (statusCode < 0) {
        cameraConnected = false;
      }
    }
  );
}

// Retrieves shutter speed setting and sets variables appropriately
void getBulb() {
  char endpointUrl[128];
  snprintf(endpointUrl, sizeof(endpointUrl), "%s/ver100/shooting/settings/tv", apiUrl);

  request(endpointUrl,
    []() {
      return http.GET();
    },
    []() {
      JsonDocument response;
      deserializeJson(response, http.getString().c_str());
      if (response["value"] == String("bulb")) {
        bulbMode = true;
        // If we haven't yet stored an exposure setting, choose one from the ability list
        if (expSetting[0] == '\0') {
          snprintf(expSetting, sizeof(expSetting), response["ability"][1].as<String>().c_str());
        }
      } else {
        bulbMode = false;
        // Store exposure setting for future use
        snprintf(expSetting, sizeof(expSetting), response["value"].as<String>().c_str());
      }
    },
    []() {
      bulbMode = false;
    }
  );
}

// Set camera exposure to bulb
void enableBulb() {
  // Store current exposure setting
  getBulb();

  char endpointUrl[128];
  snprintf(endpointUrl, sizeof(endpointUrl), "%s/ver100/shooting/settings/tv", apiUrl);

  request(endpointUrl,
    []() {
      char body[] = "{\"value\": \"bulb\"}";
      return http.PUT(body);
    },
    []() {
      snprintf(statusMsg, sizeof(statusMsg), "Successfully enabled bulb mode.");
      bulbMode = true;
    },
    []() {}
  );
}

// Set camera exposure to previous setting
void disableBulb() {
  char endpointUrl[128];
  snprintf(endpointUrl, sizeof(endpointUrl), "%s/ver100/shooting/settings/tv", apiUrl);

  request(endpointUrl,
    []() {
      JsonDocument body;
      body["value"] = expSetting;
      String bodyText;
      serializeJson(body, bodyText);
      return http.PUT(bodyText);
    },
    []() {
      snprintf(statusMsg, sizeof(statusMsg), "Successfully disabled bulb mode.");
      bulbMode = false;
    },
    []() {}
  );
}

// Return exposure time in seconds from expSetting
// Example strings:
//   30"
//   2"5
//   1/60
float parseExpSetting() {
  float exp = atoi(expSetting);
  int len = strlen(expSetting);
  char *delim = strchr(expSetting, '"');
  if (delim == NULL) {
    delim = strchr(expSetting, '/');
    if (delim != NULL) {
      exp /= atoi(delim + 1);
    }
  } else if (delim - expSetting < len - 1) {
    exp += atoi(delim + 1) / 10.0f;
  }
  return exp;
}