#include <Servo.h>
  
// ---- Create servo objects ----
Servo servoBase;
Servo servoShoulder;
Servo servoElbow;
Servo servoGripper;
Servo body_part_order[] = {servoBase, servoShoulder, servoGripper, servoShoulder};

// ---- Servo pin assignments ----
const int PIN_BASE = 3;
const int PIN_SHOULDER = 5;
const int PIN_ELBOW = 6;
const int PIN_GRIPPER = 9;

// VARIABLES
const int BASE_POS_RIGHT_SIDE = 180;
const int BASE_POS_LEFT_SIDE = 0;
const int SHOULDER_POS_LIFT_UP = 120;
const int GRIPPER_BLOCK_WIDTH = 85;
const int GRIPPER_DUCK_WIDTH = 95;
const int GRIPPER_OPEN = 130;
const int DELAY = 800;
int shoulder_drop_right = 0;
int shoulder_drop_left = 0;
int right_side_block_pickup_pos[] = {BASE_POS_RIGHT_SIDE, shoulder_drop_right, GRIPPER_BLOCK_WIDTH, SHOULDER_POS_LIFT_UP};
int left_side_block_pickup_pos[] = {BASE_POS_LEFT_SIDE, shoulder_drop_left, GRIPPER_OPEN, SHOULDER_POS_LIFT_UP};
int right_side_duck_pickup_pos[] = {150, shoulder_drop_right, GRIPPER_DUCK_WIDTH, 40};
int left_side_duck_pickup_pos[] = {180, GRIPPER_OPEN};
bool run_once = true;

void move_arm_to_start_position(bool b) {
  // Get to starting position
  servoShoulder.write(120); delay(DELAY);
  servoBase.write(90); delay(DELAY);
  servoElbow.write(95); delay(DELAY);
  if (b == false){
      servoElbow.write(140); delay(DELAY);
      delay(5000);
  }
  servoGripper.write(GRIPPER_OPEN); delay(DELAY);
}

void move_arm(Servo body_part, int movement_amount){
  body_part.write(movement_amount); 
  delay(DELAY);
}

void setup() {
  // Attach the servos
  servoBase.attach(PIN_BASE);
  servoShoulder.attach(PIN_SHOULDER);
  servoElbow.attach(PIN_ELBOW);
  servoGripper.attach(PIN_GRIPPER);

  move_arm_to_start_position(true);
}

void loop() {

  if (run_once == true) {
    // BLOCK 1
    shoulder_drop_right = 173;
    shoulder_drop_left = 170;
    right_side_block_pickup_pos[1] = shoulder_drop_right;
    left_side_block_pickup_pos[1] = shoulder_drop_left;

    // Right side; block pickup
    for (int i = 0; i < 4; i++) {
      move_arm(body_part_order[i], right_side_block_pickup_pos[i]);
    }
    // Left side; block release
    for (int i = 0; i < 4; i++) {
      move_arm(body_part_order[i], left_side_block_pickup_pos[i]);
    }

    // YELLOW DUCK
    shoulder_drop_right = 180;
    shoulder_drop_left = 0;
    right_side_duck_pickup_pos[1] = shoulder_drop_right;
    left_side_duck_pickup_pos[1] = shoulder_drop_left;
    
    // Right side; pickup
    for (int i = 0; i < 4; i++) {
      move_arm(body_part_order[i], right_side_duck_pickup_pos[i]);
    }
    // Left side; drop
    move_arm(servoBase, 130);
    move_arm(servoElbow, 180);
    move_arm(servoGripper, GRIPPER_OPEN);
    move_arm_to_start_position(true);

    // POSITIVE POTATO

    //Pickup
    move_arm(servoShoulder, 100);
    move_arm(servoBase, 40);
    move_arm(servoElbow, 180);
    move_arm(servoShoulder, 150);
    move_arm(servoShoulder, 173);
    move_arm(servoGripper, GRIPPER_BLOCK_WIDTH);
    move_arm(servoShoulder, 160);
    move_arm_to_start_position(false);
  }
  run_once = false;
}

// //#include <dummy.h>

// //#include <ESP32Servo.h>

// //Servo servoBase;


// ---- Incoming serial buffer ----
// String incoming = "";

// // Choose a SAFE GPIO pin (not strapping pins)
// const int PIN_BASE = 18;   // GPIO18 is good

// String incoming = "";

// void setup() {
    // Serial is built in global object provided by Arduino
//   // Serial.begin(115200);
//   // servoBase.setPeriodHertz(50);     // Standard servo frequency
//   // servoBase.attach(PIN_BASE, 500, 2400);  // min/max pulse
//   // servoBase.write(90);
// }
// void loop() {}

  /*
    The write command does the following:
    -Give the servo the desired position for it to strive to.
    -The servo holds this desired position forever, because even after the first time it reaches
    -...it, it can drift.  
    -So we don't want to stop it after we write it.
    -The servo constantly checks if it wavers from the 90 degree angle and moves back towards it if so.
    -Note, 90 converts to ~1.5 microseconds.  This is how long the digital signal pulses HIGH HOWEVER
    -...it is NOT how long it moves the motor.  That microseconds are used in a deeper calculation
    -...with the pentiometer.
  */

//void loop() {
  // Read incoming chars until new line
  // Say this command sent from ROS, over the USB, to the Arduino RX: //"B:90,S:40,E:20,G:10\n"
  // while (Serial.available()>0) {
  //   char c = Serial.read()
  //   if (c == "\n"){
  //       processCommand();

//}

