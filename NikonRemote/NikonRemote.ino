#include <avr/sleep.h>

//The IR-led is connected to pin 13
int ir_led_pin = 13;

void setup()
{
  pinMode (ir_led_pin, OUTPUT);
  digitalWrite (ir_led_pin, LOW);
  
  //Set the interrupt on pin 2 to call the wakeUp ISR
  attachInterrupt(0, wakeUp, CHANGE);
}

/* The loop function just puts the boar at sleep and waits
*  for the wakeUp interrupt. Then sends the shoot signal to 
*  the camera via the IR-led
*/
void loop()
{
  sleepNow ();
  shootPic (ir_led_pin);
}

//This function just wakes the Arduino up, it just does nothing
void wakeUp () {}

void sleepNow () {
  //Select sleep mode
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  
  //Enable sleep mode
  sleep_enable ();
  
  //Attach interrupt 
  attachInterrupt (0, wakeUp, CHANGE);
  
  //Sleep tight
  sleep_mode ();
  
  //After wake up the flow will restart here, so disable sleep mode
  sleep_disable ();
  
  //Disable the interrupt to avoid interference with the ISR
  detachInterrupt (0);
}

/* This function encodes the shoot singnal for Nikon DSLR cameras
*/
void shootPic (int pin) {
   pulseOn (pin, 2000); 
   delayMicroseconds (7830);
   delayMicroseconds (10000);
   delayMicroseconds (10000);
   pulseOn (pin, 390);
   delayMicroseconds (1580);
   pulseOn (pin, 410);
   delayMicroseconds (3850);
   pulseOn (pin, 400);
}

//Pulse modulation
void pulseOn (int pin, int time) {
  static const int period = 25;
  static const int wait_time = 9;  

  for (time = time/period; time > 0; time--) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(wait_time);
    digitalWrite(pin, LOW);
    delayMicroseconds(wait_time);
  }
}

