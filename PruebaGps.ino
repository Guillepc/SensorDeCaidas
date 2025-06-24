#include <TinyGPS++.h>
#include <Arduino.h>

// Creamos el objeto GPS
TinyGPSPlus gps;

// Configuración de Serial para GPS (Hardware Serial1 en MKR WAN 1310)
#define RX_PIN 13
#define TX_PIN 14

// Usamos Serial1 en MKR WAN 1310 para el GPS
#define gpsSerial Serial1

void setup() {
  Serial.begin(115200);   // Para monitorizar en el PC
  gpsSerial.begin(9600);  // Velocidad de comunicación con el GPS

  Serial.println("Iniciando GPS...");
}

void loop() {
  while (gpsSerial.available() > 0) { 
    gps.encode(gpsSerial.read());  // Procesamos los datos del GPS
  }

  if (gps.location.isUpdated()) {  // Si hay nueva información de localización
    Serial.print("Latitud: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(" | Longitud: ");
    Serial.println(gps.location.lng(), 6);
  }
}
