#include <Arduino.h>
#include <Servo.h>
#include <unity.h>

#include "../test_config.h"

Servo servo1;
Servo servo2;

void test_servo_behavior_classification() {
  servo1.attach(SERVO_PORT1_PIN);
  servo2.attach(SERVO_PORT2_PIN);
  TEST_ASSERT_TRUE_MESSAGE(servo1.attached(), "Servo1 attach failed.");
  TEST_ASSERT_TRUE_MESSAGE(servo2.attached(), "Servo2 attach failed.");

  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);
  delay(1000);

  Serial.println("=== CONTINUOUS SERVO CALIBRATION TEST ===");
  Serial.println("Use this to find neutral stop pulse and practical speed commands.");
  Serial.println("Observe motion for each command and note where rotation stops.");
  Serial.println();

  Serial.println("[Phase 1] S1 neutral sweep (wide): 1400 -> 1600, step 10");
  servo2.writeMicroseconds(1500);
  for (int pulse = 1400; pulse <= 1600; pulse += 10) {
    servo1.writeMicroseconds(pulse);
    Serial.print("S1 pulse: ");
    Serial.println(pulse);
    delay(1800);
  }
  servo1.writeMicroseconds(1500);
  delay(1200);

  Serial.println("[Phase 2] S2 neutral sweep (wide): 1400 -> 1600, step 10");
  servo1.writeMicroseconds(1500);
  for (int pulse = 1400; pulse <= 1600; pulse += 10) {
    servo2.writeMicroseconds(pulse);
    Serial.print("S2 pulse: ");
    Serial.println(pulse);
    delay(1800);
  }
  servo2.writeMicroseconds(1500);
  delay(1200);

  Serial.println("[Phase 3] S1 speed table around neutral");
  Serial.println("Commands: 1350 1425 1475 1500 1525 1575 1650");
  servo2.writeMicroseconds(1500);
  const int speedTable[] = {1350, 1425, 1475, 1500, 1525, 1575, 1650};
  for (unsigned int i = 0; i < sizeof(speedTable) / sizeof(speedTable[0]); i++) {
    servo1.writeMicroseconds(speedTable[i]);
    Serial.print("S1 speed cmd pulse: ");
    Serial.println(speedTable[i]);
    delay(2200);
  }
  servo1.writeMicroseconds(1500);
  delay(1200);

  Serial.println("[Phase 4] S2 speed table around neutral");
  servo1.writeMicroseconds(1500);
  for (unsigned int i = 0; i < sizeof(speedTable) / sizeof(speedTable[0]); i++) {
    servo2.writeMicroseconds(speedTable[i]);
    Serial.print("S2 speed cmd pulse: ");
    Serial.println(speedTable[i]);
    delay(2200);
  }
  servo2.writeMicroseconds(1500);
  delay(1200);

  Serial.println("[Phase 5] Angle API equivalence check");
  Serial.println("Expected: 0~low pulse, 90~stop, 180~high pulse");
  servo2.writeMicroseconds(1500);
  servo1.write(0);
  Serial.println("S1 angle: 0");
  delay(2000);
  servo1.write(90);
  Serial.println("S1 angle: 90");
  delay(2000);
  servo1.write(180);
  Serial.println("S1 angle: 180");
  delay(2000);
  servo1.write(90);
  delay(1000);

  servo1.writeMicroseconds(1500);
  servo2.write(0);
  Serial.println("S2 angle: 0");
  delay(2000);
  servo2.write(90);
  Serial.println("S2 angle: 90");
  delay(2000);
  servo2.write(180);
  Serial.println("S2 angle: 180");
  delay(2000);
  servo2.write(90);
  delay(1000);

  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);
  Serial.println("=== DONE ===");
  Serial.println("Record:");
  Serial.println("1) S1 neutral stop pulse/range");
  Serial.println("2) S2 neutral stop pulse/range");
  Serial.println("3) Low/medium/high useful pulses per direction");
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }

  UNITY_BEGIN();
  RUN_TEST(test_servo_behavior_classification);
  UNITY_END();
}

void loop() {
}
