// Variables Sensor UV
float sensorVoltage;
float sensorValue;

//Librerias Sensor MPU6050
#include "Wire.h"
#include <MPU6050_light.h>

//Variables Sensor MPU6050
MPU6050 mpu(Wire);
long timer = 0;

//Librerias Sensor BMP280
//#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

//Variables Sensor BMP280
Adafruit_BMP280 bmp;
float TEMPERATURA;
float PRESION;

void setup() {
  //Setup Sensor UV
  Serial.begin(9600);
  Serial.println("Setup Sensor UV");
  pinMode(A1, OUTPUT);

  //Setup Sensor MPU6050
  //Serial.begin(9600);
  Serial.println("Setup Sensor MPU6050");
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ }
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true,true);
  Serial.println("Done!\n");

  //Setup Sensor BMP280
  //Serial.begin(9600);
  Serial.println("Setup Sensor BMP280");
  Serial.println("Iniciando:");
  if ( !bmp.begin() ) {
    Serial.println("BMP280 no encontrado !");
    while (1);
  }
}

void loop() {
  //loop Sensor UV
  Serial.println("Loop Sensor UV");
  sensor_uv();

  Serial.println("Loop Sensor MPU6050");
  sensor_MPU_6050();

  Serial.println("Loop Sensor BMP280");
  sensor_BMP_280();
}

void sensor_uv()
{
  sensorValue = analogRead(A1);
  sensorVoltage = sensorValue / 1024 * 5.0;
  Serial.print("sensor reading = ");
  Serial.print(sensorValue);
  Serial.print(" sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  delay(1000);
}

void sensor_MPU_6050()
{
  mpu.update();

  if(millis() - timer > 1000){ // print data every second
    Serial.print(F("TEMPERATURE: "));Serial.println(mpu.getTemp());
    Serial.print(F("ACCELERO  X: "));Serial.print(mpu.getAccX());
    Serial.print("\tY: ");Serial.print(mpu.getAccY());
    Serial.print("\tZ: ");Serial.println(mpu.getAccZ());
  
    Serial.print(F("GYRO      X: "));Serial.print(mpu.getGyroX());
    Serial.print("\tY: ");Serial.print(mpu.getGyroY());
    Serial.print("\tZ: ");Serial.println(mpu.getGyroZ());
  
    Serial.print(F("ACC ANGLE X: "));Serial.print(mpu.getAccAngleX());
    Serial.print("\tY: ");Serial.println(mpu.getAccAngleY());
    
    Serial.print(F("ANGLE     X: "));Serial.print(mpu.getAngleX());
    Serial.print("\tY: ");Serial.print(mpu.getAngleY());
    Serial.print("\tZ: ");Serial.println(mpu.getAngleZ());
    Serial.println(F("=====================================================\n"));
    timer = millis();
  }
}

void sensor_BMP_280()
{
  TEMPERATURA = bmp.readTemperature();
  PRESION = bmp.readPressure()/100;
  Serial.print("Temperatura: ");
  Serial.print(TEMPERATURA);
  Serial.print(" C ");
    
  Serial.print("Presion: ");
  Serial.print(PRESION);
  Serial.println(" hPa");

  delay(5000);
}
