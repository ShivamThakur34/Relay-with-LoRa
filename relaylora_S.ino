// Slave with relay and push button with lora using esp wroom 32
#include <SPI.h>
#include <LoRa.h>

#define RELAY_PIN 23  // Relay pin
#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 26

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Ensure relay starts OFF

  // Initialize LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }
  Serial.println("LoRa Receiver Initialized.");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedText = "";
    while (LoRa.available()) {
      receivedText += (char)LoRa.read();
    }
    Serial.print("Received: ");
    Serial.println(receivedText);

    // Control relay based on received message
    if (receivedText == "ON") {
      digitalWrite(RELAY_PIN, HIGH);  // Turn Relay ON
      Serial.println("Relay Turned ON");
    } else if (receivedText == "OFF") {
      digitalWrite(RELAY_PIN, LOW);   // Turn Relay OFF
      Serial.println("Relay Turned OFF");
    }
  }
}
