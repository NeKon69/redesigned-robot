#pragma once

#include <Arduino.h>
#include <Servo.h>

struct ContinuousServoCalibration {
  int stop_us;
  int clockwise_us;
  int anticlockwise_us;
  uint16_t cw_ms_per_90;
  uint16_t acw_ms_per_90;
  uint16_t cw_ms_for_90;
  uint16_t acw_ms_for_90;
};

class ContinuousServoWrapper {
 public:
  ContinuousServoWrapper(uint8_t signal_pin, const ContinuousServoCalibration &calibration);

  void attach();
  void detach();
  bool attached() const;

  void stop();
  void rotateClockwise90();
  void rotateClockwise180();
  void rotateClockwise360();
  void rotateAntiClockwise90();
  void rotateAntiClockwise180();
  void rotateAntiClockwise360();

 private:
  void rotateTimed(int pulse_us, uint16_t duration_ms);

  uint8_t signal_pin_;
  ContinuousServoCalibration calibration_;
  Servo servo_;
};
