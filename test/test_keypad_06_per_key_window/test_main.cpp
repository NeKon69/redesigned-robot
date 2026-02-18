#include <Arduino.h>
#include <unity.h>
#include <Keypad.h>

#include "../test_config.h"

static char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

Keypad keypad = Keypad(makeKeymap(keys), (byte *)KEYPAD_ROW_PINS, (byte *)KEYPAD_COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);

static void runWindowForExpectedKey(char expected, bool &matched) {
  const unsigned long windowMs = 2000;
  const unsigned long start = millis();

  Serial.println("--------------------");
  Serial.print("Press key ");
  Serial.print(expected);
  Serial.println(" now (2s window)");

  while (millis() - start < windowMs) {
    char key = keypad.getKey();
    if (!key) {
      delay(5);
      continue;
    }

    Serial.print("Detected: ");
    Serial.println(key);

    if (key == expected) {
      matched = true;
      Serial.println("Result: MATCH");
      return;
    }

    Serial.print("Result: MISMATCH (expected ");
    Serial.print(expected);
    Serial.println(")");
  }

  Serial.println("Result: TIMEOUT");
}

void test_per_key_2s_windows_and_missing_report() {
  const char expectedOrder[] = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};
  bool matched[sizeof(expectedOrder)] = {false};
  int matchedCount = 0;

  Serial.println("Per-key window test");
  Serial.println("You get 2s for each expected key.");

  for (unsigned int i = 0; i < sizeof(expectedOrder); i++) {
    runWindowForExpectedKey(expectedOrder[i], matched[i]);
    if (matched[i]) {
      matchedCount++;
    }
    delay(250);
  }

  Serial.println("==== Summary ====");
  Serial.print("Matched keys: ");
  Serial.print(matchedCount);
  Serial.print("/");
  Serial.println((int)sizeof(expectedOrder));

  if (matchedCount < (int)sizeof(expectedOrder)) {
    Serial.println("Missing expected keys:");
    for (unsigned int i = 0; i < sizeof(expectedOrder); i++) {
      if (!matched[i]) {
        Serial.print(expectedOrder[i]);
        Serial.print(' ');
      }
    }
    Serial.println();
  }

  TEST_ASSERT_EQUAL_MESSAGE((int)sizeof(expectedOrder), matchedCount, "Some expected keys were not detected in their 2s windows.");
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }

  UNITY_BEGIN();
  RUN_TEST(test_per_key_2s_windows_and_missing_report);
  UNITY_END();
}

void loop() {
}

