#include <usefull_32.h>

TaskHandle_t thread_com_linux;
std::vector<float> msg_vect;

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
      msg_vect.clear();
      read_serial_input(&Serial, msg_vect);
      print_float_vector(&Serial, msg_vect, 1);
    }
    else
    {
      delay(10);
    }
  }
}

// Serial.print("com_linux() running on core ");
// Serial.println(xPortGetCoreID());
// delay(1000);

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

  pinMode(ONBOARD_LED,OUTPUT);
}

void loop() {
  /*
    Ce thread à pour fonction de communiquer avec roboclaw 
    pour pouvoir envoyer les commandes et recuperer l'ensemble des données.
  */

  digitalWrite(ONBOARD_LED,HIGH);
  delay(100);
  digitalWrite(ONBOARD_LED,LOW);
  delay(100);
}