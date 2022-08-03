#include <usefull_32.h>
#include <RoboClaw.h>
#include <Arduino.h>
#include <mutex>

TaskHandle_t thread_com_linux;
std::vector<String> msg_vect;
SemaphoreHandle_t xMutex = xSemaphoreCreateMutex();

void function_com_linux( void * pvParameters )
{
  /*
    Ce thread à pour fonction de communiquer avec le system
    linux principal.
  */

  while(true)
  {
    if(Serial.available() > 0) 
    { 
      xSemaphoreTake( xMutex, portMAX_DELAY );
      msg_vect.clear();
      read_serial_input(&Serial, msg_vect);
      xSemaphoreGive( xMutex );
    }
    else
    {
      delay(20);
    }
  }
}

// Serial.print("com_linux() running on core ");
// Serial.println(xPortGetCoreID());
// delay(1000);

RoboClaw roboclaw(&Serial2, 10000);

void setup() {
  Serial.begin(115200);
  
  xTaskCreatePinnedToCore(
                    function_com_linux,     /* Task function. */
                    "thread_com_linux",     /* name of task. */
                    10000,                  /* Stack size of task */
                    NULL,                   /* parameter of the task */
                    1,                      /* priority of the task */
                    &thread_com_linux,      /* Task handle to keep track of created task */
                    0);                     /* pin task to core 0 */                  
  delay(500); 

  pinMode(ONBOARD_LED, OUTPUT);

  roboclaw.begin(115200);
  roboclaw.ForwardM1(0x80, 0);
  roboclaw.ResetEncoders(0x80);
  roboclaw.SetM1EncoderMode(0x80, 0);
  roboclaw.SetM1VelocityPID(0x80, 1.32, 0.18, 0.0, 15000);
}

int id_controler_A = 0x80;
int id_controler_B = 0x81;
int id_controler_C = 0x82;

void loop() {
  /*
    Ce thread à pour fonction de communiquer avec roboclaw 
    pour pouvoir envoyer les commandes et recuperer l'ensemble des données.
  */


  xSemaphoreTake( xMutex, portMAX_DELAY );
  // if(msg_vect.size() == 8)
  // {
  //   if(msg_vect[1].toInt() == 0)
  //   {
  //     Serial.println(convert_cmToPulse(msg_vect[2].toFloat()));
  //     if(msg_vect[2].toFloat() > 0) roboclaw.SpeedDistanceM1(id_controler_A, convert_cmToPulse(msg_vect[2].toFloat()), 100000, 1);
  //   }
  // }
  xSemaphoreGive( xMutex );

  // uint16_t temp;
  // roboclaw.ReadTemp(id_controler_A, temp);
  // // uint16_t curr1; uint16_t curr2;
  // // roboclaw.ReadCurrents(id_controler_A, curr1, curr2);
  // bool t = false;
  // uint16_t bat_v = roboclaw.ReadMainBatteryVoltage(id_controler_A, &t);
  // Serial.println(bat_v);
  // digitalWrite(ONBOARD_LED, HIGH);
  // roboclaw.ForwardM1(0x80,12);
  // delay(2000);
  // digitalWrite(ONBOARD_LED, LOW);
  // roboclaw.ForwardM1(0x80,0);
  // delay(2000);

  // roboclaw.SpeedDistanceM1(id_controler_A, -2000, 20000, 1);
  // delay(5000);
  // roboclaw.SpeedDistanceM1(id_controler_A, 2000, 20000, 1);
  // delay(5000);
  
  Serial.println(roboclaw.ReadEncM1(id_controler_A));

  delay(1000);
}