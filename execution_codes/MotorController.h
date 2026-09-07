#ifndef MotorController_H
#define MotorController_H

// #define CMD_TX_PIN 39
// #define CMD_RX_PIN 37

// Rear Right
#define RR_PIN1 33
#define RR_PIN2 34
// Rear Left
#define RL_PIN1 35
#define RL_PIN2 36
// Front Right
#define FR_PIN1 37
#define FR_PIN2 38
// Front Left
#define FL_PIN1 39
#define FL_PIN2 40

void Stop();
void WheelsInit();
void MoveForward(int speed);
void MoveBackward(int speed);
void MoveRight(int speed);
void MoveLeft(int speed);
void TurnRight90();
void TurnLeft90();

#endif
