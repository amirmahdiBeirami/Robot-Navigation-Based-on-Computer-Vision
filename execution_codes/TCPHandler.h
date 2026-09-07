#ifndef TCPHandler_H
#define TCPHandler_H

#include <WiFi.h>
#include "MotorController.h"
#include "OTA.h"

#define SSID "rc"
#define PASSWORD "87654321s"
#define SERVER_PORT 1234

WiFiServer server(SERVER_PORT);
void client_runner(void * parameter);

#endif
