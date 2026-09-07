
#define LED_PIN 15
#define CAMERA_RST 1

#include "TCPHandler.h"
#include "BlynkHandler.h"
#include "MPU.h"
#include "DistanceSensor.h"

float angleX;
float angleY;
float angleZ;

TaskHandle_t ctHandle = NULL;

void setup() 
{
  // Create WiFi AP with desired SSID (and password if needed)
  WiFi.softAP(SSID);

  // Robot Initializations
  WheelsInit();
  MPU_Init();

  DistanceSensorInit(front);
  DistanceSensorInit(left);
  DistanceSensorInit(right);

  OTAInit(); // Start the OTA

  // Reset the camera module
  pinMode(CAMERA_RST, OUTPUT);
  digitalWrite(CAMERA_RST, LOW);
  delay(100);
  digitalWrite(CAMERA_RST, HIGH);

  server.begin(); // Start the TCP server
  Blynk.config(BLYNK_AUTH_TOKEN,HOST,PORT); // Set Blynk Server Config
  xTaskCreate(client_runner, "ClientTask", 10000, NULL, 1, &ctHandle); // Creating a new Task to handle the TCP server
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void loop()
{
  Blynk.run();

  angleZ = mpu.getAngle('Z');

  delay(1);
}
