#include <Arduino.h>
#include <Servo.h>
#include <unity.h>

#include "../test_config.h"

Servo servo1;
Servo servo2;

void test_microsecond_precision_positions() {
  servo1.attach(SERVO_PORT1_PIN);
  servo2.attach(SERVO_PORT2_PIN);
  TEST_ASSERT_TRUE(servo1.attached());
  TEST_ASSERT_TRUE(servo2.attached());

  Serial.println("Timed burst test (pseudo-rotation control by time).");
  Serial.println("Each burst should produce repeatable rotation amount.");

  const unsigned long burstMs = 700;
  for (int i = 1; i <= 5; i++) {
    Serial.print("Burst ");
    Serial.println(i);
    servo1.writeMicroseconds(SERVO_MOVE_LOW_US);
    servo2.writeMicroseconds(SERVO_MOVE_LOW_US);
    delay(burstMs);
    servo1.writeMicroseconds(SERVO_PORT1_STOP_US);
    servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
    delay(1500);
  }

  for (int i = 1; i <= 5; i++) {
    Serial.print("Reverse burst ");
    Serial.println(i);
    servo1.writeMicroseconds(SERVO_MOVE_HIGH_US);
    servo2.writeMicroseconds(SERVO_MOVE_HIGH_US);
    delay(burstMs);
    servo1.writeMicroseconds(SERVO_PORT1_STOP_US);
    servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
    delay(1500);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }
  UNITY_BEGIN();
  RUN_TEST(test_microsecond_precision_positions);
  UNITY_END();
}

void loop() {
}
