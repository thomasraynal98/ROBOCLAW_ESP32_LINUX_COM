#include <usefull_32.h>

void read_serial_input(HardwareSerial* Serial, std::vector<float>& msg_vector)
{
    String msg_brut;
    msg_brut   = Serial->readString();

    int idx_A  = -1;
    int idx_B  = 0;

    float data = 0.0;

    while(msg_brut.indexOf('|', idx_A+1 ) != -1)
    {
        idx_B = msg_brut.indexOf('|', idx_A+1 );
        data  = msg_brut.substring(idx_A+1, idx_B).toFloat();
        msg_vector.push_back(data);
        idx_A = idx_B;
    }

    send_serial_input(Serial, msg_brut);
}

void send_serial_input(HardwareSerial* Serial, String msg_vector)
{
    Serial->println(msg_vector);
}

void print_float_vector(HardwareSerial* Serial, std::vector<float>& msg_vector, int option)
{
    // option == 0 >> print each float one by one.
    // option == 1 >> print all float in one string.

    if(option == 0)
    {
        for(float value : msg_vector)
        {
            Serial->println(value);
        }
    }
    else if(option == 1)
    {
        String msg_str = "";
        for(float value : msg_vector)
        {
            msg_str += String(value) + "|";
        }
        Serial->println(msg_str);
    }
}