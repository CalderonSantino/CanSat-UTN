float sensorVoltage;
float sensorValue;

void setup() {
  Serial.begin(9600);
  pinMode(A1, OUTPUT);
}

void loop() {
  sensorValue = analogRead(A1);
  sensorVoltage = sensorValue / 1024 * 5.0;
  Serial.print("sensor reading = ");
  Serial.print(sensorValue);
  Serial.print(" sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  delay(1000);
}