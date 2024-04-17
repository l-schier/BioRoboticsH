#define SERVO_SPEED 2 // servo speed in ms
#include <Servo.h>
#include <Arduino.h>

//front left and back right curl when all are 0
int front_left_pos = 0;   // desired angle for front left leg
int front_right_pos = 180;  // desired angle for front right leg
int rear_left_pos = 180;    // desired angle for rear left leg
int rear_right_pos = 0;   // desired angle for rear right leg

Servo front_right; // front right leg
Servo front_left;  // front left leg
Servo rear_right;  // rear right leg
Servo rear_left;   // rear left leg

#define front_left_pin 9
#define front_right_pin 7
#define rear_left_pin 22
#define rear_right_pin 23
/*
Actual pins
#define rear_left_pin 11
#define rear_right_pin 5

*/

int set = 1;

bool servoPosCheck()
{
    if (front_right_pos != front_right.read()) return false;
    if (front_left_pos != front_left.read()) return false;
    if (rear_right_pos != rear_right.read()) return false;
    if (rear_left_pos != rear_left.read()) return false;
    return true;
}

void setServoPos(int left_front, int right_front, int left_rear, int right_rear)
{
  front_left_pos = left_front;
  front_right_pos = right_front;
  rear_left_pos = left_rear;
  rear_right_pos = right_rear;
}

void setup()
{
  // initialize serial communication
  Serial.begin(9600);
  
  // initialize servos
  front_right.attach(front_right_pin); // front right leg
  front_left.attach(front_left_pin); // front left leg
  rear_right.attach(rear_right_pin); // rear right leg
  rear_left.attach(rear_left_pin); // rear left leg

}


void loop()
{
  static unsigned long servo_time;
  
  // check time since last servo position update 
  if ((millis()-servo_time) >= SERVO_SPEED) {
    servo_time = millis(); // save time reference for next position update
    
    // update front_right position
    // if desired position is different from current position move one step left or right
    if (front_right_pos > front_right.read()) front_right.write(front_right.read() + 1);
    else if (front_right_pos < front_right.read()) front_right.write(front_right.read() - 1);
    // update front_left position
    if (front_left_pos > front_left.read()) front_left.write(front_left.read() + 1);
    else if (front_left_pos < front_left.read()) front_left.write(front_left.read() - 1);
    // update rear_right position
    if (rear_right_pos > rear_right.read()) rear_right.write(rear_right.read() + 1);
    else if (rear_right_pos < rear_right.read()) rear_right.write(rear_right.read() - 1);
    // update rear_left position
    if (rear_left_pos > rear_left.read()) rear_left.write(rear_left.read() + 1);
    else if (rear_left_pos < rear_left.read()) rear_left.write(rear_left.read() - 1);
  }



  if (servoPosCheck()) {
    // if all servos are in desired position, update desired position
    if (set == 1) {
        setServoPos(0, 60, 60, 0);
        set = 2;
        Serial.println("set 2");
    }else if (set == 2) {
        setServoPos(60, 180, 180, 60);
        set = 3;
        Serial.println("set 3");
    }else if (set == 3) {
        setServoPos(40, 140, 140, 40);
        set = 1;
        Serial.println("set 1");
    }

  }
  //delay(1000);
}