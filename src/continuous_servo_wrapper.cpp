#include "continuous_servo_wrapper.h"

ContinuousServoWrapper::ContinuousServoWrapper(
    uint8_t signal_pin, const ContinuousServoCalibration &calibration)
    : signal_pin_(signal_pin), calibration_(calibration) {}

void ContinuousServoWrapper::attach() {
  servo_.attach(signal_pin_);
  stop();
}

void ContinuousServoWrapper::detach() { servo_.detach(); }

bool ContinuousServoWrapper::attached() const { return servo_.attached(); }

void ContinuousServoWrapper::stop() {
  servo_.writeMicroseconds(calibration_.stop_us);
}

void ContinuousServoWrapper::rotateClockwise90() {
  rotateTimed(calibration_.clockwise_us, calibration_.cw_ms_per_90);
}

void ContinuousServoWrapper::rotateClockwise180() {
  rotateTimed(calibration_.clockwise_us, calibration_.cw_ms_per_90 * 2);
}

void ContinuousServoWrapper::rotateClockwise360() {
  rotateTimed(calibration_.clockwise_us, calibration_.cw_ms_per_90 * 4);
}

void ContinuousServoWrapper::rotateAntiClockwise90() {
  rotateTimed(calibration_.anticlockwise_us, calibration_.acw_ms_per_90);
}

void ContinuousServoWrapper::rotateAntiClockwise180() {
  rotateTimed(calibration_.anticlockwise_us, calibration_.acw_ms_per_90 * 2);
}

void ContinuousServoWrapper::rotateAntiClockwise360() {
  rotateTimed(calibration_.anticlockwise_us, calibration_.acw_ms_per_90 * 4);
}

void ContinuousServoWrapper::rotateTimed(int pulse_us, uint16_t duration_ms) {
  servo_.writeMicroseconds(pulse_us);
  delay(duration_ms);
  stop();
}
