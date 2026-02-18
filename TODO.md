# TODO

## Continuous Servo Calibration (Pending)

- Re-run calibration for 90-degree moves on both servos.
- Re-validate and recalibrate 180/360 behavior for both servos (currently inconsistent).
- Update these constants in `test/test_config.h` after recalibration:
  - `SERVO1_CW_MS_FOR_90`
  - `SERVO1_ACW_MS_FOR_90`
  - `SERVO2_CW_MS_FOR_90`
  - `SERVO2_ACW_MS_FOR_90`
- Re-tune these multiplier constants if 180/360 continue to drift:
  - `SERVO1_CW_MS_PER_90`
  - `SERVO1_ACW_MS_PER_90`
  - `SERVO2_CW_MS_PER_90`
  - `SERVO2_ACW_MS_PER_90`
- Verify with:
  - `pio test -e megaatmega2560 --filter test_servo_10_rotation_calibration -v`
