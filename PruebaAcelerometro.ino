  #include "I2Cdev.h"
  #include "MPU6050.h"
  #include "Wire.h"

  const int mpuAddress = 0x68;  // Dirección I2C del MPU6050
  MPU6050 mpu(mpuAddress);

  int16_t ax, ay, az;  // Deben ser int16_t, no int
  int16_t gx, gy, gz;

  const float accScale = 2.0 * 9.81 / 32768.0; // Sensibilidad 2g
  const float gyroScale = 250.0 / 32768.0;     // Sensibilidad 250 °/s

  void setup() {
    Serial.begin(9600);
    Wire.begin();  // Confirma los pines correctos

    mpu.initialize();
    mpu.setSleepEnabled(false);  // Desactivar modo SLEEP

    // 🔹 Prueba forzando una primera lectura "vacía"
    mpu.getAcceleration(&ax, &ay, &az);
    mpu.getRotation(&gx, &gy, &gz);
    delay(100);  // Espera un poco

    if (mpu.testConnection()) {
        Serial.println("✅ Sensor iniciado correctamente");
    } else {
        Serial.println("⚠️ Error al iniciar el sensor");
    }
}


  void loop() {   
      mpu.getAcceleration(&ax, &ay, &az);
      mpu.getRotation(&gx, &gy, &gz);

      Serial.print("Valores RAW - a[");
      Serial.print(ax); Serial.print(", ");
      Serial.print(ay); Serial.print(", ");
      Serial.print(az); Serial.print("] g[");
      Serial.print(gx); Serial.print(", ");
      Serial.print(gy); Serial.print(", ");
      Serial.print(gz); Serial.println("]");

      Serial.print("Valores normalizados - a[");
      Serial.print(ax * accScale, 4); Serial.print(", ");
      Serial.print(ay * accScale, 4); Serial.print(", ");
      Serial.print(az * accScale, 4); Serial.print("] g[");
      Serial.print(gx * gyroScale, 4); Serial.print(", ");
      Serial.print(gy * gyroScale, 4); Serial.print(", ");
      Serial.print(gz * gyroScale, 4); Serial.println("]");

      Serial.println("-------------------------");
      delay(100);
  }
