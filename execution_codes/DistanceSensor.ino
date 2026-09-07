#include "DistanceSensor.h"

void DistanceSensorInit(UltraSonic_t sensor)
{
  pinMode(sensor.TrigPin, OUTPUT);
  pinMode(sensor.EchoPin, INPUT);
}

float DistanceSensorRead(UltraSonic_t sensor)
{
  long duration;
  digitalWrite(sensor.TrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(sensor.TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor.TrigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(sensor.EchoPin, HIGH);
  
  return duration * SOUND_SPEED/2;
}
