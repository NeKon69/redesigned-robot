#pragma once

#include <Arduino.h>

class MFRC522;

class RfidReader {
 public:
  RfidReader();

  void begin();
  bool pollUid(String &uidOut);

 private:
  MFRC522 *reader_ = nullptr;
  String last_uid_;
  unsigned long last_uid_ms_ = 0;

  static String uidToHex_(const MFRC522 &reader);
};
