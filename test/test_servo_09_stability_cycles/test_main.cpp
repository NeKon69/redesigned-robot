#include <Arduino.h>
#include <Servo.h>
#include <unity.h>

#include "../test_config.h"

Servo servo1;
Servo servo2;

void test_stability_cycles() {
  servo1.attach(SERVO_PORT1_PIN);
  servo2.attach(SERVO_PORT2_PIN);
  TEST_ASSERT_TRUE(servo1.attached());
  TEST_ASSERT_TRUE(servo2.attached());

  const int cycles = 12;
  Serial.println("Stability cycles (continuous mode).");
  Serial.println("Expect consistent start/stop and no drift at stop command.");

  for (int i = 1; i <= cycles; i++) {
    servo1.writeMicroseconds(SERVO_MOVE_LOW_US);
    servo2.writeMicroseconds(SERVO_MOVE_LOW_US);
    delay(1200);

    servo1.writeMicroseconds(SERVO_PORT1_STOP_US);
    servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
    delay(1000);

    servo1.writeMicroseconds(SERVO_MOVE_HIGH_US);
    servo2.writeMicroseconds(SERVO_MOVE_HIGH_US);
    delay(1200);

    servo1.writeMicroseconds(SERVO_PORT1_STOP_US);
    servo2.writeMicroseconds(SERVO_PORT2_STOP_US);
    delay(1000);

    Serial.print("Cycle ");
    Serial.print(i);
    Serial.print("/");
    Serial.println(cycles);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }
  UNITY_BEGIN();
  RUN_TEST(test_stability_cycles);
  UNITY_END();
}

void loop() {
}
