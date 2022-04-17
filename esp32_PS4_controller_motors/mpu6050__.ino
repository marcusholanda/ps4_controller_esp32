#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void mpu_init(void) {


  Serial.println("MPU6050 init");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}


float get_theta_speed(){  //in degrees

	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);
	float theta = g.gyro.z * 180 / 3.14; 
	return theta;
}
