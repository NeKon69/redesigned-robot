#include <Arduino.h>
#include <Keypad.h>
#include <unity.h>

#include "../test_config.h"

char keys[KEYPAD_ROWS][KEYPAD_COLS] = {{'1', '2', '3', 'A'},
                                       {'4', '5', '6', 'B'},
                                       {'7', '8', '9', 'C'},
                                       {'*', '0', '#', 'D'}};

Keypad keypad = Keypad(makeKeymap(keys), (byte *)KEYPAD_ROW_PINS,
                       (byte *)KEYPAD_COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);

void test_echoes_every_detected_keypress() {
  const int requiredPresses = 8;
  const unsigned long timeoutMs = 30000;
  int presses = 0;
  unsigned long start = millis();

  Serial.println("Key echo test");
  Serial.println("Press any keys. Expected output: Pressed: <key>");

  while (millis() - start < timeoutMs && presses < requiredPresses) {
    char key = keypad.getKey();
    if (!key) {
      delay(10);
      continue;
    }
    presses++;
    Serial.print("Pressed: ");
    Serial.println(key);
  }

  TEST_ASSERT_EQUAL_MESSAGE(requiredPresses, presses,
                            "Did not capture enough keypresses.");
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }

  UNITY_BEGIN();
  RUN_TEST(test_echoes_every_detected_keypress);
  UNITY_END();
}

void loop() {}
