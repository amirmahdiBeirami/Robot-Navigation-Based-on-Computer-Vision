#include "MPU.h"

mpu6050_FastAngles mpu;

void MPU_Init()
{
  mpu.begin(MPU_MODE_250);
  mpu.setComplementaryFactor(0.98);

  mpu.setKalmanQangle(0.001);
  mpu.setKalmanQbias(0.003);
  mpu.setKalmanRmeasure(0.03);
}
