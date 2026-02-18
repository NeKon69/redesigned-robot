#include <Arduino.h>
#include <unity.h>

#include "../../src/continuous_servo_wrapper.h"
#include "../test_config.h"

static ContinuousServoCalibration cal1 = {
    SERVO_PORT1_STOP_US,
    SERVO_CW_US,
    SERVO_ACW_US,
    SERVO1_CW_MS_PER_90,
    SERVO1_ACW_MS_PER_90,
    SERVO1_CW_MS_FOR_90,
    SERVO1_ACW_MS_FOR_90};

static ContinuousServoCalibration cal2 = {
    SERVO_PORT2_STOP_US,
    SERVO_CW_US,
    SERVO_ACW_US,
    SERVO2_CW_MS_PER_90,
    SERVO2_ACW_MS_PER_90,
    SERVO2_CW_MS_FOR_90,
    SERVO2_ACW_MS_FOR_90};

ContinuousServoWrapper servo1(SERVO_PORT1_PIN, cal1);
ContinuousServoWrapper servo2(SERVO_PORT2_PIN, cal2);

static void runRotationSet(const char *label, ContinuousServoWrapper &servo) {
  Serial.println("--------------------------------");
  Serial.print("Calibration set for ");
  Serial.println(label);
  Serial.println("Observe final angle after each command.");

  Serial.println("CW 90");
  servo.rotateClockwise90();
  delay(2000);
  Serial.println("CW 180");
  servo.rotateClockwise180();
  delay(2000);
  Serial.println("CW 360");
  servo.rotateClockwise360();
  delay(2500);

  Serial.println("ACW 90");
  servo.rotateAntiClockwise90();
  delay(2000);
  Serial.println("ACW 180");
  servo.rotateAntiClockwise180();
  delay(2000);
  Serial.println("ACW 360");
  servo.rotateAntiClockwise360();
  delay(2500);
}

void test_rotation_calibration_helper() {
  servo1.attach();
  servo2.attach();

  TEST_ASSERT_TRUE_MESSAGE(servo1.attached(), "Servo1 attach failed.");
  TEST_ASSERT_TRUE_MESSAGE(servo2.attached(), "Servo2 attach failed.");

  Serial.println("== Rotation calibration helper ==");
  Serial.println("If rotation overshoots: reduce *_MS_PER_90.");
  Serial.println("If rotation undershoots: increase *_MS_PER_90.");
  Serial.println("Tune CW and ACW separately per servo in test_config.h.");

  servo2.stop();
  runRotationSet("Servo1 (Port1)", servo1);
  servo1.stop();
  delay(1000);

  servo1.stop();
  runRotationSet("Servo2 (Port2)", servo2);
  servo2.stop();

  Serial.println("== End of calibration run ==");
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < SERIAL_WAIT_MS) {
  }

  UNITY_BEGIN();
  RUN_TEST(test_rotation_calibration_helper);
  UNITY_END();
}

void loop() {
}
