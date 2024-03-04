/* <---------------------------------------------------> */

// Variables Sensor UV
float sensor_voltage;
float sensor_value;
unsigned long id_sensor_uv = 1;

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

unsigned long id_temperatura = 1;
unsigned long id_presion = 1;

//Variables MicroSD
#include <SPI.h>
#include <SD.h>

#define SSpin 10
File archivo;

/* <---------------------------------------------------> */

void setup() {
  Serial.begin(9600);
  Serial.println("Inicio Setup");
  //Setup Sensor UV
  pinMode(A1, OUTPUT);

  //Setup Sensor MPU6050
  Wire.begin();
  Serial.println("Pre MPU");
  //byte status = mpu.begin();
  //while(status!=0){ }
  Serial.println("MPU Pasado");
  
  delay(1000);
  //mpu.calcOffsets(true,true);

  Serial.println("Pre BMP");
  //Setup Sensor BMP280
  //if ( !bmp.begin() ) while (1);
  Serial.println("BMP Pasado");
  Serial.println("Pre SD");

  //Setup MicroSD
  if ( !SD.begin(SSpin)) {
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;					// se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");
}

void loop() {
  sensor_uv();

  //sensor_MPU_6050();

  //sensor_BMP_280();
}

/* <---------------------------------------------------> */

void sensor_uv()
{
  Serial.println("Sensor UV ");
  sensor_value = analogRead(A1);
  sensor_voltage = sensor_value / 1024 * 5.0;

  if(guardar_datos(sensor_voltage, id_sensor_uv, "sensorUV.txt")) id_sensor_uv++;
  Serial.println(sensor_voltage);
}

void sensor_MPU_6050()
{
  //mpu.update();

  //aceleracion_en_x = mpu.getAccX();
  //aceleracion_en_y = mpu.getAccY();
  //aceleracion_en_z = mpu.getAccZ();

  //giroscopio_en_x = mpu.getGyroX();
  //giroscopio_en_y = mpu.getGyroY();
  //giroscopio_en_z = mpu.getGyroZ();

  //aceleracion_en_angulo_x = mpu.getAccAngleX();
  //aceleracion_en_angulo_y = mpu.getAccAngleY();

  //angulo_en_x = mpu.getAngleX();
  //angulo_en_y = mpu.getAngleY();
  //angulo_en_z = mpu.getAngleZ();
}

void sensor_BMP_280()
{
  //temperatura = bmp.readTemperature();
  //presion = bmp.readPressure()/100;

  //if(guardar_datos(temperatura, id_temperatura, "temperatura.txt")) id_temperatura++;
  //if(guardar_datos(presion, id_presion, "presion.txt")) id_presion++;
}

bool guardar_datos(float valor, int id, String nombre_archivo){
  Serial.print("ID: ");
  Serial.println(id);
  Serial.print("VALOR: ");
  Serial.println(valor);
  archivo = SD.open((String) nombre_archivo, FILE_WRITE);
    if (archivo) { //DATALOG
      archivo.print("ID: ");
      archivo.println(id);
      archivo.print("VALOR: ");
      archivo.println(valor);
      archivo.close();
      Serial.print("Archivo guardado: ");
      Serial.println((String) nombre_archivo);
      return 1;
    }
  Serial.println(archivo);
  Serial.println("Archivo NO guardado: ");
  return 0;
}