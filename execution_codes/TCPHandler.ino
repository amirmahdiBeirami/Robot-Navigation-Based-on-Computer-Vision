#include "TCPHandler.h"

void client_runner(void * parameter)
{
  while (1)
  {
    WiFiClient client = server.available();
    if (client)
    {
      while (client.connected()) 
      {
        if (client.available()) 
        {
          String command = client.readStringUntil('\r');

          if (command == "FORWARD1") {
            digitalWrite(LED_PIN, LOW);
            MoveForward(100);
          }
          else if (command == "BACKWARD1") {
            digitalWrite(LED_PIN, LOW);
            MoveBackward(100); 
          }
          else if (command == "RIGHT1") {
            digitalWrite(LED_PIN, LOW);
            MoveRight(100);
          }
          else if (command == "LEFT1") {
            digitalWrite(LED_PIN, LOW);
            MoveLeft(100);
          }
          else if (command == "FORWARD30") {
            digitalWrite(LED_PIN, LOW);
            MoveForward(30);
          }
          else if (command == "FORWARD60") {
            digitalWrite(LED_PIN, LOW);
            MoveForward(60);
          }
          else if (command == "TURNLEFT90") {
            digitalWrite(LED_PIN, LOW);
            TurnLeft90();
          }
          else if (command == "TURNRIGHT90") {
            digitalWrite(LED_PIN, LOW);
            TurnRight90(100);
          }   
          else if (command == "STOP") {
            digitalWrite(LED_PIN, HIGH);
            Stop();
          }
          else if (command == "bye") {
            Stop();
            break;
          }                                        
        }
      }
    }
    ArduinoOTA.handle();
    delay(1);
  }
}
