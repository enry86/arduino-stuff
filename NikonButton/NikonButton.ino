#include <avr/sleep.h>

int pin = 13;
int state = LOW;

void setup()
{
  pinMode(pin, OUTPUT);
  digitalWrite (pin, LOW);
  attachInterrupt(0, wakeUp, LOW);
}

void loop()
{
  sleepNow ();
  shootPic (pin);
}

void wakeUp () {}

void sleepNow () {
set_sleep_mode(SLEEP_MODE_PWR_DOWN);
sleep_enable();
attachInterrupt(0,wakeUp, LOW);
sleep_mode();  
sleep_disable();
detachInterrupt(0);
}


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

void pulseOn(int pin, int time) {
  static const int period = 25;
  static const int wait_time = 9;  

  for (time = time/period; time > 0; time--) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(wait_time);
    digitalWrite(pin, LOW);
    delayMicroseconds(wait_time);
  }
}

