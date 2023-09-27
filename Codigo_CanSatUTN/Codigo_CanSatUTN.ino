// Variables Sensor UV
float sensor_voltage;
float sensor_value;

//Librerias Sensor MPU6050
#include "Wire.h"
#include <MPU6050_light.h>

//Variables Sensor MPU6050
MPU6050 mpu(Wire);

float aceleracion_en_x = 0;
float aceleracion_en_y = 0;
float aceleracion_en_z = 0;

float  giroscopio_en_x = 0;
float  giroscopio_en_y = 0;
float  giroscopio_en_z = 0;

float  aceleracion_en_angulo_x = 0;
float  aceleracion_en_angulo_y = 0;

float  angulo_en_x = 0;
float  angulo_en_y = 0;
float  angulo_en_z = 0;

//Librerias Sensor BMP280
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

//Variables Sensor BMP280
Adafruit_BMP280 bmp;
float temperatura;
float presion;

//Variables MicroSD
#include <SD.h>
#define SSpin 9
File archivo;

/* <---------------------------------------------------> */

void setup() {

  //Setup Sensor UV
  pinMode(A1, OUTPUT);

  //Setup Sensor MPU6050
  Wire.begin();
  
  byte status = mpu.begin();
  while(status!=0){ }
  
  delay(1000);
  mpu.calcOffsets(true,true);

  //Setup Sensor BMP280
  if ( !bmp.begin() ) {
    while (1);
  }

  //Setup MicroSD
  if (!SD.begin(SSpin)) {}
}

void loop() {
  sensor_uv();

  sensor_MPU_6050();

  sensor_BMP_280();


  archivo = SD.open("datalog.txt", FILE_WRITE);
    if (archivo) { //DATALOG
      archivo.println("Comezando grabado de datos. ");
      archivo.close();
    }
}

void sensor_uv()
{
  sensor_value = analogRead(A1);
  sensor_voltage = sensor_value / 1024 * 5.0;
}

void sensor_MPU_6050()
{
  mpu.update();

  aceleracion_en_x = mpu.getAccX();
  aceleracion_en_y = mpu.getAccY();
  aceleracion_en_z = mpu.getAccZ();

  giroscopio_en_x = mpu.getGyroX();
  giroscopio_en_y = mpu.getGyroY();
  giroscopio_en_z = mpu.getGyroZ();

  aceleracion_en_angulo_x = mpu.getAccAngleX();
  aceleracion_en_angulo_y = mpu.getAccAngleY();

  angulo_en_x = mpu.getAngleX();
  angulo_en_y = mpu.getAngleY();
  angulo_en_z = mpu.getAngleZ();

}

void sensor_BMP_280()
{
  temperatura = bmp.readTemperature();
  presion = bmp.readPressure()/100;
}