#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int estado = 0;
unsigned long tiempoEstado = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("Error de conexión con el MPU6050");
    while (1);
  }

  Serial.println("Detector de caídas iniciado.");
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Convertir a g
  float accelX = ax / 16384.0;
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;

  float totalAccel = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ);

  float roll = atan2(accelY, accelZ) * 180.0 / PI;
  float pitch = atan2(-accelZ, sqrt(accelX * accelX + accelY * accelY)) * 180.0 / PI;

  Serial.print("AX: "); Serial.print(accelX);
  Serial.print(" AY: "); Serial.print(accelY);
  Serial.print(" AZ: "); Serial.print(accelZ);
  Serial.print(" | Roll: "); Serial.print(roll);
  Serial.print(" Pitch: "); Serial.print(pitch);
  Serial.print(" | Estado: "); Serial.println(estado);

  switch (estado) {
    case 0: // En reposo (de pie)
      if (abs(accelX) < 0.6) {  // Si cae la aceleración en X
        estado = 1;
        tiempoEstado = millis();
      }
      break;

    case 1: // Sospecha de caída
      if (totalAccel > 1.8) {
        estado = 2;
        tiempoEstado = millis();
      } else if (millis() - tiempoEstado > 1500) {
        estado = 0;
      }
      break;

    case 2: // Golpe detectado
      if ((abs(accelX) < 0.4 || abs(accelX) > 1.3) && millis() - tiempoEstado > 500) {
        estado = 3;
        tiempoEstado = millis();
      } else if (millis() - tiempoEstado > 2000) {
        estado = 0;
      }
      break;

    case 3: // Confirmación de caída
      Serial.println("⚠️ ¡CAÍDA DETECTADA!");
      estado = 0;
      break;
  }

  delay(200);
}
