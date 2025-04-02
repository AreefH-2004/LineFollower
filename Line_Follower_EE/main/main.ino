/*
 * Line Follower Robot - Arduino Project
 * 
 * This program uses five IR sensors and a weighted logic system to follow a line
 * with improved responsiveness. The weights prioritize sensors based on position, 
 * enabling smoother turns and better error correction compared to binary thresholding.
 *
 * Components:
 * - Funduino IR sensors
 * - Arduino Uno
 * - Servo motors (x2)
 * - Differential salvaged from toy car
 * - DC-DC step-down converter
 *
 * Author: [Areef Hossain]
 * GitHub: [https://github.com/AreefH-2004]
 */


#include <Servo.h>
// Implemented a weighted logic system to enhance the robot’s adaptability 
// across various track layouts. Unlike rigid binary input handling, this approach assigns higher
// influence to sensors detecting line presence, enabling smoother and more responsive navigation.

//This weighted system takes in values from the funduino and ir sensors. 

//Initializing ardunio pin I/O
#define irSensor 2  // right
#define irSensor1 8  //left

// Servo Motor Pins - Arduino Shield
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

// Global constants 
const float leftirsensor_weight = -0.3f;
const float left_weight = -0.1f;
const float centerWeight = 0.0f;
const float right_weight = 0.1f;
const float rightirsensor_weight = 0.3f;

// Function to read IR sensor value and translate into binary I/O
// Converts analog IR sensor reading into binary input (1 = line not detected, 0 = line detected)
int sensor_value(int version) {


  if (version < 500) {
      return 1;
  } else {
   
    return 0;
  }

 
}

// Weighted logic - Function for decision making 
void weighted_logic(int &irLeftVal,  int &leftState, int &centerState, int &rightState, int &irRightVal) {

    //Intialize paramters into an array
    int truth_values[] = {irLeftVal, leftState, centerState, rightState, irRightVal};

    //Initalizes global weights into an array
    const float weights[] = {leftirsensor_weight, left_weight, centerWeight, right_weight, rightirsensor_weight};

    //Intializes the movement variable that will used in the line-follower's decision making
    float movement = 0;

    //Loop essentially adds the value of a weight, if the corresponding sensor value is 0/ less light is reflected. 
    for (int i = 0; i < 5; i++) {
        if (truth_values[i] == 0) {
            movement += weights[i]; 
        }
    }


    if (movement == 0){
          //Forward Logic
          Serial.print(movement); Serial.println(" Robot: Forward");

          servoleft.writeMicroseconds(1300); 
          servoright.writeMicroseconds(1700);

          delay(30);  // Wait before repeating
          
    }
    else if (movement < -0.09 ) {  // Corrected boundary check
        // Right turn Logic
        Serial.print(movement);Serial.println(" Robot: S Right");

        servoleft.writeMicroseconds(1500);  
        servoright.writeMicroseconds(1700);
        
        delay(30);  // Wait before repeating
 
    } 
    else if (movement > 0.09) {
        //Left turn Logic
        Serial.print(movement);Serial.println(" Robot: S Left");

        servoleft.writeMicroseconds(1300);  
        servoright.writeMicroseconds(1500);
  
        delay(30); 
    }

    else{
      // Failsafe / drift handling
       servoleft.writeMicroseconds(1500);
       servoright.writeMicroseconds(1500);

       delay(100);

       Serial.print(movement); Serial.println("Issue");
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
    Serial.print(" | RightState: "); Serial.print(rightState);  
    Serial.print(" | ir_rightState: "); Serial.println(Right_ir);


    if (Left_ir == 1 && leftState == 1 && centerState == 1 && rightState == 1 && Right_ir == 1) {
     servoleft.writeMicroseconds(1500);
     servoright.writeMicroseconds(1500);
      Serial.println(" Movement: NULL - Robot: Stop");
   
      delay(100);

    }
    else {
          weighted_logic(Left_ir,  leftState, centerState, rightState, Right_ir);
    }
   


    delay(100);  // Wait before repeating


}





