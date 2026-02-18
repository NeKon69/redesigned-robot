#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#ifndef PIO_UNIT_TESTING
static constexpr uint8_t RC522_SS_PIN = 53;
static constexpr uint8_t RC522_RST_PIN = 49;

MFRC522 mfrc522(RC522_SS_PIN, RC522_RST_PIN);

static void printUid(const MFRC522::Uid &uid) {
  Serial.print("CARD_UID:");
  for (byte i = 0; i < uid.size; i++) {
    if (uid.uidByte[i] < 0x10) {
      Serial.print('0');
    }
    Serial.print(uid.uidByte[i], HEX);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2000) {
  }
  SPI.begin();
  mfrc522.PCD_Init();
  delay(100);
  Serial.println("RC522 capture mode ready. Tap cards...");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    delay(40);
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    delay(40);
    return;
  }

  printUid(mfrc522.uid);
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  delay(600);
}
#endif
