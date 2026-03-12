#include "rfid_reader.h"

#include <MFRC522.h>
#include <SPI.h>

#include "runtime_config.h"

RfidReader::RfidReader() { reader_ = new MFRC522(RC522_SS_PIN, RC522_RST_PIN); }

void RfidReader::begin() {
  SPI.begin();
  reader_->PCD_Init();
  delay(50);
}

bool RfidReader::pollUid(String &uidOut) {
  if (!reader_->PICC_IsNewCardPresent()) {
    return false;
  }
  if (!reader_->PICC_ReadCardSerial()) {
    return false;
  }

  const String uid = uidToHex_(*reader_);
  reader_->PICC_HaltA();
  reader_->PCD_StopCrypto1();

  if (uid == last_uid_ && millis() - last_uid_ms_ < RFID_REPEAT_SUPPRESS_MS) {
    return false;
  }

  last_uid_ = uid;
  last_uid_ms_ = millis();
  uidOut = uid;
  return true;
}

String RfidReader::uidToHex_(const MFRC522 &reader) {
  String out;
  for (byte i = 0; i < reader.uid.size; i++) {
    if (reader.uid.uidByte[i] < 0x10) {
      out += '0';
    }
    out += String(reader.uid.uidByte[i], HEX);
  }
  out.toUpperCase();
  return out;
}
