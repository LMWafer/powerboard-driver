
// ---------- Command functions ----------
#define COMMAND 0x00

#define ARM 0x00
#define DISARM 0x01

#define SET_SPEED_ALL 0x02
#define SET_SPEED_M1 0x03
#define SET_SPEED_M2 0x04

#define STOP_ALL 0x05
#define STOP_M1 0x06
#define STOP_M2 0x07

#define BRAKE_ALL 0x08
#define BRAKE_M1 0x09
#define BRAKE_M2 0x0A

#define REVERSE_ALL 0x0B
#define REVERSE_M1 0x0C
#define REVERSE_M2 0x0D

#define ENABLE_MA 0x0E
#define DISABLE_MA 0x0F

#define ENABLE_MB 0x10
#define DISABLE_MB 0x11

#define SET_SIGNAL_IN1 0x12
#define SET_SIGNAL_IN2 0x13
#define SET_SIGNAL_IN3 0x14
#define SET_SIGNAL_IN4 0x15

#define ENABLE_REGULATOR 0x14
#define DISABLE_REGULATOR 0x15

#define ENABLE_INPUT 0x15
#define DISABLE_INPUT 0x16

#define ENABLE_OUTPUT 0x17
#define DISABLE_OUTPUT 0x18


// ---------- Retrieve functions ----------
#define RETRIEVE 0x01

#define SPEED_M1 0x00
#define SPEED_M2 0x01

#define M1_BRAKED 0x02
#define M2_BRAKED 0x03

#define MA_ENABLED 0x04
#define MB_ENABLED 0x05

#define IN1_SETPOINT 0x06
#define IN2_SETPOINT 0x07
#define IN3_SETPOINT 0x08
#define IN4_SETPOINT 0x09

#define REGULATOR_ENABLED 0x0A
#define INPUT_ENABLED 0x0B
#define OUTPUT_ENABLED 0x0C