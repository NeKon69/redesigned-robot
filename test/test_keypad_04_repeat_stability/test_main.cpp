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

void test_repeated_reads_on_single_key_are_stable() {
  const char targetKey = '5';
  const int targetReads = 8;
  const unsigned long timeoutMs = 45000;
  int reads = 0;
  unsigned long start = millis();

  Serial.println("Repeat stability test");
  Serial.print("Press key ");
  Serial.print(targetKey);
  Serial.println(" repeatedly.");

  while (millis() - start < timeoutMs && reads < targetReads) {
    char key = keypad.getKey();
    if (!key) {
      delay(10);
      continue;
    }

    Serial.print("Pressed: ");
    Serial.println(key);
    if (key != targetKey) {
      continue;
    }

    reads++;
    Serial.print("Valid target reads: ");
    Serial.println(reads);
  }

  TEST_ASSERT_EQUAL_MESSAGE(targetReads, reads, "Did not detect enough repeated target key reads.");
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }

  UNITY_BEGIN();
  RUN_TEST(test_repeated_reads_on_single_key_are_stable);
  UNITY_END();
}

void loop() {
}

