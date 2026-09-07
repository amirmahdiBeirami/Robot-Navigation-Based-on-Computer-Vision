
#include "MotorController.h"

void Stop()
{
  analogWrite(RR_PIN1, 0);
  analogWrite(RR_PIN2, 0);
  analogWrite(RL_PIN1, 0);
  analogWrite(RL_PIN2, 0);
  analogWrite(FR_PIN1, 0);
  analogWrite(FR_PIN2, 0);
  analogWrite(FL_PIN1, 0);
  analogWrite(FL_PIN2, 0);
}

void WheelsInit()
{
  pinMode(RR_PIN1, OUTPUT);
  pinMode(RR_PIN2, OUTPUT);
  pinMode(RL_PIN1, OUTPUT);
  pinMode(RL_PIN2, OUTPUT);
  pinMode(FR_PIN1, OUTPUT);
  pinMode(FR_PIN2, OUTPUT);
  pinMode(FL_PIN1, OUTPUT);
  pinMode(FL_PIN2, OUTPUT);

  Stop();
}

void MoveForward(int speed)
{
  analogWrite(RR_PIN1, speed+25);
  analogWrite(RR_PIN2, 0);
  
  analogWrite(RL_PIN1, speed);
  analogWrite(RL_PIN2, 0);
  
  analogWrite(FR_PIN1, speed+25);
  analogWrite(FR_PIN2, 0);

  analogWrite(FL_PIN1, speed);
  analogWrite(FL_PIN2, 0);
}

void MoveBackward(int speed)
{
  analogWrite(RR_PIN1, 0);
  analogWrite(RR_PIN2, speed);
  
  analogWrite(RL_PIN1, 0);
  analogWrite(RL_PIN2, speed);
  
  analogWrite(FR_PIN1, 0);
  analogWrite(FR_PIN2, speed);

  analogWrite(FL_PIN1, 0);
  analogWrite(FL_PIN2, speed);
}

void MoveRight(int speed)
{
  analogWrite(RR_PIN1, 0);
  analogWrite(RR_PIN2, speed);
  
  analogWrite(RL_PIN1, speed);
  analogWrite(RL_PIN2, 0);
  
  analogWrite(FR_PIN1, 0);
  analogWrite(FR_PIN2, speed);

  analogWrite(FL_PIN1, speed);
  analogWrite(FL_PIN2, 0);
}

void MoveLeft(int speed)
{
  analogWrite(RR_PIN1, speed+30);
  analogWrite(RR_PIN2, 0);
  
  analogWrite(RL_PIN1, 0);
  analogWrite(RL_PIN2, speed);
  
  analogWrite(FR_PIN1, speed);
  analogWrite(FR_PIN2, 0);

  analogWrite(FL_PIN1, 0);
  analogWrite(FL_PIN2, speed);
}

void TurnRight90()
{
  static int old_angle = angleZ;
  const int speed = 100;

  while (DistanceSensorRead(right) < 50) MoveForward(100);

  while (angleZ <= old_angle + 90)
  {
    analogWrite(RR_PIN1, 0);
    analogWrite(RR_PIN2, speed);

    analogWrite(RL_PIN1, speed);
    analogWrite(RL_PIN2, 0);

    analogWrite(FR_PIN1, 0);
    analogWrite(FR_PIN2, speed);

    analogWrite(FL_PIN1, speed);
    analogWrite(FL_PIN2, 0);
  }
  Stop();
}

void TurnLeft90()
{
  static int old_angle = angleZ;
  const int speed = 100;

  while (DistanceSensorRead(left) < 50) MoveForward(100);

  while (angleZ >= old_angle - 90)
  {
    analogWrite(RR_PIN1, speed+30);
    analogWrite(RR_PIN2, 0);

    analogWrite(RL_PIN1, 0);
    analogWrite(RL_PIN2, speed);

    analogWrite(FR_PIN1, speed);
    analogWrite(FR_PIN2, 0);

    analogWrite(FL_PIN1, 0);
    analogWrite(FL_PIN2, speed);
  }
  Stop();
}
