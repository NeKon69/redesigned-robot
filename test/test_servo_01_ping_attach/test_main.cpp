#include <Arduino.h>
#include <Servo.h>
#include <unity.h>

#include "../test_config.h"

Servo servo1;
Servo servo2;

void test_ping_and_attach() {
  servo1.attach(SERVO_PORT1_PIN);
  servo2.attach(SERVO_PORT2_PIN);

  TEST_ASSERT_TRUE_MESSAGE(servo1.attached(),
                           "Servo on port 1 did not attach.");
  TEST_ASSERT_TRUE_MESSAGE(servo2.attached(),
                           "Servo on port 2 did not attach.");

  Serial.println("Step 1: stop both servos.");
  Serial.println("Expect: no rotation.");
  servo1.writeMicroseconds(SERVO_PORT1_STOP_US);
  servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
  delay(2000);

  Serial.println("Step 2: short low-pulse burst.");
  Serial.println("Expect: both rotate same direction briefly.");
  servo1.writeMicroseconds(SERVO_MOVE_LOW_US);
  servo2.writeMicroseconds(SERVO_MOVE_LOW_US);
  delay(800);

  Serial.println("Step 3: stop both.");
  servo1.writeMicroseconds(SERVO_PORT1_STOP_US);
  servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
  delay(2000);

  Serial.println("Step 4: short high-pulse burst.");
  Serial.println("Expect: both rotate opposite direction briefly.");
  servo1.writeMicroseconds(SERVO_MOVE_HIGH_US);
  servo2.writeMicroseconds(SERVO_MOVE_HIGH_US);
  delay(800);

  Serial.println("Step 5: final stop.");
  servo1.writeMicroseconds(SERVO_PORT1_STOP_US);
  servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
  delay(1500);
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }
  UNITY_BEGIN();
  RUN_TEST(test_ping_and_attach);
  UNITY_END();
}

void loop() {}
