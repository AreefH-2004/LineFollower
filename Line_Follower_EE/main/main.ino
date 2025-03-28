#include <Servo.h>


#define irSensor 2  // right
#define irSensor1 8  //left

// Servo Motor Pins
const int motorleft = 4;   // Left rear wheel PWM pin
const int motorright = 5;  // Right rear wheel PWM pin

// Line Follower Sensor Pins
const int irSensorLeft = 8;
const int leftSensor = 13;
const int centerSensor = 12;
const int rightSensor = 11;
const int irSensorRight = 2; 

Servo servoleft;
Servo servoright;

// Global constants (defined in constants.h)
const float leftirsensor_weight = -0.3f;
const float left_weight = -0.1f;
const float centerWeight = 0.0f;
const float right_weight = 0.1f;
const float rightirsensor_weight = 0.3f;

// Function to read IR sensor value
int sensor_value(int version) {


  if (version < 500) {
      return 1;
  } else {
   
    return 0;
  }

  delay(500);  // Small delay for stability
}

// Function to assign weights if values are 0

void weighted_logic(int &irLeftVal,  int &leftState, int &centerState, int &rightState, int &irRightVal) {
    // Array to hold float sensor values
   
    // Array to hold integer state values
    int truth_values[] = {irLeftVal, leftState, centerState, rightState, irRightVal};

  
    const float weights[] = {leftirsensor_weight, left_weight, centerWeight, right_weight, rightirsensor_weight};

    float movement = 0;

    for (int i = 0; i < 5; i++) {
        if (truth_values[i] == 1) {
            movement += weights[i];
        }
    }
// const float leftirsensor_weight = -0.3f;
// const float left_weight = -0.1f;
// const float centerWeight = 0.0f;
// const float right_weight = 0.1f;
// const float rightirsensor_weight = 0.3f;

    if (movement == 0){
          Serial.println("Robot: Forward");
          servoleft.writeMicroseconds(1700);  // Right amount for forward
          servoright.writeMicroseconds(1300); // Opposite direction forward
    }
    else if (-0.3 < movement && movement < 0 ) {  // Corrected boundary check
        // Slight left veer
        servoleft.writeMicroseconds(1300);  
        servoright.writeMicroseconds(1700);
        Serial.println("Robot: S Left");
    } 
    else if (0.3 > movement && movement > 0) {
        // Slight right veer
        servoleft.writeMicroseconds(1700);
        servoright.writeMicroseconds(1300);
        Serial.println("Robot: S Right");
    }
    else if ( movement <= -0.3 ) {
        // Hard left turn
        servoleft.writeMicroseconds(1100);  // Left wheel slow (or reverse)
        servoright.writeMicroseconds(1900); // Right wheel fast forward
        Serial.println("Robot: Left");
    } 
    else if (movement >= 0.3) {
        // Hard right turn
        servoleft.writeMicroseconds(1900);  
        servoright.writeMicroseconds(1100);
        Serial.println("Robot: Right");
    }

    
  
}



void setup() {
     Serial.begin(9600); // Debugging output

  // Attach servos to their respective pins
  servoleft.attach(motorleft);
  servoright.attach(motorright);

  // Set sensor pins as input
  pinMode(irSensorLeft, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(centerSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(irSensorRight, INPUT);
}

void loop() {

  
   
  int irLeftVal_temp = analogRead(A0);  // IR Left uses analog values
  int leftState = digitalRead(leftSensor);
  int centerState = digitalRead(centerSensor);
  int rightState = digitalRead(rightSensor);
  int irRightVal_temp = analogRead(A2);  // IR Right uses analog values

  int Left_ir = sensor_value(irLeftVal_temp);
  int Right_ir = sensor_value(irRightVal_temp);
    // Assign weights if necessary

    // Print updated values
    Serial.print("  ir_leftState: "); Serial.print(Left_ir);
    Serial.print(" | leftState: "); Serial.print(leftState);
    Serial.print(" | centerState: "); Serial.print(centerState);
    Serial.print(" | RightState: "); Serial.print(rightState);  // Moves to new line
    Serial.print(" | ir_rightState: "); Serial.println(Right_ir);

    // Forward movement when only the center sensor detects the line
  
   weighted_logic(Left_ir,  leftState, centerState, rightState, Right_ir);
  

  // if (( centerState == 0 &&  rightState == 1) && (leftState == 0 && centerState == 0 &&  rightState == 0) ) {
  //   Serial.println("Moving Forward");
  //   servoleft.writeMicroseconds(1300);  // Left wheel forward
  //   servoright.writeMicroseconds(1700); // Right wheel forward
  // }
  
  // // // Turn left when left sensor detects the line
  // else if (((leftState == 0 && centerState == 0) || (leftState == 0 && centerState == 1 &&  rightState == 1))  &&  rightState == 1 ) {
  //   Serial.println("Turning Left");
  //       servoleft.writeMicroseconds(1700);  // Left wheel forward
  //   servoright.writeMicroseconds(1500); // Right wheel stops/slows
  // }
  // // // Turn right when right sensor detects the line
  // else if (((rightState == 0 && centerState == 0) || (rightState == 0 && centerState == 1))  &&  leftState == 1 ) {
  //   Serial.println("Turning Right");


  //       servoleft.writeMicroseconds(1500);  // Left wheel stops/slows
  //   servoright.writeMicroseconds(1300); // Right wheel forward
  // }
  // else{
  // // Stop if no sensor detects the line 
  

    delay(1000);  // Wait before repeating


}





