#include <Wire.h>
#include <MPU6050.h>
#include <TinyGPS++.h>
#include <MKRWAN.h>

// Objetos globales
MPU6050 mpu;
TinyGPSPlus gps;
LoRaModem modem;

// Pines del GPS (Serial1)
#define RX_PIN 13
#define TX_PIN 14
#define gpsSerial Serial1

// Estado detector
int estado = 0;
unsigned long tiempoEstado = 0;


void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("Error de conexión con el MPU6050");
    while (1);
  }

  if (!modem.begin(EU868)) {
    Serial.println("Error al iniciar el módulo LoRa");
    while (1);
  }

  if (!modem.joinOTAA(appEui, appKey)) {
    Serial.println("Error al unirse a TTN");
    while (1);
  }

  modem.sleep(); // Poner en bajo consumo tras la unión inicial

  Serial.println("Sistema de detección de caídas iniciado");
}

void loop() {
  // Leer acelerómetro
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  float accelX = ax / 16384.0;
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;
  float totalAccel = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ);

  switch (estado) {
    case 0:
      if (abs(accelX) < 0.6) {
        estado = 1;
        tiempoEstado = millis();
      }
      break;
    case 1:
      if (totalAccel > 1.8) {
        estado = 2;
        tiempoEstado = millis();
      } else if (millis() - tiempoEstado > 1500) {
        estado = 0;
      }
      break;
    case 2:
      if ((abs(accelX) < 0.4 || abs(accelX) > 1.3) && millis() - tiempoEstado > 500) {
        estado = 3;
        tiempoEstado = millis();
      } else if (millis() - tiempoEstado > 2000) {
        estado = 0;
      }
      break;
    case 3:
      Serial.println("⚠️ ¡CAÍDA DETECTADA!");

      // Activar GPS solo en caso de caída
      gpsSerial.begin(9600);
      unsigned long start = millis();
      while (millis() - start < 3000) { // Esperar hasta 3 segundos para capturar ubicación
        while (gpsSerial.available()) {
          gps.encode(gpsSerial.read());
        }
      }
      gpsSerial.end(); // Apagar GPS tras usarlo

      float lat = gps.location.isValid() ? gps.location.lat() : 0.0;
      float lon = gps.location.isValid() ? gps.location.lng() : 0.0;

      String mensaje = "CAIDA DETECTADA en (" + String(lat, 6) + ", " + String(lon, 6) + ")";
      Serial.println("Enviando: " + mensaje);

      modem.beginPacket();
      modem.print(mensaje);
      int err = modem.endPacket(true);


      if (err > 0) {
        Serial.println("Mensaje enviado con éxito");
      } else {
        Serial.println("Error al enviar mensaje");
      }

      modem.sleep(); // Poner LoRa en modo bajo consumo otra vez

      estado = 0;
      break;
  }

  delay(200);
}
