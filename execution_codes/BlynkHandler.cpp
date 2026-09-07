#define NO_GLOBAL_INSTANCES
#include "BlynkHandler.h"

// const int trigPin = 17;
// const int echoPin = 16;
// long duration;
// float distanceCm;
// float distanceInch;

// Movements
BLYNK_WRITE(V1)
{
  if (param.asInt() == 1)
    MoveForward(100);    
  else
    Stop();
}

BLYNK_WRITE(V2)
{
  if (param.asInt() == 1)
    MoveLeft(100);
  else
    Stop();
}

BLYNK_WRITE(V3)
{
  if (param.asInt() == 1)
    MoveBackward(100);
  else
    Stop();
}

BLYNK_WRITE(V4)
{
  if (param.asInt() == 1)
    MoveRight(100);
  else
    Stop();
}

// Read Distance
BLYNK_READ(V5)
{

 // Clears the trigPin
  // digitalWrite(trigPin, LOW);
  // delayMicroseconds(2);
  // // Sets the trigPin on HIGH state for 10 micro seconds
  // digitalWrite(trigPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin, LOW);
  
  // // Reads the echoPin, returns the sound wave travel time in microseconds
  // duration = pulseIn(echoPin, HIGH);
  
  // // Calculate the distance
  // distanceCm = duration * SOUND_SPEED/2;

  // Blynk.virtualWrite(V5, distanceCm);
}

// Read Angles
BLYNK_READ(V6)
{
  angleX = mpu.getAngle('X', KALMAN);
  angleY = mpu.getAngle('Y', KALMAN);
    
  Blynk.virtualWrite(V6, angleZ);
}

BLYNK_WRITE(V7)
{
  if (param.asInt() == 1)
    mpu.zeroAngles();
}