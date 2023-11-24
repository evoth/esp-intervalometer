#include "server.h"

void setup()
{
  Serial.begin(115200);
  Serial.println();
  init_server();
}

void loop()
{
  loop_process_request();
}
