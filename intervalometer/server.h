#ifndef SERVER_H
#define SERVER_H

#include <ESPAsyncWebServer.h>
#include <ESPAsyncUDP.h>
#include <ESP8266HTTPClient.h>

#include "global.h"
#include "webpage.h"
#include "time.h"
#include "camera.h"

extern void init_server();

extern void loop_process_request();

#endif