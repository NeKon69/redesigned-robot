# Arduino Mega2560 + RC522 bring-up

## Wiring

Use this exact RC522 mapping:

| RC522 pin | Mega2560 pin |
|---|---|
| SDA (SS) | 53 |
| SCK | 52 |
| MOSI | 51 |
| MISO | 50 |
| IRQ | Not connected |
| GND | GND |
| RST | 49 |
| 3.3V | 3.3V |

## Test flow

1. Run only the new RC522 stage test:
   - `pio test -e megaatmega2560 --filter test_rc522_01_spi_smoke -v`
2. If it passes, run all tests:
   - `pio test -e megaatmega2560 -v`
3. Move to next stage:
   - `test_rc522_02_reader_health`
   - `test_rc522_03_uid_read`
   - `test_rc522_04_stability`

## Useful serial monitor command

- `pio device monitor -b 115200`

## 4x4 Keypad assumptions

Current test assumes the keypad's 8 wires are connected in order to Mega `24..31`:

- `R1->29`, `R2->28`, `R3->31`, `R4->30`
- `C1->25`, `C2->24`, `C3->27`, `C4->26`

Keypad test command:

- `pio test -e megaatmega2560 --filter test_keypad_01_matrix_scan -v`
- `pio test -e megaatmega2560 --filter test_keypad_02_key_echo -v`
- `pio test -e megaatmega2560 --filter test_keypad_03_guided_mapping -v`
- `pio test -e megaatmega2560 --filter test_keypad_04_repeat_stability -v`
- `pio test -e megaatmega2560 --filter test_keypad_05_full_coverage -v`
- `pio test -e megaatmega2560 --filter test_keypad_06_per_key_window -v`

Recommended keypad bring-up order:

1. `test_keypad_01_matrix_scan` (electrical/raw row-col detection only)
2. `test_keypad_02_key_echo` (prints mapped key for each press)
3. `test_keypad_03_guided_mapping` (strict expected-vs-actual prompts)
4. `test_keypad_04_repeat_stability` (repeat-read robustness)
5. `test_keypad_05_full_coverage` (45s, raw row/col logs, missing-key report)
6. `test_keypad_06_per_key_window` (2s per expected key, explicit missing list)

## SG90 servo tests (Port1/Port2)

Current pin mapping:

- `SERVO_PORT1_PIN -> 2`
- `SERVO_PORT2_PIN -> 3`
- `SERVO_PORT1_STOP_US -> 1520`
- `SERVO_PORT2_STOP_US -> 1520`
- `SERVO_MOVE_LOW_US -> 1425`
- `SERVO_MOVE_HIGH_US -> 1650`

Run order (continuous-servo calibrated flow):

1. `pio test -e megaatmega2560 --filter test_servo_00_behavior_classification -v`
2. `pio test -e megaatmega2560 --filter test_servo_01_ping_attach -v`
3. `pio test -e megaatmega2560 --filter test_servo_02_port1_basic_angles -v`
4. `pio test -e megaatmega2560 --filter test_servo_03_port2_basic_angles -v`
5. `pio test -e megaatmega2560 --filter test_servo_04_dual_sync_and_opposite -v`
6. `pio test -e megaatmega2560 --filter test_servo_05_port1_precision_sweep -v`
7. `pio test -e megaatmega2560 --filter test_servo_06_port2_precision_sweep -v`
8. `pio test -e megaatmega2560 --filter test_servo_07_microsecond_precision -v`
9. `pio test -e megaatmega2560 --filter test_servo_08_ramp_profiles -v`
10. `pio test -e megaatmega2560 --filter test_servo_09_stability_cycles -v`
11. `pio test -e megaatmega2560 --filter test_servo_10_rotation_calibration -v`

Calibration notes:

- `test_servo_10_rotation_calibration` uses wrapper functions for `CW/CCW x 90/180/360`.
- Tune these constants in `test/test_config.h`:
  - `SERVO1_CW_MS_PER_90`, `SERVO1_ACW_MS_PER_90`
  - `SERVO2_CW_MS_PER_90`, `SERVO2_ACW_MS_PER_90`
- If overshoot: decrease value.
- If undershoot: increase value.

After each new pass, run all non-keypad tests:

- `pio test -e megaatmega2560 -v`

## Switch tests (identification first)

Current pins:

- `SWITCH1_PIN -> 4`
- `SWITCH2_PIN -> 5`

First switch test:

- `pio test -e megaatmega2560 --filter test_switch_00_identify_wiring -v`

Switch run order:

1. `pio test -e megaatmega2560 --filter test_switch_00_identify_wiring -v`
2. `pio test -e megaatmega2560 --filter test_switch_01_raw_state_monitor -v`
3. `pio test -e megaatmega2560 --filter test_switch_02_edge_count -v`
4. `pio test -e megaatmega2560 --filter test_switch_03_debounce_validation -v`
5. `pio test -e megaatmega2560 --filter test_switch_04_dual_combo_states -v`
6. `pio test -e megaatmega2560 --filter test_switch_05_hold_duration -v`

## LCD 2004A (I2C backpack) first check

Wiring:

- `GND -> GND`
- `VCC -> 5V`
- `SDA -> SDA`
- `SCL -> SCL`

First test only:

- `pio test -e megaatmega2560 --filter test_lcd_00_i2c_scanner -v`
- `pio test -e megaatmega2560 --filter test_lcd_00b_bus_quick_probe -v`

LCD run order (after wiring/power confirmed):

1. `pio test -e megaatmega2560 --filter test_lcd_00_i2c_scanner -v`
2. `pio test -e megaatmega2560 --filter test_lcd_00b_bus_quick_probe -v`
3. `pio test -e megaatmega2560 --filter test_lcd_01_detect_and_init -v`
4. `pio test -e megaatmega2560 --filter test_lcd_02_line_rendering -v`
5. `pio test -e megaatmega2560 --filter test_lcd_03_cursor_clear_home -v`
6. `pio test -e megaatmega2560 --filter test_lcd_04_refresh_stability -v`
7. `pio test -e megaatmega2560 --filter test_lcd_05_backlight_control -v`

## Capture 3 RFID cards into JSON

1. Upload capture firmware:
   - `pio run -e megaatmega2560 -t upload`
2. Install dependency once:
   - `pip install pyserial`
3. Capture cards (deduplicated, saved in root `cards.json`):
   - `python3 capture_cards.py --port /dev/ttyUSB0 --count 3`
