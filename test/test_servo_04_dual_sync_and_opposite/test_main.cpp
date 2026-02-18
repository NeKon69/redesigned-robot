#include <Arduino.h>
#include <Servo.h>
#include <unity.h>

#include "../test_config.h"

Servo servo1;
Servo servo2;

void test_dual_sync_and_opposite_motion() {
  servo1.attach(SERVO_PORT1_PIN);
  servo2.attach(SERVO_PORT2_PIN);
  TEST_ASSERT_TRUE(servo1.attached());
  TEST_ASSERT_TRUE(servo2.attached());

  Serial.println("Phase A sync low: both should rotate same direction.");
  servo1.writeMicroseconds(SERVO_MOVE_LOW_US);
  servo2.writeMicroseconds(SERVO_MOVE_LOW_US);
  delay(2500);

  Serial.println("Stop both.");
  servo1.writeMicroseconds(SERVO_PORT1_STOP_US);
  servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
  delay(1800);

  Serial.println("Phase B sync high: both should rotate same other direction.");
  servo1.writeMicroseconds(SERVO_MOVE_HIGH_US);
  servo2.writeMicroseconds(SERVO_MOVE_HIGH_US);
  delay(2500);

  Serial.println("Stop both.");
  servo1.writeMicroseconds(SERVO_PORT1_STOP_US);
  servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
  delay(1800);

  Serial.println("Phase C opposite: S1 low, S2 high.");
  servo1.writeMicroseconds(SERVO_MOVE_LOW_US);
  servo2.writeMicroseconds(SERVO_MOVE_HIGH_US);
  delay(2500);

  Serial.println("Phase D opposite: S1 high, S2 low.");
  servo1.writeMicroseconds(SERVO_MOVE_HIGH_US);
  servo2.writeMicroseconds(SERVO_MOVE_LOW_US);
  delay(2500);

  Serial.println("Final stop.");
  servo1.writeMicroseconds(SERVO_PORT1_STOP_US);
  servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
  delay(1800);
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }
  UNITY_BEGIN();
  RUN_TEST(test_dual_sync_and_opposite_motion);
  UNITY_END();
}

void loop() {
}
