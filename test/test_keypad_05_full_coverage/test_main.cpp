#include <Arduino.h>
#include <unity.h>

#include "../test_config.h"

static char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

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

void test_full_keypad_coverage_with_missing_report() {
  const unsigned long windowMs = 45000;
  unsigned long start = millis();
  bool wasPressed = false;
  int totalEvents = 0;
  int uniqueKeys = 0;
  int matrixHits[KEYPAD_ROWS][KEYPAD_COLS] = {0};
  bool seen[KEYPAD_ROWS][KEYPAD_COLS] = {{false}};

  Serial.println("Full keypad coverage test (new)");
  Serial.println("Press all 16 keys in any order within 45s.");
  Serial.println("Each event prints raw row/col and interpreted key.");

  while (millis() - start < windowMs) {
    byte row = 0;
    byte col = 0;
    bool isPressed = detectRawPress(row, col);

    if (!isPressed) {
      wasPressed = false;
      delay(8);
      continue;
    }
    if (wasPressed) {
      delay(8);
      continue;
    }

    wasPressed = true;
    totalEvents++;
    matrixHits[row][col]++;
    if (!seen[row][col]) {
      seen[row][col] = true;
      uniqueKeys++;
    }

    Serial.print("Event ");
    Serial.print(totalEvents);
    Serial.print(": row=");
    Serial.print(row);
    Serial.print(" (pin ");
    Serial.print(KEYPAD_ROW_PINS[row]);
    Serial.print("), col=");
    Serial.print(col);
    Serial.print(" (pin ");
    Serial.print(KEYPAD_COL_PINS[col]);
    Serial.print(") => key=");
    Serial.println(keys[row][col]);

    if (uniqueKeys == (KEYPAD_ROWS * KEYPAD_COLS)) {
      break;
    }
  }

  Serial.println("---- Coverage summary ----");
  Serial.print("Total press events: ");
  Serial.println(totalEvents);
  Serial.print("Unique keys seen: ");
  Serial.println(uniqueKeys);

  Serial.println("Matrix hit counts:");
  for (byte row = 0; row < KEYPAD_ROWS; row++) {
    for (byte col = 0; col < KEYPAD_COLS; col++) {
      Serial.print(keys[row][col]);
      Serial.print(":");
      Serial.print(matrixHits[row][col]);
      Serial.print("  ");
    }
    Serial.println();
  }

  if (uniqueKeys < (KEYPAD_ROWS * KEYPAD_COLS)) {
    Serial.println("Missing keys:");
    for (byte row = 0; row < KEYPAD_ROWS; row++) {
      for (byte col = 0; col < KEYPAD_COLS; col++) {
        if (!seen[row][col]) {
          Serial.print(keys[row][col]);
          Serial.print("  ");
        }
      }
    }
    Serial.println();
  }

  TEST_ASSERT_EQUAL_MESSAGE(KEYPAD_ROWS * KEYPAD_COLS, uniqueKeys, "Not all 16 keys were detected.");
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
  RUN_TEST(test_full_keypad_coverage_with_missing_report);
  UNITY_END();
}

void loop() {
}

