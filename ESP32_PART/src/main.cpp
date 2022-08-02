#include <usefull_32.h>
#include <RoboClaw.h>
#include <Arduino.h>

TaskHandle_t thread_com_linux;
std::vector<float> msg_vect;

// void function_com_linux( void * pvParameters )
// {
//   /*
//     Ce thread à pour fonction de communiquer avec le system
//     linux principal.
//   */

//   while(true)
//   {
//     if(Serial.available() > 0) 
//     { 
//       msg_vect.clear();
//       read_serial_input(&Serial, msg_vect);
//     }
//     else
//     {
//       delay(10);
//     }
//   }
// }

// Serial.print("com_linux() running on core ");
// Serial.println(xPortGetCoreID());
// delay(1000);

RoboClaw roboclaw(&Serial2, 10000);

void setup() {
  // Serial.begin(38400);
  
  // xTaskCreatePinnedToCore(
  //                   function_com_linux,     /* Task function. */
  //                   "thread_com_linux",     /* name of task. */
  //                   10000,                  /* Stack size of task */
  //                   NULL,                   /* parameter of the task */
  //                   1,                      /* priority of the task */
  //                   &thread_com_linux,      /* Task handle to keep track of created task */
  //                   0);                     /* pin task to core 0 */                  
  // delay(500); 

  // pinMode(ONBOARD_LED, OUTPUT);

  roboclaw.begin(38400);

}

void loop() {
  /*
    Ce thread à pour fonction de communiquer avec roboclaw 
    pour pouvoir envoyer les commandes et recuperer l'ensemble des données.
  */


  // digitalWrite(ONBOARD_LED, HIGH);
  roboclaw.ForwardM1(0x80,12);
  delay(2000);
  // digitalWrite(ONBOARD_LED, LOW);
  roboclaw.ForwardM1(0x80,0);
  delay(2000);
}