#include <Arduino.h>
#include <Servo.h>
#include <unity.h>

#include "../test_config.h"

Servo servo1;
Servo servo2;

void test_ramp_profiles() {
  servo1.attach(SERVO_PORT1_PIN);
  servo2.attach(SERVO_PORT2_PIN);
  TEST_ASSERT_TRUE(servo1.attached());
  TEST_ASSERT_TRUE(servo2.attached());

  Serial.println("Pulse ramp around neutral.");
  Serial.println("Expect speed to increase as pulse moves away from neutral.");

  const int segments[] = {1510, 1500, 1490, 1475, 1450, 1425, 1450, 1475, 1500,
                          1530, 1560, 1600, 1650, 1600, 1560, 1530, 1520};
  for (unsigned int i = 0; i < sizeof(segments) / sizeof(segments[0]); i++) {
    servo1.writeMicroseconds(segments[i]);
    servo2.writeMicroseconds(segments[i]);
    Serial.print("Segment ");
    Serial.print(i + 1);
    Serial.print(" pulse: ");
    Serial.println(segments[i]);
    delay(1600);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }
  UNITY_BEGIN();
  RUN_TEST(test_ramp_profiles);
  UNITY_END();
}

void loop() {
}
