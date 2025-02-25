// Master relay with lora and esp wroom 32
#include <SPI.h>
#include <LoRa.h>

#define BUTTON_PIN 22  // Push button
#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 26

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);  // Digital button as input

  // Initialize LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {  // 433 MHz Frequency
    Serial.println("LoRa init failed!");
    while (1);
  }
  Serial.println("LoRa Initialized.");
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState == HIGH) {
    Serial.println("Button Pressed! Sending ON signal...");
    LoRa.beginPacket();
    LoRa.print("ON");
    LoRa.endPacket();
  } else {
    Serial.println("Button Released! Sending OFF signal...");
    LoRa.beginPacket();
    LoRa.print("OFF");
    LoRa.endPacket();
  }
  
  delay(500);  // Small delay to avoid rapid transmissions
}
