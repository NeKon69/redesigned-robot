#include <Arduino.h>
#include <Servo.h>
#include <unity.h>

#include "../test_config.h"

Servo servo2;

void test_port2_precision_sweep() {
  servo2.attach(SERVO_PORT2_PIN);
  TEST_ASSERT_TRUE(servo2.attached());

  const int pulses[] = {1475, 1450, 1425, SERVO_PORT2_STOP_US, 1575, 1600, 1650, SERVO_PORT2_STOP_US};
  Serial.println("Port2 speed ladder (calibrated pulse control).");
  for (unsigned int i = 0; i < sizeof(pulses) / sizeof(pulses[0]); i++) {
    servo2.writeMicroseconds(pulses[i]);
    Serial.print("Step ");
    Serial.print(i + 1);
    Serial.print(" pulse: ");
    Serial.println(pulses[i]);
    delay(2200);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }
  UNITY_BEGIN();
  RUN_TEST(test_port2_precision_sweep);
  UNITY_END();
}

void loop() {
}
