
#ifndef DistanceSensor_H
#define DistanceSensor_H

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

struct UltraSonic_t {
  int TrigPin, EchoPin;
} front{17, 16}, left{3,2}, right{4,5};

void DistanceSensorInit(UltraSonic_t sensor);
float DistanceSensorRead(UltraSonic_t sensor);

#endif