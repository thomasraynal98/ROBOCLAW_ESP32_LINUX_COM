#include <vector>
#include <Arduino.h>

#define ONBOARD_LED  2
#define M_TIC_QUAD 20000
#define TIC_PER_MOTOR_REVOLUTION 4480

void read_serial_input(HardwareSerial* Serial, std::vector<String>& msg_vector);
void send_serial_input(HardwareSerial* Serial, String msg_vector);
void print_float_vector(HardwareSerial* Serial, std::vector<String>& msg_vector, int option);
uint32_t convert_cmToPulse(float cm_s);