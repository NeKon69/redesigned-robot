#include <Arduino.h>
#include <unity.h>
#include <Keypad.h>

#include "../test_config.h"

char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

Keypad keypad = Keypad(makeKeymap(keys), (byte *)KEYPAD_ROW_PINS, (byte *)KEYPAD_COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);

static void failExpectedKey(char expected) {
  char msg[80];
  snprintf(msg, sizeof(msg), "Timeout waiting for expected key '%c'.", expected);
  TEST_FAIL_MESSAGE(msg);
}

static void waitForExpectedKey(char expected, unsigned long timeoutMs) {
  const unsigned long start = millis();
  while (millis() - start < timeoutMs) {
    char key = keypad.getKey();
    if (!key) {
      delay(10);
      continue;
    }

    Serial.print("Pressed: ");
    Serial.println(key);
    if (key == expected) {
      Serial.println("Match: OK");
      return;
    }

    Serial.print("Mismatch. Expected: ");
    Serial.print(expected);
    Serial.print(", got: ");
    Serial.println(key);
  }
  failExpectedKey(expected);
}

void test_guided_selected_key_mapping() {
  const unsigned long perKeyTimeoutMs = 12000;
  const char sequence[] = {'1', '2', '3', 'A', '7', '8', '9', 'C', '*', '0', '#', 'D'};

  Serial.println("Guided mapping test");
  Serial.println("Expected layout:");
  Serial.println("1 2 3 A");
  Serial.println("4 5 6 B");
  Serial.println("7 8 9 C");
  Serial.println("* 0 # D");
  Serial.println("Press prompted keys in order.");

  for (unsigned int i = 0; i < sizeof(sequence); i++) {
    Serial.println("--------------------");
    Serial.print("Now press key: ");
    Serial.println(sequence[i]);
    waitForExpectedKey(sequence[i], perKeyTimeoutMs);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }

  UNITY_BEGIN();
  RUN_TEST(test_guided_selected_key_mapping);
  UNITY_END();
}

void loop() {
}

