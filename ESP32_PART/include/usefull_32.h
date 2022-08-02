#include <vector>
#include <Arduino.h>

#define ONBOARD_LED  2

void read_serial_input(HardwareSerial* Serial, std::vector<float>& msg_vector);
void print_float_vector(HardwareSerial* Serial, std::vector<float>& msg_vector, int option);