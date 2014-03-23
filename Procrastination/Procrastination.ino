// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo srvPan;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
Servo srvTilt;
int pos = 0;    // variable to store the servo position 
int maxPos = 150;
 
void setup() 
{   
  srvPan.attach(9);
  srvTilt.attach(10);  // attaches the servo on pin 9 to the servo object 
} 
 
 
void loop() 
{ 
  for(pos = 0; pos < maxPos; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    srvTilt.write(pos);              // tell servo to go to position in variable 'pos' 
    srvPan.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = maxPos; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    srvTilt.write(pos);              // tell servo to go to position in variable 'pos' 
    srvPan.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
}
