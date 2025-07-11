#include <MKRWAN.h>

LoRaModem modem;

// Datos de prueba
String simulatedLatitude = "40.4168";  // Por ejemplo, Madrid
String simulatedLongitude = "-3.7038"; 

String appEui;
String appKey;
String devAddr;
String nwkSKey;
String appSKey;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Welcome to MKR WAN 1300/1310 fall detection simulation");

  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1);
  }

  Serial.print("Your module version is: ");
  Serial.println(modem.version());

  if (modem.version() != ARDUINO_FW_VERSION) {
    Serial.println("Please make sure that the latest modem firmware is installed.");
    Serial.println("To update the firmware upload the 'MKRWANFWUpdate_standalone.ino' sketch.");
  }

  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  int mode = 0;
  while (mode != 1 && mode != 2) {
    Serial.println("Are you connecting via OTAA (1) or ABP (2)?");
    while (!Serial.available());
    mode = Serial.readStringUntil('\n').toInt();
  }

  int connected;
  if (mode == 1) {
    Serial.println("Enter your APP EUI");
    while (!Serial.available());
    appEui = Serial.readStringUntil('\n');

    Serial.println("Enter your APP KEY");
    while (!Serial.available());
    appKey = Serial.readStringUntil('\n');

    appKey.trim();
    appEui.trim();

    connected = modem.joinOTAA(appEui, appKey);
  } else if (mode == 2) {
    Serial.println("Enter your Device Address");
    while (!Serial.available());
    devAddr = Serial.readStringUntil('\n');

    Serial.println("Enter your NWS KEY");
    while (!Serial.available());
    nwkSKey = Serial.readStringUntil('\n');

    Serial.println("Enter your APP SKEY");
    while (!Serial.available());
    appSKey = Serial.readStringUntil('\n');

    devAddr.trim();
    nwkSKey.trim();
    appSKey.trim();

    connected = modem.joinABP(devAddr, nwkSKey, appSKey);
  }

  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1);
  }

  Serial.println("Setup complete. Type 'c' to simulate fall detection and send alert.");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'c' || c == 'C') {
      sendFallAlert();
    }
  }
  modem.poll();
}

void sendFallAlert() {
  String message = "CAIDA DETECTADA en (40.4168, -3.7038)";
  
  Serial.println("Sending alert: ");
  Serial.println(message);

  modem.beginPacket();
  modem.print(message);  // Asegura que se imprime como texto

  int err = modem.endPacket(true);  // Confirmed uplink
  if (err > 0) {
    Serial.println("Alert message sent correctly!");
  } else {
    Serial.println("Error sending alert message :(");
  }
}

