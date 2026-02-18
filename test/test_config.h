#pragma once

static constexpr uint8_t RC522_SS_PIN = 53;
static constexpr uint8_t RC522_RST_PIN = 49;
static constexpr unsigned long SERIAL_WAIT_MS = 2000;

static constexpr uint8_t KEYPAD_ROWS = 4;
static constexpr uint8_t KEYPAD_COLS = 4;
static constexpr uint8_t KEYPAD_ROW_PINS[KEYPAD_ROWS] = {24, 25, 26, 27};
static constexpr uint8_t KEYPAD_COL_PINS[KEYPAD_COLS] = {28, 29, 30, 31};

static constexpr uint8_t SERVO_PORT1_PIN = 2;
static constexpr uint8_t SERVO_PORT2_PIN = 3;
static constexpr int SERVO_PORT1_STOP_US = 1400;
static constexpr int SERVO_PORT2_STOP_US = 1400;
static constexpr int SERVO_MOVE_LOW_US = 1250;
static constexpr int SERVO_MOVE_HIGH_US = 1650;

// Direction semantics (from your observation):
// - Dir A (anti-clockwise) -> SERVO_MOVE_LOW_US
// - Dir B (clockwise)      -> SERVO_MOVE_HIGH_US
static constexpr int SERVO_ACW_US = SERVO_MOVE_LOW_US;
static constexpr int SERVO_CW_US = SERVO_MOVE_HIGH_US;

// Initial timing calibration (edit after running calibration test).
// These are milliseconds of drive time for approximately 90 degrees.
static constexpr uint16_t SERVO1_CW_MS_PER_90 = 218;
static constexpr uint16_t SERVO1_ACW_MS_PER_90 = 218;
static constexpr uint16_t SERVO2_CW_MS_PER_90 = 255;
static constexpr uint16_t SERVO2_ACW_MS_PER_90 = 250;

// Fine-tune 90-degree only (does NOT affect 180/360).
static constexpr uint16_t SERVO1_CW_MS_FOR_90 = 218;
static constexpr uint16_t SERVO1_ACW_MS_FOR_90 = 218;
static constexpr uint16_t SERVO2_CW_MS_FOR_90 = 255;
static constexpr uint16_t SERVO2_ACW_MS_FOR_90 = 250;

static constexpr uint8_t SWITCH1_PIN = 4;
static constexpr uint8_t SWITCH2_PIN = 5;

static constexpr uint8_t LCD_COLS = 20;
static constexpr uint8_t LCD_ROWS = 4;
