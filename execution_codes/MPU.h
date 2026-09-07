#ifndef MPU_H
#define MPU_H

#include <mpu6050_FastAngles.h>

extern mpu6050_FastAngles mpu;
extern float angleX;
extern float angleY;
extern float angleZ;

void MPU_Init();

#endif
