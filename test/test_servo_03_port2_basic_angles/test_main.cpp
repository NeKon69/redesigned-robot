#include <Arduino.h>
#include <Servo.h>
#include <unity.h>

#include "../test_config.h"

Servo servo2;

void test_port2_direction_and_stop() {
  servo2.attach(SERVO_PORT2_PIN);
  TEST_ASSERT_TRUE_MESSAGE(servo2.attached(), "Servo on port 2 did not attach.");

  Serial.println("Port2 continuous-servo direction check.");
  Serial.println("Step 1: stop.");
  servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
  delay(2500);

  Serial.println("Step 2: low pulse (dir A).");
  servo2.writeMicroseconds(SERVO_MOVE_LOW_US);
  delay(2500);

  Serial.println("Step 3: stop.");
  servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
  delay(2500);

  Serial.println("Step 4: high pulse (dir B).");
  servo2.writeMicroseconds(SERVO_MOVE_HIGH_US);
  delay(2500);

  Serial.println("Step 5: stop.");
  servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
  delay(2500);
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }
  UNITY_BEGIN();
  RUN_TEST(test_port2_direction_and_stop);
  UNITY_END();
}

void loop() {
}
