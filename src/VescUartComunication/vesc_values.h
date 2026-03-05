#pragma once
/* File contains values that are updated by the VESC UART library. */

// Variables to be grabbed from VESC UART, not all are completely accurate nor updated. ---
float avgMotorCurrent = 0;
float avgInputCurrent = 0;
float dutyCycleNow = 0;
float rpm = 0;
float inpVoltage = 0;
float ampHours = 0; // total drawn over time
float ampHoursCharged = 0; // charge battery has recieved
float wattHours = 0;
float wattHoursCharged = 0;
long tachometer = 0;
long tachometerAbs = 0;
float tempMosfet = 0;
float tempMotor = 0;
float pidPos = 0;
int batteryval = 0;
int speed = 0;
uint8_t id;

// keeping track of updated values with last values, these are updated in the main loop below.
float last_avgMotorCurrent = -1;
float last_avgInputCurrent = -1;
float last_dutyCycleNow = -1;
float last_rpm = -1;
float last_inpVoltage = -1;
float last_ampHours = -1;
float last_ampHoursCharged = -1;
float last_wattHours = -1;
float last_wattHoursCharged = -1;
long last_tachometer = -1;
long last_tachometerAbs = -1;
float last_tempMosfet = -1;
float last_tempMotor = -1;
float last_pidPos = -1;
int last_batteryval = -1;
int last_speed = -1;
int last_fill = -1;