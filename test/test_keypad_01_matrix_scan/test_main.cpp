#include <Arduino.h>
#include <unity.h>

#include "../test_config.h"

static void releaseRowsToInputPullup() {
  for (byte row = 0; row < KEYPAD_ROWS; row++) {
    pinMode(KEYPAD_ROW_PINS[row], INPUT_PULLUP);
  }
}

static bool detectRawPress(byte &rowIndex, byte &colIndex) {
  for (byte row = 0; row < KEYPAD_ROWS; row++) {
    releaseRowsToInputPullup();
    pinMode(KEYPAD_ROW_PINS[row], OUTPUT);
    digitalWrite(KEYPAD_ROW_PINS[row], LOW);

    for (byte col = 0; col < KEYPAD_COLS; col++) {
      pinMode(KEYPAD_COL_PINS[col], INPUT_PULLUP);
      if (digitalRead(KEYPAD_COL_PINS[col]) == LOW) {
        rowIndex = row;
        colIndex = col;
        releaseRowsToInputPullup();
        return true;
      }
    }
  }

  releaseRowsToInputPullup();
  return false;
}

void test_raw_matrix_scan_detects_key_events() {
  const int requiredEvents = 4;
  const unsigned long timeoutMs = 30000;
  int events = 0;
  unsigned long start = millis();
  bool wasPressed = false;

  Serial.println("Low-level matrix scan test");
  Serial.println("Press any 4 keys (30s window).");
  Serial.println("This ignores key labels and checks matrix electrical detection.");

  while (millis() - start < timeoutMs && events < requiredEvents) {
    byte row = 0;
    byte col = 0;
    bool isPressed = detectRawPress(row, col);
    if (!isPressed) {
      wasPressed = false;
      delay(10);
      continue;
    }
    if (wasPressed) {
      delay(10);
      continue;
    }

    Serial.print("Raw press detected at row=");
    Serial.print(row);
    Serial.print(" (pin ");
    Serial.print(KEYPAD_ROW_PINS[row]);
    Serial.print("), col=");
    Serial.print(col);
    Serial.print(" (pin ");
    Serial.print(KEYPAD_COL_PINS[col]);
    Serial.println(")");

    events++;
    wasPressed = true;
    delay(250);
  }

  TEST_ASSERT_EQUAL_MESSAGE(requiredEvents, events, "Not enough raw key events detected.");
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }

  releaseRowsToInputPullup();
  for (byte col = 0; col < KEYPAD_COLS; col++) {
    pinMode(KEYPAD_COL_PINS[col], INPUT_PULLUP);
  }

  UNITY_BEGIN();
  RUN_TEST(test_raw_matrix_scan_detects_key_events);
  UNITY_END();
}

void loop() {
}
