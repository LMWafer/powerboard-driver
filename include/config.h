
// ---------- MACROS ----------

#define BRAKE 0x01
#define NO_BRAKE 0x00

#define FORWARD 0x00
#define BACKWARD 0x01

#define FULL_THROTTLE 0xFF
#define HIGH_THROTTLE 0xC0
#define HALF_THROTTLE 0x80
#define LOW_THROTTLE 0x64
#define NO_THROTTLE 0x00

// ---------- I2C ----------

#define MY_ADDRESS 112

// ---------- Microcontroller pinout ----------

//-[] L298N pins (H-bridge)
//-> "ENA" | enable first H-bridge of L298N chip, that is first motor driver
#define BRIDGE_ENA_PIN 7
//-> "ENB" | enable second H-bridge of L298N chip, that is second motor driver
#define BRIDGE_ENB_PIN 8
//-> "IN1"| first input of first H-bridge, its signal gets amplified and outputed on "OUT1" board pin
#define BRIDGE_IN1_PIN 3
//-> "IN2" | second input of first H-bridge, its signal gets amplified and outputed on "OUT2" board pin
#define BRIDGE_IN2_PIN 5
//-> "IN3" | first input of second H-bridge, its signal gets amplified and outputed on "OUT3" board pin
#define BRIDGE_IN3_PIN 6
//-> "IN4" | second input of second H-bridge, its signal gets amplified and outputed on "OUT4" board pin
#define BRIDGE_IN4_PIN 9

//-[] Pololu D24V150F12 and associated KY-019 pins (buck converter and its relays)
//-> "EN" on buck | regulator enable input, drive low (< 1V) to disable
#define BUCK_REGULATOR_EN_PIN 10
//-> "S" on input relay | enable relay upstream buck's "VIN"
#define BUCK_INPUT_EN_PIN 11
//-> "S" on output relay | enable relay downstream buck's "VOUT"
#define BUCK_OUTPUT_EN_PIN 12
